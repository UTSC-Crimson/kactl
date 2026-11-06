// __int128 / unsigned __int128 (gnu++23, GCC 14):
// No literals: (__int128)1 << 100. Cast BEFORE multiplying:
// (__int128)a * b, not (__int128)(a * b).
// Print: println("{}", x). No cin >> x (use Python instead).
// Halves: (uint64_t)x, (uint64_t)(x >> 64).
// numeric_limits<__int128> works.
// Bits require unsigned: auto u = (unsigned __int128)x;
// __builtin_popcountg(u), __builtin_ctzg(u, 128),
// __builtin_clzg(u, 128) (2nd arg is returned when u == 0).
// __builtin_{add,sub,mul}_overflow(a, b, &r): true on
// overflow, r = wrapped result. Range is r's type.
// mul_overflow: two signed 32-bit inputs fit signed 64-bit.
// With 64-bit inputs (e.g. int macro), ll can overflow.
// Ordinary a * b still needs a cast BEFORE multiplication.
// Capped lcm:
// if (__builtin_mul_overflow(l / gcd(l, x), x, &l)) l = INF;
