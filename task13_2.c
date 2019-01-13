#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
	char tmp[4096];
	uint32_t counter = 0;
	while(1) {
		pid_t p = fork();
		if (p == 0) exit((scanf("%s", tmp) != EOF));
		else {
			int status;
                        waitpid(p, &status, 0);
			if (status == 0) break;
			counter += WEXITSTATUS(status);
		}
	}
	printf("%d", counter);
	return 0;
}
