module subs
    integer (kind=4) :: n
    integer (kind=4), allocatable :: primes(:)
    contains
      logical (kind=1) function testprime(i)
        implicit none
        integer (kind=4), intent(in) :: i 
        integer (kind=4) :: j,nsqroot

        nsqroot = ceiling(sqrt(real(i))) + 1
        if (nsqroot .ge. i) nsqroot = i - 1

        j = 2
        do while (mod(i,j).NE.0 .and. j.le.nsqroot) 
          j = j + 1
        end do

        testprime = .FALSE.    
        if (j .GT. nsqroot) testprime=.TRUE.
        return
      end function testprime

      subroutine removenums(i)
        integer (kind=4), intent(in) :: i
        integer (kind=4) :: j

        j = i*2
        do while (j .LE. n)
          primes(j) = -1
          j = j + i
        end do 
 
      end subroutine removenums
end module subs       



program primesieve
    use omp_lib
    use subs
    implicit none
    integer (kind=4) :: i,nprimes,ierr,tid


    write(6,*) ' What is the highest number you want to test?'
    read(5,*) n
    if (n .LT. 2) then
      write(6,*) ' Number must be bigger than 1, stopping'
      stop
    endif


    allocate(primes(n),stat=ierr)
    if (ierr .NE. 0) then
       write(6,*) ' Cannot allocate array, stopping '
       stop
    endif

    forall (i=1:n) primes(i)=i
    primes(1) = -1

end program primesieve