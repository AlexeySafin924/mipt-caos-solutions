#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
	char file[PATH_MAX];
	struct stat st;
	char *nl;
	while (fgets(file, sizeof(file), stdin)) {
		nl = memchr(file, '\n', sizeof(file));
		if (nl) *nl = '\0';
		int exec = open(file, O_RDONLY);
		//if file exists, not empty, and marked as executable
		if (exec > 0 && fstat(exec, &st) != -1 && st.st_mode & S_IXUSR) {
			//if it to short(shorter then #!) it is invalid executable
			if (lseek(exec, 0, SEEK_END) < 2) {puts(file); continue; }
			lseek(exec, 0, SEEK_SET);
			char hash_sym = -1, exclamation_sym = -1;
			read(exec, &hash_sym, sizeof(char));
			read(exec, &exclamation_sym, sizeof(char));
			//if it is have #! header we check for path and is it content marked as executable
			if (hash_sym == '#' && exclamation_sym == '!') {
                char buffer[PATH_MAX];
                read(exec, buffer, sizeof(buffer));
                nl = memchr(buffer, '\n', sizeof(buffer));
                if (nl) *nl = '\0';
                struct stat interpreter;
                if (stat(buffer, &interpreter) == -1 || !(interpreter.st_mode & S_IXUSR)) puts(file);
            } else {
				//we check for ELF file
				lseek(exec, 0, SEEK_SET);
               	char del = -1, e = -1, l = -1, f = -1;
				read(exec, &del, sizeof(char));
				read(exec, &e, sizeof(char));
            	read(exec, &l, sizeof(char));
               	read(exec, &f, sizeof(char));
				if (del != 0x7f || e != 'E' || l != 'L' || f != 'F') puts(file);
			}
		}
	}
	return 0;
}
