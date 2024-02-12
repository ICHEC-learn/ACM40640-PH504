program race

  use omp_lib
  implicit none
  integer (kind=4) :: i, n, tid, nthreads, ierr
  real (kind=4) :: ainit(1)
  logical (kind=1) :: test
  integer (kind=4), allocatable :: a(:)

  ! Read size of array
  write(6,*)'Please enter the size of the array 2<n<10001'
  read(5,*) n
  if (n.LE.2 .OR. n.GT.1000) then
    write(6,*)'Array size must be in the range 2<n<10001, stopping'
    stop
  endif

  allocate(a(n),stat=ierr)
  if (ierr .NE. 0) then
    write(6,*)'Cannot allocate arrays'
    stop
  endif

  a(1)= 0

  ! Start of parallel region
!$omp parallel private(tid,ainit), shared(nthreads,a)
  tid=omp_get_thread_num()
  nthreads=omp_get_num_threads()
  call random_seed()
  call random_number(ainit)
  a = a(1) + nint(10.0*ainit(1))
  write(*,'(a,1x,i0,1x,a,i0,a,1x,i0)') 'Hello from thread', tid,'out of ',nthreads, ",my a is:",a(1)
!$omp end parallel
  ! End parallel region

  write(*,'(a,1x,i0)')'Hello from master thread, my a is:',a(1)

  deallocate(a)

end program race
