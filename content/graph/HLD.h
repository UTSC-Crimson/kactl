/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Path/subtree updates and queries on a nonempty
 * tree. Vertex IDs and input values are 0-based; internal pos
 * and segment-tree ranges are 1-based and inclusive.
 * adj is undirected (remove (*) for child-only lists).
 * v has one Data per vertex. With VALS\_EDGES, v[u] stores
 * the edge from par[u] to u; v[root] is ignored. Subtrees
 * exclude the edge to their parent. Data::merge must be
 * commutative. Queries return Data (sum in .v by default).
 * Usage: HLD<false> h(adj, vector<Data>(n), root);
 * h.modifyPath(u, v, Aux(x)); // add x along the path
 * h.modifySubtree(u, Aux(x, true)); // assign x in subtree
 * h.queryPath(u, v).v; // path sum
 * Time: O(N) construction, O(\log^2 N) path operations,
 * O(\log N) point/subtree operations.
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template<bool VALS_EDGES> struct HLD {
	int N, tim = 1;
	vector<vi> adj;
	vi par, siz, rt, pos, tail;
	LazySegmentTree<Data, Aux> tree;
	HLD(const vector<vi>& adj, const vector<Data>& v,
			int root = 0)
		: N(sz(adj)), adj(adj), par(N, -1), siz(N, 1),
		  rt(N, root), pos(N), tail(N, -1),
		  tree(N, init(v, root)) {}
	vector<Data> init(const vector<Data>& v, int root) {
		dfsSz(root); dfsHld(root);
		vector<Data> a(N+1);
		rep(i,0,N) a[pos[i]] = v[i];
		if (VALS_EDGES) a[pos[root]] = Data();
		return a;
	}
	void dfsSz(int v) {
		for (int& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v)); // (*)
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++, tail[v] = v;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
			if (u == adj[v][0]) tail[v] = tail[u];
		}
	}
	template<class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v]);
		}
		op(pos[u] + VALS_EDGES, pos[v]);
	}
	Data get(int u) { return tree.query(pos[u], pos[u]); }
	void modifyPath(int u, int v, const Aux& val) {
		process(u, v, [&](int l, int r) {
			tree.update(l, r, val);
		});
	}
	void modifySubtree(int v, const Aux& val) {
		tree.update(pos[v] + VALS_EDGES, pos[v]+siz[v]-1, val);
	}
	Data queryPath(int u, int v) {
		Data res;
		process(u, v, [&](int l, int r) {
			res = Data::merge(res, tree.query(l, r));
		});
		return res;
	}
	Data querySubtree(int v) {
		return tree.query(pos[v] + VALS_EDGES, pos[v]+siz[v]-1);
	}
};
