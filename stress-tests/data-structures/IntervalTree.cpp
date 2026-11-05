// Needs C++20 (operator<=>): g++ -std=gnu++20 or later.
#include "../utilities/template.h"

#include "../../content/data-structures/IntervalTree.h"

mt19937 rng(42);
int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

// recompute subtree max r, check stored metadata matches
int check(itvl_tree::node_const_iterator it, itvl_tree::node_const_iterator end) {
	if (it == end) return INT_MIN;
	int mx = max({(*it)->r, check(it.get_l_child(), end), check(it.get_r_child(), end)});
	assert(it.get_metadata() == mx);
	return mx;
}

int main() {
	rep(test,0,3000) {
		itvl_tree t;
		set<Itvl> ref;
		int C = rnd(1, 3) == 1 ? 10 : rnd(1, 2) == 1 ? 100 : 1e9, ids = rnd(1, 5), Q = rnd(1, 200);
		rep(q,0,Q) {
			int op = rnd(0, 9), l = rnd(-C, C), r = rnd(-C, C);
			if (l > r) swap(l, r);
			if (op < 4) {
				Itvl v{l, r, rnd(0, ids)};
				assert(t.insert(v).second == ref.insert(v).second);
			} else if (op < 6 && !ref.empty()) {
				Itvl v = *next(ref.begin(), rnd(0, sz(ref) - 1));
				if (rnd(0, 3) == 0) v.id = rnd(0, ids); // maybe absent
				assert(t.erase(v) == ref.erase(v));
			} else if (op == 6) { // erase everything overlapping [l, r]
				for (auto v : all_overlaps(t, l, r)) assert(t.erase(v) && ref.erase(v));
				for (auto& v : ref) assert(!(v.l <= r && l <= v.r));
			}
			vector<Itvl> want;
			for (auto& v : ref) if (v.l <= r && l <= v.r) want.push_back(v);
			auto it = get_overlap(t, l, r);
			if (want.empty()) assert(it == t.end());
			else assert(it != t.end() && it->l <= r && l <= it->r && ref.count(*it));
			assert(all_overlaps(t, l, r) == want);
			int x = rnd(-C, C); // point stab
			bool any = false;
			for (auto& v : ref) any |= v.l <= x && x <= v.r;
			assert((get_overlap(t, x, x) != t.end()) == any);
			assert(sz(t) == sz(ref) && equal(all(t), all(ref)));
			check(t.node_begin(), t.node_end());
		}
	}
	cout << "Tests passed!" << endl;
}
