#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <sys/stat.h>

void rec_dir(const char *name, int64_t* count) {
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(name))) return;
	while ((entry = readdir(dir)) != NULL) {
		char path[PATH_MAX];
		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
			rec_dir(path, count);
		}
		else if (entry->d_type == DT_REG) {
			int64_t tmp = *count;
			struct stat st;
			if (lstat(path, &st) != -1) tmp += st.st_size;
			*count = tmp;
		}
	}
}

int main(int argc, char* argv[]) {
	int64_t a = 0;
	rec_dir(argv[1], &a);
	printf("%"PRIu64"\n", a);
	return 0;
}
