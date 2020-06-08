#include <bits/stdc++.h>
using namespace std;

#define var long long
#define FOR(i, st, en) for (int i = st; i <= en; ++i)
#define FORD(i, st, en) for (int i = st; i >= en; --i)
#define REP(i, st, en) for (int i = st; i < en; ++i)
#define REPD(i, st, en) for (int i = st; i > en; --i)
#define FORS(i, s) for (int i = 0; i < s.size(); ++i)
#define taskname ""
#define file                              \
	freopen(taskname".inp", "r", stdin); \
	freopen(taskname".out", "w", stdout)
#define maxn 21
typedef pair<int, int> ii;

const int inf = 10000;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
int m, n, res=inf, idx=1;
char a[maxn][maxn];
int c[maxn][maxn], dist[inf][maxn], num[maxn][maxn], pos[maxn][maxn];
bool check[inf][maxn];
ii dust[11];

bool inside(int x, int y) {
	if (x>=1 && x<=m && y>=1 && y<=n) return true;
	return false;
}

void bfs(int id, int u, int v) {
	queue<ii> st;
	st.push({u, v});
	while (!st.empty()) {
		int x = st.front().first;
		int y = st.front().second;
		st.pop();
		REP(i, 0, 4) {
			int tmpx = x+dx[i];
			int tmpy = y+dy[i];
			if (tmpx!=u || tmpy!=v) {
				if (inside(tmpx, tmpy) && num[tmpx][tmpy]==0) {
					num[tmpx][tmpy] = num[x][y]+1;
					if (a[tmpx][tmpy] != 'x') st.push({tmpx, tmpy});
					if (a[tmpx][tmpy] == '*') c[id][pos[tmpx][tmpy]] = num[tmpx][tmpy];
				}
			}
		}
	}
}

void init() {
	FOR(id, 1, idx) {
		memset(num, 0, sizeof(num));
		int x = dust[id].first;
		int y = dust[id].second;
		bfs(id, x, y);
	}
}

void loang() {
	REP(i, 1, 1<<idx) FOR(j, 1, idx) {
		dist[i][j] = inf;
		check[i][j] = false;
	}
	queue<ii> st;
	st.push({0, 0});
	check[0][0] = 1; dist[0][0] = 0;

	while (!st.empty()) {
		int u = st.front().first;
		int k = st.front().second;
		st.pop();

		FOR(i, 1, idx)
			if ((u&(1<<(i-1))) == 0) {
				int v = u|(1<<(i-1));
				dist[v][i] = min(dist[v][i], dist[u][k] + c[k][i]);
				if (check[v][i] == false) {
					st.push({v, i});
					check[v][i] = true;
				}
			}
	}
}

void reset() {
	res = inf; idx = 1;
	memset(a, 0, sizeof(a));
	memset(c, 0, sizeof(c));
	memset(dist, 0, sizeof(dist));
	memset(num, 0, sizeof(num));
	memset(pos, 0, sizeof(pos));
	memset(check, 0, sizeof(check));
	memset(dust, 0, sizeof(dust));
}

bool enter() {
	reset();
	if (n == 0 && m == 0) return false;
	FOR(i, 1, m) FOR(j, 1, n) {
		cin >> a[i][j];
		if (a[i][j] == 'o') dust[1].first = i, dust[1].second = j, pos[i][j] = 1;
		else if (a[i][j] == '*') dust[++idx] = {i, j}, pos[i][j] = idx;
	}
	
	if (dust[1].first==0 && dust[1].second==0) {
		cout << -1 << endl;
		return true;
	}
	init();

	// adding
	FOR(i, 2, idx) c[i][1] = c[1][i];
	
	// check
	FOR(i, 1, idx) FOR(j, 1, idx) {
		if (i == j) continue;
		if (c[i][j] == 0) {
			cout << -1 << endl;
			return true;
		}
	}

	loang();
	cout << dist[(1<<idx)-1][1] << endl;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);

	while (cin >> n >> m) {
		bool ok = enter();
		if (ok == false) break;
	}
	
	return 0;
}
