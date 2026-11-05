// __int128 / unsigned __int128 (gnu++23, GCC 14):
// No literals: (__int128)1 << 100. Cast BEFORE multiplying:
// (__int128)a * b, not (__int128)(a * b).
// Print: println("{}", x). No cin >> x (use Python instead).
// Halves: (uint64_t)x, (uint64_t)(x >> 64).
// numeric_limits<__int128> works.
// Bits: __builtin_popcountg(x), __builtin_ctzg(x, 128),
// __builtin_clzg(x, 128) (2nd arg is returned when x == 0).
// __builtin_{add,sub,mul}_overflow(a, b, &r): true on
// overflow, r = wrapped result. Range is r's type, so
// int * int into ll never overflows. e.g. capped lcm:
// if (__builtin_mul_overflow(l / gcd(l, x), x, &l)) l = INF;
