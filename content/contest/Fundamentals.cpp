const ll mod = 1e9 + 7, LIM = 2e6 + 1; // LIM <= mod, mod prime
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
ll fac[LIM], ifac[LIM], inv[LIM], lp[LIM], mu[LIM], phi[LIM];
vi pr; // lp[i] = smallest prime factor of i
void init() { // call once at start
	inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	rep(i,2,LIM) {
		inv[i] = mod - mod / i * inv[mod % i] % mod;
		fac[i] = fac[i-1] * i % mod;
		ifac[i] = ifac[i-1] * inv[i] % mod;
	}
	// linear sieve; uncomment for mobius (mu) and totient (phi)
	// mu[1] = phi[1] = 1;
	rep(i,2,LIM) {
		if (!lp[i]) {
			lp[i] = i, pr.push_back(i);
			// mu[i] = -1, phi[i] = i - 1;
		}
		for (ll p : pr) {
			if (i * p >= LIM) break;
			lp[i * p] = p;
			if (i % p == 0) {
				// mu[i * p] = 0, phi[i * p] = phi[i] * p;
				break;
			}
			// mu[i * p] = -mu[i], phi[i * p] = phi[i] * (p - 1);
		}
	}
}
ll perm(ll n, ll k) { // ordered k of n, 0 if k < 0 or k > n
	if (k < 0 || k > n) return 0;
	assert(n < LIM);
	return fac[n] * ifac[n-k] % mod;
}
ll comb(ll n, ll k) { // n choose k
	return k < 0 || k > n ? 0 : perm(n, k) * ifac[k] % mod; }
// # of solutions to x_1 + ... + x_k = n with all x_i >= 0
ll starsAndBars(ll n, ll k) {
	if (k == 0) return n == 0;
	return comb(n + k - 1, k - 1);
}
ll catalan(ll n) {
	return n < 0 ? 0 : comb(2 * n, n) * inv[n + 1] % mod; }
