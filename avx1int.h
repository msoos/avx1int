#include <immintrin.h>
#define ALIGN __attribute__ ((aligned (32)))
#include <cassert>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdint.h>

inline __m256d get_value_tmp(uint64_t a0, uint64_t a1, uint64_t a2 , uint64_t a3)
{
	uint64_t ALIGN tmp_sliced[4];

	tmp_sliced[0] = a0;
	tmp_sliced[1] = a1;
	tmp_sliced[2] = a2;
	tmp_sliced[3] = a3;

	return _mm256_load_pd((double*)tmp_sliced);
}

struct AVX1Int {
	AVX1Int(){}

	bool any_bit_set() const {
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		return tmp_sliced[0] || tmp_sliced[1] || tmp_sliced[2] || tmp_sliced[3];
	}

	uint64_t get_64_at(const unsigned at) const {
		assert(at < 4);
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		return tmp_sliced[at];
	}

	std::string get_str_val() const {
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		std::stringstream ss;
		ss << std::hex << std::setfill('0')
		   << std::setw(16) << tmp_sliced[3]
		   << std::setw(16) << tmp_sliced[2]
		   << std::setw(16) << tmp_sliced[1]
		   << std::setw(16) << tmp_sliced[0];
		return ss.str();
	}

	bool bit_set(unsigned at) const {
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		if (at >= 64 * 3) {
			return (tmp_sliced[3] >> (at - 64 * 3)) & 1;
		} else if (at >= 64 * 2) {
			return (tmp_sliced[2] >> (at - 64 * 2)) & 1;
		} else if (at >= 64) {
			return (tmp_sliced[1] >> (at - 64)) & 1;
		} else {
			return (tmp_sliced[0] >> (at)) & 1;
		}
	}

	AVX1Int set_bit(const unsigned at) {
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		if (at >= 64 * 3) {
			tmp_sliced[3] |= 1ULL << (at - 64 * 3);
		} else if (at >= 64 * 2) {
			tmp_sliced[2] |= 1ULL << (at - 64 * 2);
		} else if (at >= 64) {
			tmp_sliced[1] |= 1ULL << (at - 64 * 1);
		} else {
			tmp_sliced[0] |= 1ULL << (at);
		}

		dat = _mm256_load_pd((double*)tmp_sliced);
		return *this;
	}

	void set_value(uint64_t a0, uint64_t a1, uint64_t a2 , uint64_t a3) {
		dat = get_value_tmp(a0, a1, a2, a3);
	}

	AVX1Int(uint64_t a0, uint64_t a1, uint64_t a2 , uint64_t a3) {
		set_value(a0, a1, a2, a3);
	}

	AVX1Int& operator^=(const AVX1Int& rhs) {
		dat = _mm256_xor_pd(dat, rhs.dat);
		return *this;
	}

	AVX1Int& operator&=(const AVX1Int& rhs) {
		dat = _mm256_and_pd(dat, rhs.dat);
		return *this;
	}

	AVX1Int& operator|=(const AVX1Int& rhs) {
		dat = _mm256_or_pd(dat, rhs.dat);
		return *this;
	}

	bool operator==(const AVX1Int& rhs) const {
		uint64_t ALIGN tmp_sliced[4];
		_mm256_store_pd((double*)tmp_sliced, dat);

		uint64_t ALIGN tmp_sliced2[4];
		_mm256_store_pd((double*)tmp_sliced2, rhs.dat);

		for(int i = 0; i < 4; i++) {
			if (tmp_sliced[i] != tmp_sliced2[i]) {
				return false;
			}
		}
		return true;
	}

	AVX1Int& operator=(const AVX1Int& rhs) {
		dat = rhs.dat;
		return *this;
	}

	const AVX1Int operator^(const AVX1Int& other) const {
		AVX1Int result;
		result.dat = _mm256_xor_pd(dat, other.dat);
		return result;
	}

	const AVX1Int operator&(const AVX1Int& other) const {
		AVX1Int result;
		result.dat = _mm256_and_pd(dat, other.dat);
		return result;
	}

	const AVX1Int operator|(const AVX1Int& other) const {
		AVX1Int result;
		result.dat = _mm256_or_pd(dat, other.dat);
		return result;
	}

	const AVX1Int operator~() const;

	__m256d dat;
};

static const AVX1Int AVX1Int_MAX(~0ULL, ~0ULL, ~0ULL, ~0ULL);
static const AVX1Int AVX1Int_MIN(0ULL, 0ULL, 0ULL, 0ULL);

const AVX1Int AVX1Int::operator~() const {
		AVX1Int result;
		result.dat = _mm256_xor_pd(dat, AVX1Int_MAX.dat);
		return result;
}

