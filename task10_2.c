#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main() {
	char file_name[PATH_MAX];
	struct stat st;
	char *nl, *nm;
	while (fgets(file_name, sizeof(file_name), stdin)) {
		nl = memchr(file_name, '\n', sizeof(file_name));
		if (nl) *nl = '\0';
		if (lstat(file_name, &st) != -1 && S_ISREG(st.st_mode)) {
			char link_name[PATH_MAX];
			strcpy(link_name, "link_to_");
			nm = basename(file_name);
			strcat(link_name, nm);
			symlink(file_name, link_name);
		}
		else if (lstat(file_name, &st) != -1 && S_ISLNK(st.st_mode)) {
			char path[PATH_MAX];
			char file[PATH_MAX];
			char tmp[PATH_MAX];
			ssize_t r = readlink(file_name, tmp, sizeof(tmp));
			tmp[r] = '\0';
			nm = dirname(file_name);
			strcpy(file, nm);
			strcat(file, "/");
			strcat(file, tmp);
			realpath(file, path);
			puts(path);
		}
	}
	return 0;
}
