program helloMPI
  use mpi
  implicit none

  integer :: ierror
  integer :: myRank,uniSize,version,subversion
  character(len=MPI_MAX_PROCESSOR_NAME) :: myName
  integer :: iMyName

  call MPI_Init(ierror)
  call MPI_Comm_size(MPI_COMM_WORLD,uniSize,ierror)
  call MPI_Comm_rank(MPI_COMM_WORLD,myRank, ierror)
  call MPI_Get_processor_name(myName,iMyName, ierror)
  call MPI_Get_version(version,subversion, ierror)
  write(*,'(a,i0,a,i0,a,a,a,i0,a,i0)')"I am process ", myRank, &
              " out of ", uniSize, " running on ", trim(myName), &
              " with MPI version ", version,".",subversion
  call MPI_Finalize(ierror)
end program helloMPI
