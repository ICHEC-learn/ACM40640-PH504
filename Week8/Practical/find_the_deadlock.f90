program find_the_deadlock
   implicit none
   include 'mpif.h'
   integer :: rank, nprocs,ierror,fileunit 
   integer :: indata(25)
   character(len=10) :: filenam

   call MPI_Init(ierror)
   call MPI_Comm_Size(MPI_COMM_WORLD,nprocs,ierror) 
   call MPI_Comm_Rank(MPI_COMM_WORLD,rank,ierror)

   if (rank.eq.0) then
     open(1,FILE='values.dat')
     read(1,*,end=10) indata
     call MPI_Bcast(indata,25,MPI_DOUBLE_PRECISION,1,MPI_COMM_WORLD,ierror)
     close(1)
10   continue
   endif

   write(filenam,'(a,i0)') 'output.',rank

   ! output process rank 0 in file output.0
   ! output process rank 0 in file output.1
   ! output process rank 0 in file output.2
   ! and so on
   fileunit = rank+100
   write(fileunit,*) indata


  call MPI_Finalize(ierror) 
end program find_the_deadlock
