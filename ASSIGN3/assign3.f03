program assign3

	implicit none
	
	character(len=:),allocatable :: input, output
	
	integer arglen
	integer :: a, b, i, j, k, temp
	integer, dimension (:, :), allocatable :: matrix
	logical :: swapped
	
	call get_command_argument(1,length=arglen)
	allocate(character(arglen) :: input)
	call get_command_argument(1, input)
	
	call get_command_argument(2,length=arglen)
	allocate(character(arglen) :: output)
	call get_command_argument(2, output)
	
	open(3, file=input, status='old')
	read(3, *) a, b
	
	open(4, file=output, status='new')
	
	allocate(matrix(a,b))
	
	do i=1,a
		read(3,*) matrix(i,:)
	end do

	!do i=1,a
		!write(*,*)(matrix(i,j),j=1,b)
	!end do

	!write(*,*) ""

	do i=1,a
		do k=b-1, 1, -1
			swapped = .FALSE.
			do j=1, k
				if (matrix(i,j) > matrix(i,j+1)) then
					temp = matrix(i,j)
					matrix(i,j) = matrix(i,j+1)
					matrix(i,j+1) = temp
					swapped = .TRUE.
				endif
			end do
			if (.NOT. swapped) EXIT
		end do
	end do
	
	!do i=1,a
		!write(*,*)(matrix(i,j),j=1,b)
	!end do
	do k=a-1, 1, -1
		swapped = .FALSE.
		do j=1, k
			if (matrix(j,1) > matrix(j+1,1)) then
				do i=1,a-1
					temp = matrix(j,i)
					matrix(j,i) = matrix(j+1,i)
					matrix(j+1,i) = temp
				end do
				swapped = .TRUE.
			endif
		end do
		if (.NOT. swapped) EXIT
	end do
	
	!write(*,*) ""
	
	do i=1,a
		write(4,*)(matrix(i,j),j=1,b)
	end do

	deallocate(input)
	deallocate(output)
	deallocate(matrix)
end program assign3

