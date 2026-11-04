/**
 * Author: UTSC Duo Push
 * Date: 2026-11-04
 * License: CC0
 * Source: https://en.cppreference.com/w/cpp/utility/bitset
 * Description: Bitset reference. N is fixed at compile time; whole-set
 * operations cost O(N/64). Declare big bitsets globally.
 */
#pragma once

const int N = 1e5 + 1;
bitset<N> b, c;
void bitsetReference(int i, int k, ll x, string s) {
	b[i];            // bit i, no bounds check
	b.test(i);       // bit i, throws if i >= N
	b.set();         // all N bits to 1
	b.set(i);        // bit i to 1
	b.set(i, x);     // set bit i to x
	b.reset();       // all N bits to 0
	b.reset(i);      // bit i to 0
	b.flip();        // flip ALL N bits (same as b = ~b)
	b.flip(i);       // flip bit i
	b.count();       // number of 1 bits
	b.size();        // N
	b.any();         // some bit is 1
	b.none();        // no bit is 1
	// b.all() is broken by the all(x) macro: use b.count() == N
	b._Find_first(); // lowest 1 bit, N if none
	b._Find_next(i); // lowest 1 bit > i, N if none
	// no _Find_last: scan down from N - 1, or store reversed
	b & c, b | c, b ^ c, ~b; // also &=, |=, ^=
	b << k;          // bit j -> j + k, bits past N - 1 dropped
	b >> k;          // bit j -> j - k, also <<=, >>=
	b == c, b != c;  // compare
	b.to_string();   // char 0 is bit N - 1 (reversed!)
	cin >> b, cout << b; // read / print like to_string()
	b.to_ullong();   // throws if a bit >= 64 is set
	bitset<N> bx(x); // bits of x
	bitset<N> bs(s); // s = "0101": bits 0, 2 set (s reversed)
	// unordered_set<bitset<N>> works (std::hash is defined)
	// If only bits [0, n) are used, ~ and flip() also set bits
	// [n, N). Mask with low = ~bitset<N>() >> (N - n)
	// before count(), any() or _Find_first().
	// count() is ~3x faster with #pragma GCC target("popcnt")
	// at the top of the file. Judges discourage pragmas
}
