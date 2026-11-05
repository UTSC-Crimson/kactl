/**
 * Author: Evan Simanovskis
 * Date: 2026-11-05
 * License: CC0
 * Source: CLRS 14.3
 * Description: Set of closed intervals $[l, r]$; each node stores the max $r$
 * in its subtree. get\_overlap returns some interval intersecting $[l, r]$
 * (or t.end()), all\_overlaps returns all of them sorted. Point stab: $l = r = x$.
 * Insert/erase as a set; distinct ids allow equal intervals.
 * Usage: for (auto v : all_overlaps(t, l, r)) t.erase(v);
 * Time: $O(\log N)$, all\_overlaps $O((K+1) \log N)$ for $K$ hits
 * Status: stress-tested
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

struct Itvl {
	int l, r, id;
	auto operator<=>(const Itvl&) const = default;
	// operator<< is required by -D_GLIBCXX_DEBUG
	friend ostream& operator<<(ostream& o, const Itvl& v) {
		return o << v.l << ' ' << v.r << ' ' << v.id; }
};
template<class CIt, class It, class Cmp, class A>
struct itvl_update {
	typedef int metadata_type; // max r in subtree
	void operator()(It it, CIt end) {
		int mx = (*it)->r;
		for (auto c : {it.get_l_child(), it.get_r_child()})
			if (c != end) mx = max(mx, c.get_metadata());
		const_cast<int&>(it.get_metadata()) = mx;
	}
	virtual CIt node_begin() const = 0;
	virtual CIt node_end() const = 0;
};
typedef tree<Itvl, null_type, less<Itvl>, rb_tree_tag,
	itvl_update> itvl_tree;

itvl_tree::iterator get_overlap(itvl_tree& t, int l, int r) {
	auto it = t.node_begin(), end = t.node_end();
	while (it != end) {
		if ((*it)->l <= r && l <= (*it)->r) return *it;
		auto c = it.get_l_child();
		if (c != end && c.get_metadata() >= l) it = c;
		else it = it.get_r_child();
	}
	return t.end();
}
vector<Itvl> all_overlaps(itvl_tree& t, int l, int r) {
	vector<Itvl> res;
	auto end = t.node_end();
	auto go = [&](auto& go, auto it) -> void {
		if (it == end || it.get_metadata() < l) return;
		go(go, it.get_l_child());
		if ((*it)->l > r) return; // so does the right subtree
		if ((*it)->r >= l) res.push_back(**it);
		go(go, it.get_r_child());
	};
	go(go, t.node_begin());
	return res;
}
