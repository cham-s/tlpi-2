#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include "tlpi_hdr.h"


/*
	Mix of exert from BSD man(2) open and chars added for corresponding
	flags

	r		O_RDONLY        open for reading only
	w		O_WRONLY        open for writing only
	rw		O_RDWR          open for reading and writing

		In addition any combination of the following values can be or'ed in oflag:

	nb		O_NONBLOCK      do not block on open or for data to become available
	a		O_APPEND        append on each write
	cr		O_CREAT         create file if it does not exist
	tr		O_TRUNC         truncate size to 0
	exc		O_EXCL          error if O_CREAT and the file exists
	s		O_SHLOCK        atomically obtain a shared lock
	excl	O_EXLOCK        atomically obtain an exclusive lock
	nf		O_NOFOLLOW      do not follow symlinks
	sy		O_SYMLINK       allow open of symlinks
	ev		O_EVTONLY       descriptor requested for event notifications only
	clo		O_CLOEXEC       mark as close-on-exec

*/

/*
 
*/

/**
	Wrapper to avoid the ceremonial settings of flags and file permissions for
	the syscall open(2). 

	- Parameters:
		- filename: Pointer to the filename to open 
		- flags: Pointer to a string representation of the flags to set
		- perms: Pointer to a string representation of permissions to set 

	Returns: If sucessful A non negative integer value representing 
			the file descriptor of the opened. Or -1 upon failre.
	
	Errors: Known errors are set using the global var errno. It leverages the 
			great error_functions.c provided by Michael Kerrisk.
			
	//TO Do: Notes

*/


int m_open(const char *filename, const char *flags, const char *perms)
{
	int open_flags;
	int file_perms;
	int fd;
	char *position;

	if (filename == NULL)
		fatal("m_open NULL pointer sent as filename for open");

	open_flags = 0;
	file_perms = 0;

	if (flags == NULL)
		open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (perms == NULL)
		file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	position = strchr(flags, 'c');
	if (position != NULL)
		open_flags |= O_CREAT;

	position = strchr(flags, 'r');
	if (position != NULL)
		open_flags |= O_RDONLY;

	position = strchr(flags, 'w');
	if (position != NULL)
		open_flags |= O_WRONLY;

	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	fd = open(filename, open_flags, file_perms);

	if (fd == - 1)
		errExit("opening file %s", filename);
	return fd;
}
