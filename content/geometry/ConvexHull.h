/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
With col = 1 they are kept, without duplicates (all collinear: sorted). col needs integer coordinates.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested (col: vs brute force), tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts, bool col = 0) {
	sort(all(pts));
	if (col) pts.erase(unique(all(pts)), pts.end());
	if (sz(pts) <= 1) return pts;
	vector<P> h(2 * sz(pts));
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) < !col) t--;
			h[t++] = p;
		}
	if (col) t = min(t, sz(pts)); // all collinear: sorted pts
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
