#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"

namespace old { // original KACTL hull (strict, collinear points dropped)
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
}

// Walk the strict hull's edges, collecting input points on each edge in order.
vector<P> brute(vector<P> pts) {
	sort(all(pts));
	pts.erase(unique(all(pts)), pts.end());
	auto H = old::convexHull(pts);
	if (sz(H) <= 1) return H;
	if (sz(H) == 2) return pts; // all collinear -> sorted
	vector<P> res;
	rep(i,0,sz(H)) {
		P a = H[i], b = H[(i+1) % sz(H)];
		vector<P> on;
		for (P p : pts)
			if (!(p == b) && a.cross(b, p) == 0 && (p-a).dot(p-b) <= 0) on.push_back(p);
		sort(all(on), [&](P x, P y) { return (x-a).dist2() < (y-a).dist2(); });
		res.insert(res.end(), all(on));
	}
	return res;
}

int main() {
	for (int GRID : {2, 3, 5, 10, 1000})
	for (int SZ : {0, 1, 2, 3, 4, 6, 10, 30})
	rep(it,0,20000) {
		vector<P> pts(SZ);
		int mode = rand() % 3;
		rep(i,0,SZ) {
			ll k = rand() % GRID;
			if (mode == 0) pts[i] = P(k, rand() % GRID);
			else if (mode == 1) pts[i] = P(k, 2*k); // all collinear
			else pts[i] = P(k, rand() % 2 ? 0 : k); // two lines
		}
		assert(convexHull(pts, 1) == brute(pts));
		assert(convexHull(pts) == old::convexHull(pts));
	}
	cout << "Tests passed!" << endl;
}
