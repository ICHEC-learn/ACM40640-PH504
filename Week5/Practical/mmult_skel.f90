program matrixmult
   use omp_lib
   implicit none
   integer (kind=4) :: i,j,k,ierr,indx
   integer (kind=4) :: seed(33)
   real (kind=4), allocatable :: rvect(:)
   type matrix 
     integer (kind=4) :: nrow, ncol
     real (kind=4), allocatable :: matrix(:,:)
   end type
   type (matrix) :: a, b, c


! Read in the matrix sizes
   write(6,*) ' Enter size of A (row,column) '
   read(5,*) a%nrow, a%ncol
   write(6,fmt='(2(a,i0))') ' Matrix A rows=',a%nrow,' columns=',a%ncol

   write(6,*) ' Enter size of B (row,column) '
   read(5,*) b%nrow, b%ncol
   write(6,fmt='(2(a,i0))') ' Matrix B rows=',b%nrow,' columns=',b%ncol


! Check values 
   if (a%ncol .NE. b%nrow) then
     write(6,*) ' These matrices cannot be multiplied, stopping'
     stop
   else 
     c%nrow = a%nrow
     c%ncol = b%ncol
   endif

! Assign space 

! Initialise matrices

! Perform A.B

! Write to a file

end program matrixmult