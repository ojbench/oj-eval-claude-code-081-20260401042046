#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 3005;

int n, m;
vector<int> adj[MAXN];

// Fast BFS-based max flow for unit capacity graphs
int maxFlow(int s, int t) {
    if (s == t) return 0;

    int totalFlow = 0;
    vector<vector<bool>> used(n + 1, vector<bool>(n + 1, false));

    // Find at most 3 edge-disjoint paths (since max degree is 3)
    for (int iter = 0; iter < 3; iter++) {
        vector<int> parent(n + 1, -1);
        queue<int> q;
        q.push(s);
        parent[s] = s;

        bool found = false;
        while (!q.empty() && !found) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (parent[v] == -1) {
                    // Check if edge u->v is available
                    int mn = min(u, v), mx = max(u, v);
                    if (!used[mn][mx]) {
                        parent[v] = u;
                        if (v == t) {
                            found = true;
                            break;
                        }
                        q.push(v);
                    }
                }
            }
        }

        if (!found) break;

        // Mark edges on path as used
        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            int mn = min(prev, curr), mx = max(prev, curr);
            used[mn][mx] = true;
            curr = prev;
        }

        totalFlow++;
    }

    return totalFlow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    long long totalFlow = 0;

    for (int s = 1; s <= n; s++) {
        for (int t = s + 1; t <= n; t++) {
            int flow = maxFlow(s, t);
            totalFlow += flow;
        }
    }

    cout << totalFlow << endl;

    return 0;
}
