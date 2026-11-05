// Needs C++20 (operator<=>): g++ -std=gnu++20 or later.
#include "../utilities/template.h"

#include "../../content/strings/DoubleHash.h"

mt19937 rng(5);
string rstr(int n, int alpha) {
	string s(n, 'a');
	for (char& c : s) c = char('a' + rng() % alpha);
	return s;
}

// Every pair of substrings: equal hashes <=> equal strings.
void allSubstrings(const string& s) {
	vector<Hs> pre{Hs()};
	for (unsigned char c : s) pre.push_back(pre.back() + c);
	map<Hs, string> seen;
	unordered_map<ll, string> byKey;
	rep(l,0,sz(s)) rep(r,l,sz(s)+1) {
		Hs h = pre[r] - pre[l];
		string t = s.substr(l, r - l);
		assert(h == Hs(t));
		auto [it, ins] = seen.emplace(h, t);
		assert(it->second == t);
		auto [it2, ins2] = byKey.emplace(h.key(), t);
		assert(it2->second == t);
	}
}

int main() {
	// concatenation, identity, associativity
	rep(it,0,20000) {
		string a = rstr(rng() % 8, 3), b = rstr(rng() % 8, 3), c = rstr(rng() % 8, 3);
		Hs A(a), B(b), C(c);
		assert(A + B == Hs(a + b));
		assert((A + B) + C == A + (B + C));
		assert(A + Hs() == A && Hs() + A == A);
		assert((Hs(a) == Hs(b)) == (a == b));
		if (!a.empty()) assert(Hs(a.substr(0, sz(a) - 1)) + a.back() == A);
		// a - b removes prefix b
		assert((A + B) - A == B && (A + B + C) - (A + B) == C);
		assert(A - A == Hs() && A - Hs() == A && (A + B) - A + C == B + C);
	}
	// power cache matches modpow
	auto mp = [](ll b, ll e, ll m) { ll r = 1; for (b %= m; e; e /= 2, b = b * b % m) if (e & 1) r = r * b % m; return r; };
	need(100000);
	for (int k : {0, 1, 2, 777, 99999, 100000}) assert(pw1[k] == mp(B1, k, M1) && pw2[k] == mp(B2, k, M2));
	{ string big = rstr(300000, 26); Hs H(big); assert(sz(pw1) > 1); // long concat grows cache
	  assert(H - Hs(big.substr(0, 123456)) == Hs(big.substr(123456))); }
	// '\0' must not vanish: same h, different length
	assert(!(Hs(string("\0a", 2)) == Hs("a")));
	assert(!(Hs(string(3, '\0')) == Hs(string(2, '\0'))));
	// chars >= 128 (signed char) are handled
	string hi = "\xff\x80z";
	assert(Hs(hi) - Hs(hi.substr(0, 1)) == Hs(hi.substr(1)) && Hs(hi).h1 >= 0);
	// substring hashes vs direct, collision-free over all substrings
	rep(it,0,30) allSubstrings(rstr(rng() % 150, 1 + rng() % 3));
	string tm(1 << 9, 'a'); // Thue-Morse: kills mod 2^64 hashing
	rep(i,0,sz(tm)) tm[i] = char('a' + __builtin_popcount(i) % 2);
	allSubstrings(tm);
	// segment tree of Hs with point updates
	rep(it,0,200) {
		int n = 1 + rng() % 40;
		string s = rstr(n, 2);
		int N = 1; while (N < n) N *= 2;
		vector<Hs> t(2 * N);
		auto upd = [&](int i, char c) {
			t[i += N] = Hs(c);
			for (i /= 2; i; i /= 2) t[i] = t[2*i] + t[2*i+1];
		};
		auto query = [&](int l, int r) { // [l, r), order-preserving
			Hs L, R;
			for (l += N, r += N; l < r; l /= 2, r /= 2) {
				if (l & 1) L = L + t[l++];
				if (r & 1) R = t[--r] + R;
			}
			return L + R;
		};
		rep(i,0,n) upd(i, s[i]);
		rep(q,0,200) {
			int i = rng() % n; s[i] = char('a' + rng() % 2); upd(i, s[i]);
			int l = rng() % (n + 1), r = rng() % (n + 1);
			if (l > r) swap(l, r);
			assert(query(l, r) == Hs(s.substr(l, r - l)));
		}
	}
	cout << "Tests passed!" << endl;
}
