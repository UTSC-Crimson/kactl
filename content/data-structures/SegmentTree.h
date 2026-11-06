/**
 * Author: Andrew Tam
 * Date: 2025-8-11
 * Description: Point assignment and range minimum queries.
 * Indices are 1-based and ranges are inclusive.
 * Requires n > 0; vector input is a[1..n], ignoring a[0].
 * Unset elements and empty ranges return inf.
 * Customize Data for other associative operations.
 * Usage: SegmentTree<Data> st(n);
 * st.update(i, Data(x)); // assign a[i] = x
 * st.query(l, r).v; // minimum of [l, r]
 * Time: O(N) construction, O(\log N) per operation.
 * Status: stress-tested
 */
#pragma once

const int inf = numeric_limits<int>::max();

template<class Data>
class SegmentTree {
	int n;
	vector<Data> t;
	void build(int L, int R, int v, const vector<Data>& a) {
		if (L == R) { t[v] = a[L]; return; }
		int M = (L + R) / 2;
		build(L, M, 2*v, a);
		build(M+1, R, 2*v+1, a);
		t[v] = Data::merge(t[2*v], t[2*v+1]);
	}
	void update(int qI, const Data& val,
			int L, int R, int v) {
		if (L == R) { t[v] = val; return; }
		int M = (L + R) / 2;
		if (qI <= M) update(qI, val, L, M, 2*v);
		else update(qI, val, M+1, R, 2*v+1);
		t[v] = Data::merge(t[2*v], t[2*v+1]);
	}
	Data query(int qL, int qR, int L, int R, int v) {
		if (qL <= L && R <= qR) return t[v];
		if (qR < L || R < qL) return Data();
		int M = (L + R) / 2;
		return Data::merge(query(qL, qR, L, M, 2*v),
			query(qL, qR, M+1, R, 2*v+1));
	}
public:
	SegmentTree(int n) : n(n), t(4*n) {}
	SegmentTree(int n, const vector<Data>& a)
		: SegmentTree(n) { build(1, n, 1, a); }
	void update(int i, const Data& val) {
		update(i, val, 1, n, 1);
	}
	Data query(int l, int r) { return query(l, r, 1, n, 1); }
};

struct Data {
	int v;
	Data(int v = inf) : v(v) {}
	static Data merge(const Data& a, const Data& b) {
		return Data(min(a.v, b.v));
	}
};
