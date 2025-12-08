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

    // add 1000 smallest weight edges to adjacency
    for (int i = 0; i < 1000; i++) {
        ll x = edges[i].second.first;
        ll y = edges[i].second.second;

        adj[x].pb(y);
        adj[y].pb(x);
    }

    // dfs all, compute sizes of connected components (circuit sizes)
    vector<ll> circuits;
    ll prev = 0;
    for (int i = 0; i < n; i++) {
        if (vis.count(i) == 0) dfs(i);
        circuits.pb(vis.size() - prev);
        prev = vis.size();
    }

    // output product of three largest
    sort(circuits.begin(), circuits.end(), greater<ll>());
    ll val = circuits[0] * circuits[1] * circuits[2];
    cout << val << endl;
}