#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
	char buffer[4000];
	char program[4000];
	fgets(buffer, sizeof(buffer), stdin);
	char* slash_pos = strchr(buffer, '\n');
	if (slash_pos) *slash_pos = '\0';
	if (strnlen(buffer, sizeof(buffer)) == 0) return 0;
	int file = open("tmp.c", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	snprintf(program, sizeof(program), "#include <stdio.h>\n int main() { int a = (%s); printf(\"%%d\", a); return 0; }", buffer);
	write(file, program, strnlen(program, sizeof(program)));
	close(file);
	pid_t p = fork();
	if (p == 0) { execlp("gcc", "gcc", "-o", "tmp", "tmp.c", NULL); return 0; }
	else { int status; waitpid(p, &status, 0); }
	p = fork();
	if (p == 0) { execlp("./tmp", "./tmp", NULL); return 0; }
	else { int status; waitpid(p, &status, 0); }
	remove("tmp");
	remove("tmp.c");
	return 0;
}
