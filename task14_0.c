#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	char buffer[4000];
	char program[4000];
	fgets(buffer, sizeof(buffer), stdin);
	char* slash = strchr(buffer, '\n');
	if (slash) *slash = '\0';
	if (strnlen(buffer, sizeof(buffer)) == 0) return 0;
	snprintf(program, sizeof(program), "ans = %s; print(ans)", buffer);
	execlp("python3", "python3", "-c", program, NULL);
	perror("failed to exec");
	return 1;
}
