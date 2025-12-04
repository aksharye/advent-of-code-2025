#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    ll rolls = 0;

    // read in grid
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        grid.pb(line);
    }

    // dimensions of grid
    int n = grid.size();
    int m = grid[0].size();

    // direction vectors for 8 adjacent tiles
    int dx [] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy [] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // loop through tiles in grid
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            // enumerate adjacent rolls
            int adj_rolls = 0;
            for (int k = 0; k < 8; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                // boundary check, then check tile
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (grid[nx][ny] == '@') adj_rolls++;
                }
            }

            // check condition
            if (adj_rolls < 4 && grid[x][y] == '@') rolls++;
        }
    }

    cout << rolls << endl;
}