struct P { // aggregate: P{1, 2}, P{.x = 1, .y = 2}
	int x, y;
	// all 6 comparisons, member-wise in declaration order:
	auto operator<=>(const P&) const = default;
}; // v.emplace_back(1, 2) works (C++20); auto [x, y] = p;
// Only some fields / custom order: k(). A hand-written
// <=> does NOT give ==, so define it too (unique, ranges).
struct E {
	int u, v, w, id;
	auto k() const { return tuple(w, -u, v); } // -u: desc
	auto operator<=>(const E& o) const { return k() <=> o.k(); }
	bool operator==(const E& o) const { return k() == o.k(); }
};
// Comparators must be strict: <, never <= (sort can crash).
// sort(all(v), greater<>());          descending via <=>
// ranges::sort(v, {}, &E::w);         by one field
// ranges::sort(v, greater{}, &E::w);  by one field, desc
// sort(all(ix), [&](int a, int b) { return d[a] < d[b]; });
// Containers take a type; captureless lambdas work as-is:
auto cmp = [](const E& a, const E& b) { return a.w < b.w; };
set<E, decltype(cmp)> s; // equal w => treated as duplicate!
priority_queue<E, vector<E>, decltype(cmp)> pq; // top = max w
priority_queue<P, vector<P>, greater<>> mn; // min-heap
// Capturing lambda: set<int, decltype(f)> s2(f);
// unordered_map<P, int, H> needs == and a hash:
struct H { size_t operator()(const P& p) const {
	return hash<ll>()(p.x * ll(1e9 + 7) + p.y); } };
