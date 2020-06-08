#include <bits/stdc++.h>
using namespace std;

#define FOR(i, st, en) for (int i=st;i<=en;++i)
#define FORD(i, st, en) for (int i=st;i>=en;--i)
#define REP(i, st, en) for (int i=st;i<en;++i)
#define REPD(i, st, en) for (int i=st;i>en;--i)
#define var long long
#define maxn 505
typedef pair<int, int> ii;

const int inf = 1e9;
int n, m, res;
int a[maxn], dist[maxn], e[maxn], t[maxn][maxn], c[maxn][maxn];
bool check[maxn];

int Try (int w) {
    FOR(i, 0, n+1) {
        dist[i] = inf; e[i] = 0; check[i] = true;
    }
    dist[1] = 0; e[1] = w;
    FOR(i, 1, n) {
        int u = 0;
        FOR(v, 1, n) if (check[v] == true) {
            if (u==0 || dist[u]>dist[v]) u = v;
        }

        if (u == 0) break;
        if (u == n) return dist[u];
        check[u] = false;

        FOR(v, 1, n) if (t[u][v] && e[u]-c[u][v]>=0) {
            if (dist[v] > dist[u]+t[u][v]) {
                dist[v] = dist[u]+t[u][v];
                e[v] = (a[v]) ? w : e[u]-c[u][v];
            }
            else if (dist[v] == dist[u]+t[u][v]) {
                e[v] = max(e[v], e[u]-c[u][v]);
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    freopen("in.txt", "r", stdin);

    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cin >> t[u][v] >> c[u][v];
        t[v][u] = t[u][v];
        c[v][u] = c[u][v];
    }

    int res = Try(inf);
    int left = 0, right = inf, mid = left+(right-left)/2;
    while (mid!=left && mid!=right) {
        if (Try(mid) == res) right=mid;
        else left=mid;
        mid = left+(right-left)/2;
    }

    cout << left << endl;
    return 0;
}
