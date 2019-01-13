#include <stdio.h>
#include <xmmintrin.h>
#include <smmintrin.h>

int main() {
	int m, n;
	scanf("%u%u", &m, &n);
	float* a = (float*)malloc(m * n * sizeof(float));
	float* b = (float*)malloc(m * n * sizeof(float));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%f", &a[i * n + j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%f", &b[j * n + i]);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			__m128 tmp = _mm_set_ss(0);
			int z = 0;
			while (z < n - 3) {
				__m128 a_v = _mm_loadu_ps(a + i * n + z);
				__m128 b_v = _mm_loadu_ps(b + j * n + z);
				tmp = _mm_add_ss(tmp, _mm_dp_ps(a_v, b_v, 0b11110001));
				z += 4;
			}
			float s = _mm_cvtss_f32(tmp);
			while (z < n) {
				s += a[i * n + z] * b[j * n + z];
				z++;
			}
			printf("%.4f ",s);
		}
		printf("\n");
	}
	free(a);
	free(b);
	return 0;
}
