program simpleprime
     use omp_lib
     implicit none
     integer (kind=4) :: i,j,n,nprimes,nsqroot
     integer (kind=4), allocatable :: primes(:)
     logical (kind=1) :: testprime
     external testprime


     write(6,*) ' Enter the maximum number you want to find as prime'
     read(5,*) n

     allocate(primes(n/4))

     nprimes = 0

end program simpleprime

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


