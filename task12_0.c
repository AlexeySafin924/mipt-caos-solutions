#include <sys/mman.h>
#include <dirent.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *file_name = argv[1];
	char *pattern = argv[2];
	int fd = open(file_name, O_RDONLY);
	if (fd == -1) return 0;
	struct stat st;
	fstat(fd, &st);
	if (st.st_size == 0) return 0;
	char *contents = mmap(NULL,
			st.st_size,
			PROT_READ,
			MAP_SHARED,
			fd,
			0);
	char *entry = contents;
	while (NULL != (entry = strstr(entry, pattern))) {
		size_t diff = entry - contents;
		printf("%u ", diff);
		entry++;
	}
	munmap(contents, st.st_size);
	close(fd);
	return 0;
}

