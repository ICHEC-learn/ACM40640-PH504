!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! DESCRIPTION:
! This program increments every element of the array by two.
! Compile: 
!	$mpif90 inc_mpi.f90 -o inc_mpif -fopenmp
! Run:
! 	$mpirun -np 2 ./inc_mpif <array length> <nSamples> 
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
program inc_serial
  use omp_lib
  use mpi
  implicit none

  integer :: i, j
  integer(kind=16) :: length, nSamples
  integer :: len_per_process, remainder, mylen_per_process
  integer :: procs, rank, ierr
  real(kind=8), allocatable :: a(:), a_per_process(:)
  integer, allocatable :: recvcounts(:), displs(:)
  real(kind=8) :: start_comp, start_comm, last_comp, last_comm
  real(kind=8) :: maxtime_comp, maxtime_comm
  character(len=32) :: arg

  !Get array length and number of times to run the computation
  if (COMMAND_ARGUMENT_COUNT() /=2) then
    write(*,'(a)')"Wrong usage!!!"
    write(*,'(a)')"Correct usage: "
    CALL get_command_argument(0, arg)
    write(*,'(a)')trim(arg)//" <n>  <NSamples>"
    stop
  endif

  CALL get_command_argument(1, arg)
  read(arg,*) length
  CALL get_command_argument(2, arg)
  read(arg,*) NSamples

  call MPI_Init(ierr)
  call MPI_Comm_size(MPI_COMM_WORLD, procs, ierr)
  call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)

  !Whole array allocation in master process
  if(rank .eq. 0) then
    allocate(a(length))
  end if
  allocate(recvcounts(procs))
  allocate(displs(procs))

  !Data distribution to processes
  len_per_process = length/procs
  remainder = mod(length, procs)
  if(rank .lt. remainder) then
    mylen_per_process = len_per_process+1
  else
    mylen_per_process = len_per_process
  end if
  call MPI_AllGather(mylen_per_process, 1, MPI_INTEGER, recvcounts, 1, MPI_INTEGER, MPI_COMM_WORLD, ierr)
  displs(1) = 0
  do i=2, procs
    displs(i) = displs(i-1) + recvcounts(i-1)
  end do

  !Sub-Arrays Allocation and Initialisation at each process
  allocate(a_per_process(mylen_per_process))
  do i=1,mylen_per_process
    a_per_process(i)=0.0
  end do

  !Increment elements by 2
  start_comp=omp_get_wtime()
  do i=1, nSamples
    do j=1,mylen_per_process
      a_per_process(j)=a_per_process(j)+2.0
    end do
  end do
  last_comp=omp_get_wtime()-start_comp
  start_comm=omp_get_wtime()
  call MPI_Gatherv(a_per_process, mylen_per_process, MPI_DOUBLE_PRECISION, &
                   a, recvcounts, displs, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD, ierr) 
  last_comm=omp_get_wtime()-start_comm
  
  !Check correctness
  do i=1,length
    if(rank .eq. 0) then
      if(a(i) .ne. 2.0*nSamples) then
        write(*,*)"Not equal at ", i
        exit
      end if
    end if
  end do

  call MPI_Reduce(last_comp, maxtime_comp, 1, MPI_DOUBLE_PRECISION, MPI_MAX, 0, MPI_COMM_WORLD, ierr);
  call MPI_Reduce(last_comm, maxtime_comm, 1, MPI_DOUBLE_PRECISION, MPI_MAX, 0, MPI_COMM_WORLD, ierr);
  if(rank .eq. 0) then
    write(*,*)'Size= ', length, 'Number of processes= ', procs
    write(*,'(a,f18.7, a)')'Computation Time= ', maxtime_comp/nSamples, 'sec'
    write(*,'(a,f18.7, a)')'Communication Time= ', maxtime_comm, 'sec'
  end if

  deallocate(a_per_process)
  deallocate(recvcounts)
  deallocate(displs)
  if(rank .eq. 0) then
    deallocate(a)
  end if
  call MPI_Finalize(ierr)
end program 
