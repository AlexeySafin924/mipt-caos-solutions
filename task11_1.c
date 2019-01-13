#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>

int main() {
	char first[18];
	char second[18];
	fgets(first, sizeof(first), stdin);
	struct tm time1, time2;
	memset(&time1, 0, sizeof(struct tm));
	strptime(first, "%Y-%m-%d %H:%M", &time1);
	time1.tm_isdst = -1;
	time_t t1 = mktime(&time1);
	while (fgets(second, sizeof(second), stdin)) {
		memset(&time2, 0, sizeof(struct tm));
		time2.tm_isdst = -1;
		strptime(second, "%Y-%m-%d %H:%M", &time2);
		time_t t2 = mktime(&time2);
		printf("%ld\n", (long int)difftime(t2, t1) / 60);
		t1 = t2;
	}
	return 0;
}
