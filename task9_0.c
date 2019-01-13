#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int args, char* argv[]) {
	int input = open(argv[1], O_RDONLY);
	if (input < 0) {
		close(input);
		return 1;
	}
	int out_digits = open(argv[2], O_WRONLY | O_CREAT, 0640);
	int out_other = open(argv[3], O_WRONLY | O_CREAT, 0640);
	if (out_digits < 0 || out_other < 0) {
		close(input);
		close(out_digits);
		close(out_other);
		return 2;
	}
	ssize_t in_read, out_d_read, out_o_read;
	char in_byte;
	int out;
	while ((in_read = read(input, &in_byte, sizeof(in_byte))) > 0) {
		out = '0' <= in_byte && in_byte <= '9' ? out_digits : out_other;
		if (write(out, &in_byte, sizeof(in_byte)) < 0) {
			close(input);
			close(out_digits);
			close(out_other);
			return 3;
		}
	}
	if (in_read < 0) {
		close(input);
		close(out_digits);
		close(out_other);
		return 3;
	}
	return 0;
}
