#include <bits/stdc++.h>
using namespace std;

#define var long long
#define FOR(i, st, en) for (int i = st; i <= en; ++i)
#define FORD(i, st, en) for (int i = st; i >= en; --i)
#define REP(i, st, en) for (int i = st; i < en; ++i)
#define REPD(i, st, en) for (int i = st; i > en; --i)
#define FORS(i, s) for (int i = 0; i < s.size(); ++i)
#define taskname "covid19"
#define file                              \
	freopen(taskname".inp", "r", stdin); \
	freopen(taskname".out", "w", stdout)
#define maxn 1000005

typedef pair<int, int> ii;
int m, n, test, all;
vector<ii> g[maxn];
vector<ii> save[maxn];
int a[maxn], dist[maxn];
bool check[maxn];
const int dx[2] = {0, 1};
const int dy[2] = {1, 0};

inline int digit(int i, int j) {
    return (i-1)*n + j;
}

int dijkstra(int st, int en) {
    FOR(i, 1, all) dist[i] = INT_MAX;
    dist[st] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> heap;
    heap.push({dist[st], st});

    while (!heap.empty()) {
        int u = heap.top().second;
        int cur_len = heap.top().first;
        heap.pop();

        if (u == en) return dist[en];
        if (cur_len != dist[u]) continue;

        for (auto it : g[u]) {
            int v = it.second;
            int len = it.first;
            if (dist[v] > dist[u] + len) {
                dist[v] = dist[u] + len;
                heap.push({dist[v], v});
            }
        }
    }

    return dist[en];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
    //file;

    cin >> m >> n >> test;
    FOR(i, 1, m) FOR(j, 1, n) cin >> a[digit(i, j)];

    FOR(i, 1, m) FOR(j, 1, n) {
        FOR(x, 1, m) FOR(y, 1, n)
            if (!(i == x && j == y)) {
                if (i*j == a[digit(x, y)])
                    g[digit(x, y)].push_back({3, digit(i, j)});
            } 
    }

    FOR(i, 1, m) FOR(j, 1, n) {
        FOR(k, 0, 1) {
            int x = i+dx[k];
            int y = j+dy[k];

            if (x>=1 && x<=m && y>=1 && y<=n) {
                g[digit(i, j)].push_back({1, digit(x, y)});
                g[digit(x, y)].push_back({1, digit(i, j)});
            }
        }
    }

    all = m*n;
    while (test--) {
        int i, j, x, y;
        cin >> i >> j >> x >> y;
        cout << dijkstra(digit(i, j), digit(x, y)) << endl;
    }
	return 0;
}
