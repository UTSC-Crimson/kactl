/**
 * Author: Evan Simanovskis
 * Date: 2026-11-05
 * License: CC0
 * Source: own work
 * Description: Double polynomial hash mod $10^9+7$ and $10^9+9$ with fixed
 * bases. $a + b$ hashes the concatenation; $a - b$ removes prefix $b$ from $a$.
 * + is associative with identity Hs() (segment tree friendly). == also checks
 * length. Hs(c): one symbol, $c \geq 0$. Powers are cached on first use.
 * For palindromes, also hash the reversed string.
 * Usage: Hs a("ab"); // a + 'c' == Hs("abc"), Hs("abc") - a == 'c'
 * vector<Hs> pre{Hs()}; for (unsigned char c : s) pre.push_back(pre.back() + c);
 * pre[r] - pre[l] == Hs(s.substr(l, r - l));
 * Time: O(1) per operation (amortized)
 * Status: stress-tested
 */
#pragma once

const ll M1 = 1e9 + 7, M2 = 1e9 + 9;
const ll B1 = 911382323, B2 = 972663749;
vector<ll> pw1{1}, pw2{1};
void need(int n) { // cache B^0 .. B^n
	while (sz(pw1) <= n) pw1.push_back(pw1.back() * B1 % M1),
		pw2.push_back(pw2.back() * B2 % M2);
}
struct Hs {
	ll h1 = 0, h2 = 0; int len = 0;
	Hs() {}
	Hs(ll c) : h1(c % M1), h2(c % M2), len(1) {}
	Hs(ll a, ll b, int n) : h1(a), h2(b), len(n) {}
	Hs(const string& s) {
		for (unsigned char c : s) *this = *this + c; }
	Hs operator+(const Hs& o) const {
		need(o.len);
		return {(h1 * pw1[o.len] + o.h1) % M1,
			(h2 * pw2[o.len] + o.h2) % M2, len + o.len}; }
	Hs operator-(const Hs& b) const { // b must be a prefix
		int k = len - b.len; need(k);
		return {((h1 - b.h1 * pw1[k]) % M1 + M1) % M1,
			((h2 - b.h2 * pw2[k]) % M2 + M2) % M2, k}; }
	auto operator<=>(const Hs&) const = default;
	ll key() const { return h1 * M2 + h2; } // for unordered_map
};
