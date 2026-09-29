#include "bits/stdc++.h"
using namespace std;

using ll = long long;
#define int ll
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)ssize(x)
using pii = pair<int, int>;
using vi = vector<int>;
ll cdiv(ll a, ll b) { return a/b+((a^b)>0&&a%b); }
ll fdiv(ll a, ll b) { return a/b-((a^b)<0&&a%b); }
template<class T> bool ckmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0; }

void solve(int testCase) {
    int n;
    cin >> n;
}

signed main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int numTests = 1;
    for (int i = 1; i <= numTests; i++) {
        solve(i);
    }
    return 0;
}
