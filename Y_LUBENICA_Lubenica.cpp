#include <bits/stdc++.h>
using namespace std;

#define var long long int
#define FOR(i, st, en) for (int i = st, _en = (en); i <= _en; ++i)
#define REP(i, st, en) for (int i = st, _en = (en); i < _en; ++i)
#define FORD(i, st, en) for (int i = st, _en = (en); i >= _en; --i)
#define REPD(i, st, en) for (int i = st, _en = (en); i > _en; --i)
#define getmask(n) (1LL << (n))
#define bit(x, i) (((x)>>(i)) & 1LL)
#define taskname ""
#define file                              \
	freopen(taskname".INP", "r", stdin); \
	freopen(taskname".OUT", "w", stdout)
#define maxn 100005
#define log 17
typedef pair<var, int> ii;
const int inf = 1e9;
const var mod = 1e9+7;
inline bool minimize(var &x, var y) {
	if (x > y) {x = y; return true;}
	return false;
}
inline bool maximize(var &x, var y) {
	if (x < y) {x = y; return true;}
	return false;
}
// ----------------------------------------------------------------------------------------

int n;
vector<int> adj[maxn];
vector<int> cost[maxn];
int par[maxn][log+1];
int mn[maxn][log+1];
int mx[maxn][log+1];

struct LowestCommonAncestor {
    int depth[maxn];

public:
    LowestCommonAncestor(int u) {
        depth[u] = 1;
        par[u][0] = -1;
        dfs(u, -1);
        FOR(j, 1, log) {
           FOR(i, 1, n) {
               int x = par[i][j-1];
               if (x < 0) {
                   par[i][j] = -1;
                   mn[i][j] = inf;
                   mx[i][j] = 0;
               }
               else {
                   par[i][j] = par[x][j-1];
                   mn[i][j] = min(mn[i][j-1], mn[x][j-1]);
                   mx[i][j] = max(mx[i][j-1], mx[x][j-1]);
               }
           } 
        }
    }

    pair<int, int> get(int u, int v) {
        pair<int, int> res = {inf, 0};
        if (u == v) return res;
        if (depth[v] > depth[u]) swap(u, v);
        FORD(i, log, 0) {
            int x = par[u][i];
            if (x < 0) continue;
            if (depth[x] >= depth[v]) {
                res.first = min(res.first, mn[u][i]);
                res.second = max(res.second, mx[u][i]);
                u = x;
            }
        }
        if (u == v) return res;
        FORD(i, log, 0) {
            int x = par[u][i];
            int y = par[v][i];
            if (x != y) {
                res.first = min(res.first, min(mn[u][i], mn[v][i]));
                res.second = max(res.second, max(mx[u][i], mx[v][i]));
                u = par[u][i]; v = par[v][i];
            }
        }
        res.first = min(res.first, min(mn[u][0], mn[v][0]));
        res.second = max(res.second, max(mx[u][0], mx[v][0]));
        return res;
    }

private:
    void dfs(int u, int paru) {
        REP(i, 0, (int)adj[u].size()) {
            int v = adj[u][i];
            if (v == paru) continue;
            int c = cost[u][i];

            par[v][0] = u;
            depth[v] = depth[u]+1;
            mn[v][0] = c;
            mx[v][0] = c;
            dfs(v, u);
        }
    }
};

void test_case() {
    cin >> n;
    FOR(_, 1, n-1) {
        int u, v; var c;
        cin >> u >> v >> c;
        adj[u].push_back(v); cost[u].push_back(c);
        adj[v].push_back(u); cost[v].push_back(c);
    }

    LowestCommonAncestor lca(1);

    int query; cin >> query;
    while (query--) {
        int u, v;
        cin >> u >> v;
        pair<int, int> res = lca.get(u, v);
        cout << res.first << " " << res.second << endl;
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	// file;

	int test = 1;
	// cin >> test;
	while (test--) test_case();
	return 0;
}
