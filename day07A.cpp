#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    // read in grid
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
    }

    // dimensions
    int n = grid.size();
    int m = grid[0].size();

    // find start coordinate
    int sx, sy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sx = i;
                sy = j;
            }
        }
    }

    // bfs down grid
    queue<pll> q;
    q.push({sx,sy});
    set<pll> visited;
    ll splits = 0;
    
    while (q.size() > 0) {
        pll top = q.front();
        ll x = top.first;
        ll y = top.second;

        q.pop();
        if (x < 0 || x >= n || y < 0 || y >= m) {
            continue;
        }

        if (visited.count({x,y})) continue;
        visited.insert({x,y});
        
        if (grid[x][y] != '^') {
            q.push({x+1,y});
        }

        if (grid[x][y] == '^') {
            splits++;
            q.push({x,y-1});
            q.push({x,y+1});
        }
    }

    cout << splits << endl;
}