#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int counter = 1;
	pid_t pid;
	do {
		pid = fork();
		if (-1 != pid) {
			counter++;
		}
	} while (0 == pid);
	if (pid > 0) {
		int status;
		waitpid(pid, &status, 0);
	}
	else if (-1 == pid) {
		printf("%d\n", counter);
	}
	return 0;
}
