#include <stdio.h>

int count_octets(int ch) {
	if ((ch >> 5) == 6) return 2;
	if ((ch >> 4) == 14) return 3;
	if ((ch >> 3) == 30) return 4;
	if ((ch >> 2) == 62) return 5;
	if ((ch >> 1) == 126) return 6;
	return 0;
}

int main() {
	int ascii = 0;
	int unicode = 0;
	int inp_char = 0;
	while ((inp_char = getchar()) != EOF) {
		if ((inp_char & (1 << 7)) == 0) ascii += 1;
		else {
			int next = 0;
			int count_okt = count_octets(inp_char);
			if (count_okt > 6 || count_okt < 2) {
				printf("%i %i", ascii, unicode);
				return 1;
			}
			for (int k = 1; k < count_okt; ++k) {
				if ((next = getchar()) == EOF || !((next >> 6) == 2)) {
					printf("%i %i", ascii, unicode);
					return 1;
				}
			}
			unicode += 1;
		}
	}
	printf("%i %i", ascii, unicode);
	return 0;
}