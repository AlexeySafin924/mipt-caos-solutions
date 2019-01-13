#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main(int args, char* argv[]) {
	if (args == 1) return 0;
	int input = open(argv[1], O_RDONLY);
	if (input < 0) { close(input); return 1; }
	int value = -1;
	uint32_t next_pointer = -1;
	if (read(input, &value, sizeof(value)) <= 0) return 0;
	read(input, &next_pointer, sizeof(next_pointer));
	while (next_pointer > 0) {
		printf("%d ", value);
		lseek(input, next_pointer, SEEK_SET);
		read(input, &value, sizeof(value));
		read(input, &next_pointer, sizeof(next_pointer));
	}
	printf("%d", value);
	close(input);
	return 0;
}
