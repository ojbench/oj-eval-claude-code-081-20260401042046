#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 3005;
const int MAXM = 10000;

int n, m;
int head[MAXN], nxt[MAXM], to[MAXM], cap[MAXM], ecnt;
int level[MAXN], cur[MAXN];

inline void addEdge(int u, int v, int c) {
    to[ecnt] = v; cap[ecnt] = c; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; cap[ecnt] = c; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = nxt[i]) {
            if (level[to[i]] < 0 && cap[i]) {
                level[to[i]] = level[u] + 1;
                q.push(to[i]);
            }
        }
    }
    return level[t] >= 0;
}

int dfs(int u, int t, int f) {
    if (u == t) return f;
    for (int& i = cur[u]; ~i; i = nxt[i]) {
        if (level[to[i]] == level[u] + 1 && cap[i]) {
            int d = dfs(to[i], t, min(f, cap[i]));
            if (d) {
                cap[i] -= d;
                cap[i ^ 1] += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        while (int f = dfs(s, t, 1e9)) {
            flow += f;
        }
    }
    return flow;
}

void resetCap(vector<int>& original) {
    for (int i = 0; i < ecnt; i++) {
        cap[i] = original[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(head, -1, sizeof(head));
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b, 1);
    }

    vector<int> originalCap(ecnt);
    for (int i = 0; i < ecnt; i++) {
        originalCap[i] = cap[i];
    }

    long long totalFlow = 0;

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            resetCap(originalCap);
            totalFlow += maxFlow(s, t);
        }
    }

    cout << totalFlow << endl;

    return 0;
}
