#include <stdio.h>

int main() {
    int letters = 26;
    int digits = 10;
    long long int result = 0;
    long long int tmp = 0;
    int ch = 0;
    while(-1 != (ch = getchar())) {
        if (ch == '|') {
            result |= tmp;
            tmp = 0;
        }
        if (ch == '^') {
            result ^= tmp;
            tmp = 0;
        }
        if (ch == '&') {
            result &= tmp;
            tmp = 0;
        }
        if (ch == '~') {
            result = ~result;
        }
        if ('0' <= ch && '9' >= ch) {
            tmp |= (1ULL << (ch - '0'));
        } 
        if ('A' <= ch && 'Z' >= ch) {
            tmp |= (1ULL << (ch - 'A' + digits));
        }
        if ('a' <= ch && 'z' >= ch) {
            tmp |= (1ULL << (ch - 'a' + digits + letters));
        }
    }
    int res = '1';
    for (int i = 0; i < letters + letters + digits; i++) {
        if (i >= digits + letters && i < digits + letters + letters) {
            res = i - letters - digits + 'a';
        }
        if (i >= digits && i < digits + letters) {
            res = i - digits + 'A';
        }
        if (i < digits) {
            res = (i + '0');
        }
        if (((result >> i) & 1)) {
            printf("%c", res);
        }
    }
    return 0;
}
