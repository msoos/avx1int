avx1int
=======

AVX version 1 has some integer capabilities (XOR, AND, etc.) This class makes these features easier to use. I personally made use of this class when bitslicing a cipher on AWS. The AWS c3 nodes have AVX1 but no AVX2. However, for bitslicing the binary operators available in AVX1 are good enough: XOR, AND and OR.
