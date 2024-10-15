#include "readelf.h"

void error_handler(char *error)
{
	fprintf("%s: %s: %s\n", 
			filestate.program_name,
			filestate.exec_name,
			error);

	if (fcntl(filestate.fd, F_GETFD) != -1)
	{
		close(filestate.fd);
	}
	exit(EXIT_FAILURE);
}
