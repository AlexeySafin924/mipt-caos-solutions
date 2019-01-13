#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void add(char* location, unsigned number, unsigned W) {
	char a = location[W];
	sprintf(location, "%*d", W, number);
	location[W] = a;
}

void fill_rec(unsigned W, unsigned N, unsigned n, unsigned offset, unsigned x, char* data) {
	if (n == 1) {
		add(data + W * (N * offset + offset) + offset, x, W);
	}
	else if (n == 2) {
		add(data + W * (N * offset + offset) + offset, x, W);
		add(data + W * (N * offset + offset + 1) + offset, x + 1, W);
		add(data + W * (N * (offset + 1) + offset + 1) + 1 + offset, x + 2, W);
		add(data + W * (N * (offset + 1) + offset) + 1 + offset, x + 3, W);
	}
	else {
		for (int i = 0; i < n; i++) {
			add(data + W * (N * offset + offset + i) + offset, x + i, W);
		}
		for (int i = 0; i < n - 2; i++) {
			add(data + W * (N * (offset + 1 + i) + offset + n - 1) + 1 + i + offset, x + n + i, W);
		}
		for (int i = 0; i < n; i++) {
			add(data + W * (N * (offset + n - 1) + offset + i) + n - 1 + offset, x + 3 * (n - 1) - i, W);
		}
		for (int i = 0; i < n - 2; i++) {
			add(data + W * (N * (offset + 1 + i) + offset) + 1 + i + offset, x + 4 *(n - 1) - 1 - i, W);
		}
		fill_rec(W, N, n - 2, offset + 1, x + 4 * (n - 1), data);
	}
}

void fill(unsigned N, unsigned W, char* data) {
	fill_rec(W, N, N, 0, 1, data);
	for (int i = 0; i < N; i++) data[W * (N * i + N) + i] = '\n';
}

int main(int argc, char *argv[]) {
	unsigned W = strtol(argv[3], NULL, 10);
	unsigned N = strtol(argv[2], NULL, 10);
	int fd = open(argv[1], O_RDWR | O_CREAT, 0640);
	ftruncate(fd, N * N * W + N);
	char *contents = mmap(NULL, N * N * W + N, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	fill(N, W, contents);
	msync(contents, N * N * W + N, MS_SYNC);
	munmap(contents, N * N * W + N);
	close(fd);
	return 0;
}
