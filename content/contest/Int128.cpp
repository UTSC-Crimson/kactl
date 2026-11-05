// Build gnu++23 (CMake default): -std=c++23 breaks abs(L),
// is_integral_v<L>, and <bit> functions on UL.
typedef __int128 L; typedef unsigned __int128 UL;
typedef unsigned long long ull;
// No 128-bit literals: (L)1 << 100. Cast BEFORE multiply:
// (L)a * b. Halves: (ull)x, (ull)(x >> 64). numeric_limits<L>
// works. Bits (GCC 14): __builtin_popcountg(x),
// __builtin_ctzg(x, 128), __builtin_clzg(x, 128): 128 if 0
// println("{}", x) and format work. No cin >> x, so:
L read() {
	string s; cin >> s; L x = 0; // negative: handles min()
	for (char c : s) if (c != '-') x = x * 10 - (c - '0');
	return s[0] == '-' ? x : -x;
}
ull modmul(ull a, ull b, ull m) { return (UL)a * b % m; }
// __builtin_{add,sub,mul}_overflow(a, b, &r): true on
// overflow, r = wrapped result. Range is r's type, so
// int * int into ll never overflows. e.g. capped lcm:
// if (__builtin_mul_overflow(l / gcd(l, x), x, &l)) l = INF;
