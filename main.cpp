#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 3005;
const int INF = 1e9;

struct Edge {
    int to, cap, flow;
};

vector<Edge> edges;
vector<int> g[MAXN];
int level[MAXN];
int iter[MAXN];
int n, m;

inline void addEdge(int from, int to, int cap) {
    g[from].push_back(edges.size());
    edges.push_back({to, cap, 0});
    g[to].push_back(edges.size());
    edges.push_back({from, cap, 0});
}

bool bfs(int s, int t) {
    memset(level, -1, (n + 1) * sizeof(int));
    queue<int> q;
    level[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int idx : g[v]) {
            Edge& e = edges[idx];
            if (level[e.to] < 0 && e.cap > e.flow) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }

    return level[t] >= 0;
}

int dfs(int v, int t, int f) {
    if (v == t) return f;

    for (int& i = iter[v]; i < (int)g[v].size(); i++) {
        int idx = g[v][i];
        Edge& e = edges[idx];
        if (level[v] < level[e.to] && e.cap > e.flow) {
            int d = dfs(e.to, t, min(f, e.cap - e.flow));
            if (d > 0) {
                e.flow += d;
                edges[idx ^ 1].flow -= d;
                return d;
            }
        }
    }

    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memset(iter, 0, (n + 1) * sizeof(int));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
    return flow;
}

inline void resetFlow() {
    int sz = edges.size();
    for (int i = 0; i < sz; i++) {
        edges[i].flow = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b, 1);
    }

    long long totalFlow = 0;

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            resetFlow();
            totalFlow += maxFlow(s, t);
        }
    }

    cout << totalFlow << endl;

    return 0;
}
