#include <bits/stdc++.h>
using namespace std;

#define var long long
#define FOR(i, st, en) for (int i = st; i <= en; ++i)
#define FORD(i, st, en) for (int i = st; i >= en; --i)
#define REP(i, st, en) for (int i = st; i < en; ++i)
#define REPD(i, st, en) for (int i = st; i > en; --i)
#define bit(x, i) (((x)>>(i)) & 1)
#define reset(x, val) memset(x, val, sizeof(x))
#define dbg(...) cout<<"LINE("<<__LINE__<<") -> ["<<#__VA_ARGS__<<"]: [",DBG(__VA_ARGS__)
#define taskname ""
#define file                              \
	freopen(taskname".inp", "r", stdin); \
	freopen(taskname".out", "w", stdout)
#define default "in"
#define macro                     \
	freopen(default, "r", stdin);
#define maxn 1005
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

void DBG() { cout << "]" << "\n"; }
template<class H, class... T> void DBG(H h, T... t) {
    cout << to_string(h); if(sizeof...(t)) cout << ", "; DBG(t...);
}

const int inf = 1e9;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
int n, m, ox, oy;
char a[maxn][maxn];
int dist[maxn][maxn];
priority_queue<iii, vector<iii>, greater<iii>> heap;

inline bool inside(int i, int j) {
	if (i >= 1 && j >= 1 && i <= m && j <= n) return true;
	return false;
}
inline ii go(int i, int j) {
	switch (a[i][j]) {
		case 'L': return {i, j-1};
		case 'R': return {i, j+1};
		case 'U': return {i-1, j};
		case 'D': return {i+1, j};	
	}
	return {0, 0};
}
inline void _push(int i, int j, int val) {
	if (!inside(i, j) || val > dist[i][j]) return;
	dist[i][j] = val;
	heap.push({val, {i, j}});
}

void dijkstra() {
	dist[ox][oy] = 0;
	_push(ox, oy, 0);

	while (!heap.empty()) {
		int x = heap.top().second.first, y = heap.top().second.second;
		int cur_len = heap.top().first;
		heap.pop();

		if (cur_len != dist[x][y]) continue;

		if (a[x][y] == '.' || !cur_len) {
			REP(i, 0, 4) _push(x+dx[i], y+dy[i], cur_len+1);
		}
		else {
			ii tmp = go(x, y);
			_push(tmp.first, tmp.second, cur_len);
		}
	}
}

inline void dfs(int i, int j, int di, int dj) {
	while (inside(i, j)) {
		i += di; j += dj;
		if (a[i][j] == '.' || a[i][j] == 'S') dist[i][j] = -1;
		else if (a[i][j] == 'W' || a[i][j] == 'C') break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	file;

	cin >> m >> n;
	FOR(i, 1, m) FOR(j, 1, n) dist[i][j] = inf, cin >> a[i][j];

	FOR(i, 1, m) FOR(j, 1, n) {
		if (a[i][j] == 'S') ox = i, oy = j;
		else if (a[i][j] == 'W') dist[i][j] = -1;
		else if (a[i][j] == 'C') {
			dist[i][j] = -1;
			REP(k, 0, 4) dfs(i, j, dx[k], dy[k]);
		}
	}
	if (dist[ox][oy] == -1) {
		FOR(i, 1, m) FOR(j, 1, n) if (a[i][j] == '.')
			cout << -1 << endl;
		return 0;
	}
	dijkstra();

	FOR(i, 1, m) FOR(j, 1, n) if (a[i][j] == '.')
		if (dist[i][j] == inf) cout << -1 << endl;
		else cout << dist[i][j] << endl;
	return 0;
}
