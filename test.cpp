#include <iostream>
#include "avx1int.h"
#include <assert.h>

int main()
{
	assert(AVX1Int_MIN.get_str_val() == "0000000000000000000000000000000000000000000000000000000000000000");
	assert(AVX1Int_MAX.get_str_val() == "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

	AVX1Int a(0,0,0,0);
	a.set_bit(0);
	assert(a.bit_set(0) == true);
	assert(a.bit_set(1) == false);

	AVX1Int b(0,0,0,0);
	b.set_bit(128);
	assert(b.bit_set(128) == true);
	assert(b.bit_set(129) == false);

	AVX1Int c(0,0,0,0);
	c.set_bit(255);
	assert(c.bit_set(255) == true);
	assert(c.bit_set(254) == false);
	assert(c.bit_set(0)   == false);

	AVX1Int d1(0,0,0,0);
	d1.set_bit(1);
	AVX1Int d2(0,0,0,0);
	d2.set_bit(1);
	d1 ^= d2;
	assert(d1.bit_set(0) == false);
	assert(d1.bit_set(255) == false);
	assert(d1.bit_set(254) == false);
	assert(d1.bit_set(1)   == false);

	AVX1Int e1(0,0,0,0);
	e1.set_bit(1);
	AVX1Int e2(0,0,0,0);
	e2.set_bit(0);
	e1 &= e2;
	assert(e1.bit_set(255) == false);
	assert(e1.bit_set(254) == false);
	assert(e1.bit_set(1)   == false);
	assert(e1.bit_set(0)   == false);

	AVX1Int f1(0,0,0,0);
	f1.set_bit(1);
	AVX1Int f2(0,0,0,0);
	f2.set_bit(0);
	f1 |= f2;
	assert(f1.bit_set(255) == false);
	assert(f1.bit_set(254) == false);
	assert(f1.bit_set(0)   == true);
	assert(f1.bit_set(1)   == true);

	assert(~AVX1Int_MIN == AVX1Int_MAX);

	std::cout << "All test passed." << std::endl;
	return 0;
}