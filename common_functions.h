#include <assert.h>

const unsigned long long FINAL = 1147797409030816545;
const int gameSIZE = 16;

inline unsigned char getDir(unsigned char first, unsigned char second) {
	int diff = second - first;
	switch (diff) {
	case 1: {
		return 'L';
		break;
	}
	case -1: {
		return 'R';
		break;
	}
	case 4: {
		return 'U';
		break;
	}
	case -4: {
		return 'D';
		break;
	}
	default: {
		assert(false);
	}
	}
}
