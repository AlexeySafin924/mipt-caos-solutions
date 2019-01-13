#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	uint32_t N = strtol(argv[1], NULL, 10);
	for (uint32_t i = 1; i < N + 1; i++) {
		if (fork() ==  0) {
			if (i == N) printf("%d\n", i);
			else printf("%d ", i);
			exit(0);
		}
		wait(NULL);
	}
	return 0;
}
