#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

// visited set and adjacency lists
const int MN = 1000;
set<ll> vis;
vector<ll> adj [MN];

// dfs
void dfs(int k) {
    if (vis.count(k)) return;
    vis.insert(k);

    for (ll x : adj[k]) {
        dfs(x);
    }
}

int main() {
    // read in points
    vector<vector<ll>> points;
    string line;
    while (getline(cin, line)) {
        string curr = "";
        vector<ll> coords;
        for (char c : line) {
            if (c == ',') coords.pb(stoll(curr));
            if (c == ',') curr = "";
            if (c != ',') curr.pb(c);
        }
        coords.pb(stoll(curr));
        points.pb(coords);
    }

    int n = points.size();

    // compute edge list
    vector<pair<ll,pll>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll dist = 0;
            for (int k = 0; k < 3; k++) dist += (points[i][k] - points[j][k]) * (points[i][k] - points[j][k]);
            edges.pb({dist, {i,j}});
        }
    }

    // sort edges by weight
    sort(edges.begin(), edges.end());

    // binary search number of edges needed to connect graph
    ll low = 0;
    ll high = n*n;
    while (low < high) {
        ll mid = (low + high)/2;

        // recompute adjacency list
        for (int i = 0; i < mid; i++) {
            ll x = edges[i].second.first;
            ll y = edges[i].second.second;

            adj[x].pb(y);
            adj[y].pb(x);
        }

        // dfs first point
        dfs(0);

        // check if all visited
        if (vis.size() == n) {
            high = mid;
        } else {
            low = mid+1;
        }

        // reset visited set and adjacency lists
        vis.clear();
        for (int i = 0; i < n; i++) adj[i].clear();
    }

    // find points corresponding to final edge
    ll p1 = edges[low-1].second.first;
    ll p2 = edges[low-1].second.second;

    // compute product of x-coords
    ll val = points[p1][0] * points[p2][0];
    cout << val << endl;
}