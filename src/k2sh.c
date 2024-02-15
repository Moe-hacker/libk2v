#include "include/k2v.h"
#include <sys/stat.h>
int main(int argc, char **argv)
{
	k2v_show_warning = false;
	if (argc < 2) {
		return 1;
	}
	// Read the config to memory.
	int fd = open(argv[1], O_RDONLY);
	struct stat filestat;
	fstat(fd, &filestat);
	off_t size = filestat.st_size;
	char *buf = k2v_open_file(argv[1], (size_t)size);
	k2v_to_shell(buf);
	free(buf);
}
