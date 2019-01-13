#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const uint32_t max_size = 2000;

int cmp(const void *a, const void *b) {
	int *x = (int*)a;
	int *y = (int*)b;
	return *x - *y;
}

void extern_sort(char* filename, uint32_t* priority) {
	int input = open(filename, O_RDWR);
	uint32_t size = lseek(input, 0, SEEK_END) / sizeof(int);
	lseek(input, 0, SEEK_SET);
	if (size <= max_size) {
		int* buffer = (int*)malloc(size * sizeof(int));
		read(input, buffer, size * sizeof(int));
		lseek(input, 0, SEEK_SET);
		qsort(buffer, size, sizeof(int), cmp);
		write(input, buffer, size * sizeof(int));
		return;
	}
	int file1, file2;
	file1 = *priority;
	(*priority) += 1;
	file2 = *priority;
	(*priority) += 1;
	char name1[10];
	char name2[10];
	sprintf(name1, "tmp%d.txt", file1);
	sprintf(name2, "tmp%d.txt", file2);
	int tmp1 = open(name1, O_WRONLY | O_CREAT, 0640);
	int tmp2 = open(name2, O_WRONLY | O_CREAT, 0640);
	int x = 0;
	for (int a = 0; a < size / 2; a++) {
		read(input, &x, sizeof(int));
		write(tmp1, &x, sizeof(int));
	}
	while (read(input, &x, sizeof(int)) > 0) write(tmp2, &x, sizeof(int));
	close(tmp1);
	close(tmp2);
	extern_sort(name1, priority);
	extern_sort(name2, priority);
	tmp1 = open(name1, O_RDWR);
	tmp2 = open(name2, O_RDWR);
	lseek(input, 0, SEEK_SET);
	int k, m;
	while (read(tmp1, &k, sizeof(int)) > 0 && read(tmp2, &m, sizeof(int)) > 0) {
		if (k > m) {
			write(input, &m, sizeof(int));
			lseek(tmp1, -sizeof(int), SEEK_CUR);
		}
		else {
			write(input, &k, sizeof(int));
			lseek(tmp2, -sizeof(int), SEEK_CUR);
		}
	}
	while (read(tmp1, &k, sizeof(int)) > 0) write(input, &k, sizeof(int));
	while (read(tmp2, &m, sizeof(int)) > 0) write(input, &m, sizeof(int));
	close(tmp1);
	close(tmp2);
	close(input);
}

int main(int args, char* argv[]) {
	if (args == 1) return 0;
	int priority = 0;
	extern_sort(argv[1], &priority);
	return 0;
}
