program testDOT
  use omp_lib
  implicit none
  interface
    real(kind=8) function dot(a,b,n)
      real(kind=8), intent(in) :: a(:),b(:)
      integer, intent(in) :: n
    end function dot
  end interface
    
  integer :: i,j,n,NLoops
  character(len=32) :: arg 
  real(kind=8), allocatable :: a(:),b(:),times(:)
  real(kind=8) :: mint,maxt,z,avg,sig


  if (command_argument_count() /=2) then
    write(*,'(a)')"Wrong usage!!!"
    write(*,'(a)')"Correct usage: "
    call get_command_argument(0, arg)
    write(*,'(a)')trim(arg)//" <n>  <NRepetitions>"
    write(*,'(a)')trim(arg)//" 1000 5"
    stop
  endif

  call get_command_argument(1, arg)
  read(arg,*) n
  call get_command_argument(2, arg)
  read(arg,*) NLoops
  write(*,'(a)',advance='no')"Running... "
  do i=0,command_argument_count()
    call get_command_argument(i, arg)
    write(*,'(a,1x)',advance="no") trim(arg)
  enddo
  write(*,*)
  allocate(a(n),b(n))
  allocate(times(NLoops))
! warm up
  do i=1,NLoops
    do j=1,n
       a(j)=real(j,8)/real(n,8)*real(i,8)
       b(j)=(real(j,8)+0.5_8)/real(n,8)*real(i,8)
    end do
    times(i) = omp_get_wtime()
    z=dot(a,b,n)
    times(i) = omp_get_wtime()-times(i)
  end do
  avg=sum(times)/real(NLoops,8)
  
  sig=0
  write(*,'(a8,a12,a17)')"#Loop  |","       Size|","        Time (s)|"
  do i=1,NLoops
    write(*,'(i6,1x,i12,1x,f16.8)')i,n,times(i)
    sig=sig+(times(i)-avg)*(times(i)-avg)
  enddo 
  sig=sqrt(sig/NLoops)
  write(*,*)
  write(*,'(a,es16.8)')"Last inner product: ",z
  write(*,*)
  write(*,'(a)')"Summary"
  write(*,'(a12,4(a16,1x))')"#Size  |","Avg. Time (s)|","Min. Time (s)|","Max. Time(s)|","σ (s)|"
  write(*,'(i7,1x,4(f16.8,1x))')n,avg,minval(times),maxval(times),sig
  deallocate(a,b,times)

end program testDOT


real(kind=8) function dot(a,b,n)
    implicit none
    real(kind=8), intent(in) :: a(:),b(:)
    integer, intent(in) :: n

    integer :: i
    real(kind=8) :: s
    s=0.0_8
    do i=1,n
      s=s+a(i)*b(i)
    end do
    dot=s
    return
end function dot
