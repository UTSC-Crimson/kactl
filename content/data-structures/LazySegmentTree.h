/**
 * Author: Andrew Tam
 * Date: 2025-8-11
 * Description: Range addition, assignment and sum queries.
 * Indices are 1-based and ranges are inclusive.
 * Requires n > 0; vector input is a[1..n], ignoring a[0].
 * Empty ranges have sum 0 and updates do nothing.
 * Customize Data and Aux for other operations.
 * Usage: LazySegmentTree<Data, Aux> st(n);
 * st.update(l, r, Aux(x)); // add x to [l, r]
 * st.update(l, r, Aux(x, true)); // set [l, r] to x
 * st.query(l, r).v; // sum of [l, r]
 * Time: O(N) construction, O(\log N) per operation.
 * Status: stress-tested
 */
#pragma once

template<class Data, class Aux>
class LazySegmentTree {
	int n;
	vector<Data> t;
	vector<Aux> lz;
	void build(int L, int R, int v, const vector<Data>& a) {
		if (L == R) { t[v] = a[L]; return; }
		int M = (L + R) / 2;
		build(L, M, 2*v, a);
		build(M+1, R, 2*v+1, a);
		t[v] = Data::merge(t[2*v], t[2*v+1]);
	}
	void push(int v, int len) {
		lz[v].apply(t[2*v], lz[2*v], (len+1)/2);
		lz[v].apply(t[2*v+1], lz[2*v+1], len/2);
		lz[v] = Aux();
	}
	void update(int qL, int qR, const Aux& val,
			int L, int R, int v) {
		if (qL <= L && R <= qR) {
			val.apply(t[v], lz[v], R-L+1);
			return;
		}
		if (qR < L || R < qL) return;
		push(v, R-L+1);
		int M = (L + R) / 2;
		update(qL, qR, val, L, M, 2*v);
		update(qL, qR, val, M+1, R, 2*v+1);
		t[v] = Data::merge(t[2*v], t[2*v+1]);
	}
	Data query(int qL, int qR, int L, int R, int v) {
		if (qL <= L && R <= qR) return t[v];
		if (qR < L || R < qL) return Data();
		push(v, R-L+1);
		int M = (L + R) / 2;
		return Data::merge(query(qL, qR, L, M, 2*v),
			query(qL, qR, M+1, R, 2*v+1));
	}
public:
	LazySegmentTree(int n) : n(n), t(4*n), lz(4*n) {}
	LazySegmentTree(int n, const vector<Data>& a)
		: LazySegmentTree(n) { build(1, n, 1, a); }
	void update(int l, int r, const Aux& val) {
		update(l, r, val, 1, n, 1);
	}
	Data query(int l, int r) { return query(l, r, 1, n, 1); }
};

struct Data {
	int v;
	Data(int v = 0) : v(v) {}
	static Data merge(const Data& a, const Data& b) {
		return Data(a.v + b.v);
	}
};

struct Aux {
	int v;
	bool set;
	Aux(int v = 0, bool set = false) : v(v), set(set) {}
	void apply(Data& data, Aux& aux, int len) const {
		if (set) {
			data.v = len*v;
			aux = *this;
		} else {
			data.v += len*v;
			aux.v += v;
		}
	}
};
