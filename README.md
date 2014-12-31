avx1int
=======

AVX version 1 has some integer capabilities (XOR, AND, etc.) This class makes these features easier to use. I personally made use of this class when bitslicing a cipher on AWS. The AWS c3 nodes have AVX1 but no AVX2. However, for bitslicing the binary operators available in AVX1 are good enough: XOR, AND and OR.

Note that ANDNOT is also an operator in AVX and has the same latency & throughput as AND or NOT, but combines the two. It might save some operations to use it, though you would need to go thorugh the code by hand. Also note that GCC or clang will not understand what the intrisics do and so it will not perform e.g. de-morgan to simplify your equations as it would with normal integer operations. So take care to optimize them by hand/using some automated tool (constraint solver?).
