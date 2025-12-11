#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    // read in strings, maintain adjacency matrix and reverse adjacency matrix
    map<string, vector<string>> adj;
    map<string, vector<string>> rev;

    // maintain total set of strings and indegrees
    set<string> tot;
    map<string,ll> ind;

    string line;
    while (getline(cin, line)) {
        string curr = "";
        vector<string> nodes;
        for (char c : line) {
            if (c == ' ') nodes.pb(curr);
            if (c == ' ') curr = "";
            if (c != ' ') curr.pb(c);
        }

        nodes.pb(curr);
        nodes[0] = nodes[0].substr(0, nodes[0].size()-1);
        for (int i = 1; i < nodes.size(); i++) {
            adj[nodes[0]].pb(nodes[i]);
            ind[nodes[i]]++;
            rev[nodes[i]].pb(nodes[0]);
        }
        tot.insert(nodes[0]);
    }

    // we assume this graph is a DAG, otherwise problem not well defined
    // perform a topological sort
    set<string> vis;
    queue<string> q;
    for (string x : tot) if (ind[x] == 0) q.push(x);

    vector<string> topo;
    while (q.size() > 0) {
        string top = q.front();
        q.pop();
        if (vis.count(top)) continue;
        vis.insert(top);
        topo.pb(top);

        for (string y : adj[top]) {
            ind[y]--;
            if (ind[y] == 0) q.push(y);
        }
    }

    // perform DP on topo order to obtain number of paths
    map<string, ll> dp;
    dp["you"] = 1;
    for (string x : topo) {
        for (string y : rev[x]) dp[x] += dp[y];
    }

    cout << dp["out"] << endl;
}