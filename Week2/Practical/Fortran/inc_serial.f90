!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! DESCRIPTION:
! This program increments every element of the array by two.
! Compile: 
!	$gfortran inc_serial.f90 -o inc_serialf -fopenmp
! Run:
! 	$./inc_serialf <array length> <nSamples>
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
program inc_serial
  use omp_lib
  implicit none

  integer :: i, j
  integer(kind=16) :: length, nSamples
  real(kind=8), allocatable :: a(:)
  real(kind=8) :: start, last
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

  !Array Allocation and Initialisation
  allocate(a(length))
  do i=1,length
    a(i)=0.0
  end do

  !Increment elements by 2
  start=omp_get_wtime()
  do i=1, nSamples
    do j=1,length
      a(j)=a(j)+2.0
    end do
  end do
  last=omp_get_wtime()

  !Check correctness
  do i=1,length
    if(a(i) .ne. 2.0*nSamples) then
      write(*,*)"Not equal at ", i
      exit
    end if
  end do

  write(*,*)'Size= ', length
  write(*,'(a,f18.7, a)')'Average Execution Time= ', (last-start)/nSamples, 'sec'

  deallocate(a)
end program 
