#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	struct stat st;
	int fd = open(argv[1], O_RDONLY);
	lstat(argv[1], &st);
	if (-1 == fd || st.st_size == 0) return 0;
	int32_t *data = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	printf("%d ", data[0]);
	uint32_t next_pointer = data[1];
	while (next_pointer > 0) {
		int value = data[next_pointer / sizeof(int32_t)];
		next_pointer = data[next_pointer / sizeof(int32_t) + 1];
		printf("%d ", value);
	}
	munmap(data, st.st_size);
	close(fd);
	return 0;
}

