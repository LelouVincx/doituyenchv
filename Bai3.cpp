#include <bits/stdc++.h>
using namespace std;

#define var long long
#define FOR(i, st, en) for (int i = st; i <= en; ++i)
#define FORD(i, st, en) for (int i = st; i >= en; --i)
#define REP(i, st, en) for (int i = st; i < en; ++i)
#define REPD(i, st, en) for (int i = st; i > en; --i)
#define FORS(i, s) for (int i = 0; i < s.size(); ++i)
#define taskname "Bai3"
#define file                              \
	freopen(taskname".inp", "r", stdin); \
	freopen(taskname".out", "w", stdout)
#define maxn 100005
typedef pair<int, int> ii;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	//file;

	int test; cin >> test; while (test--) {
		int n; cin >> n;
		vector<int> a(n+1), lis(n+1, INT_MAX), x(n+1), g[n+1];
		vector<ii> last;
		set<int> res;
		int maxval = 0, prev = 0;
		FOR(i, 1, n) cin >> a[i];

		lis[0] = 0;
		FOR(i, 1, n) {
			int k = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
			lis[k] = a[i];
			maxval = max(maxval, k);
			x[a[i]] = k;

			if (prev != k) {
				prev = k;
				for (auto it : last) if (it.first < a[i])
					g[a[i]].push_back(it.first);
			}
			last.push_back({a[i], k});
		}
		FOR(i, 1, n) if (x[i] == maxval) {
			stack<int> st;
			st.push(i);
			while (!st.empty()) {
				int u = st.top();
				st.pop();
				res.insert(u);
				for (int v : g[u]) st.push(v);
			}
		}
		/*
		cout << maxval << endl;
		FOR(i, 1, n) cout << a[i] << " "; cout << endl;
		FOR(i, 1, n) cout << x[i] << " "; cout << endl;
		FOR(i, 1, n) cout << Next[i] << " "; cout << endl;
		*/

		cout << res.size() << endl;
		for (auto it=res.begin();it!=res.end();++it)
			if (*it) cout << *it << " ";
		cout << endl;
	}
	return 0;
}
