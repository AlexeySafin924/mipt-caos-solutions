uint16_t satsum(uint16_t x, uint16_t y) {
	uint16_t sum = x + y;
	if (sum < x) {
		return (uint16_t)(-1);
	}
	return sum;
}
