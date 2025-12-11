#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

/*
    first very tricky problem for this year, so I think it is worth explaining

    the solution idea is to coordinate compress so that we only deal with a 500x500 grid
    then we can draw the outline of the shape, and fill it in via raycasting horizontal segments
    (this idea is called rasterization and was taught in CS345 here at Duke)

    then we can compute prefix sums so that we can check if a pair of red points is valid in constant time
    so this solution should be quadratic (this implementation is technically n^2logn due to sets used in coord compression)

    I really like this solution, I don't think one can do better than quadratic, and this works for any shape, not just the input
*/

const int MN = 500;

// grid, vertical segment indicators, prefix sums
ll grid [MN][MN];
ll vert [MN][MN];
ll ps [MN][MN];

int main() {
    // read in coordinates
    vector<vector<ll>> coords;
    string line;
    set<ll> cx, cy;
    while (getline(cin, line)) {
        string curr = "";
        vector<ll> coord;
        for (char c : line) {
            if (c == ',') coord.pb(stoll(curr));
            if (c == ',') curr = "";
            if (c != ',') curr.pb(c);
        }
        coord.pb(stoll(curr));
        coords.pb(coord);
        cx.insert(coord[0]);
        cy.insert(coord[1]);
    }

    int n = coords.size();

    // coordinate compress and maintain reverse maping
    map<ll,ll> x, y, rx, ry;

    int ct = 0;
    for (int p : cx) {
        x[p] = ct;
        rx[ct] = p; ct++;
    }

    ct = 0;
    for (int p : cy) {
        y[p] = ct;
        ry[ct] = p; ct++;
    }

    for (int i = 0; i < n; i++) {
        coords[i][0] = x[coords[i][0]];
        coords[i][1] = y[coords[i][1]];
    }

    
    // fill in outline of shape
    // if we are filling in vertical segments, set to 1 in vertical array as well
    // note that we exclude bottom points, as otherwise we may incorrectly count on "joints"
    for (int i = 1; i < n; i++) {
        if (coords[i-1][0] == coords[i][0]) {
            ll L = min(coords[i-1][1], coords[i][1]);
            ll R = max(coords[i-1][1], coords[i][1]);
            for (int j = L; j <= R; j++) grid[coords[i][0]][j]=1;
        }

        if (coords[i-1][1] == coords[i][1]) {
            ll L = min(coords[i-1][0], coords[i][0]);
            ll R = max(coords[i-1][0], coords[i][0]);
            for (int j = L; j <= R; j++) {
                grid[j][coords[i][1]]=1;
                if (j != R) vert[j][coords[i][1]]=1;
            }
        }
    }

    if (coords[0][0] == coords[n-1][0]) {
        ll L = min(coords[0][1], coords[n-1][1]);
        ll R = max(coords[0][1], coords[n-1][1]);
        for (int j = L; j <= R; j++) grid[coords[n-1][0]][j]=1;
    }

    if (coords[0][1] == coords[n-1][1]) {
        ll L = min(coords[0][0], coords[n-1][0]);
        ll R = max(coords[0][0], coords[n-1][0]);
        for (int j = L; j <= R; j++) {
            grid[j][coords[n-1][1]]=1;
            if (j != R) vert[j][coords[n-1][1]]=1;
        }
    }

    // fill in shape by casting rays horizontally
    // if we have intersected odd number of vertical segments, we are inside shape
    for (int i = 0; i < 500; i++) {
        ll inter = 0;
        for (int j = 0; j < 500; j++) {
            inter += vert[i][j];
            if (inter % 2 == 1) grid[i][j] = 1;
        }
    }

    // compute 2d prefix sums over grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ps[i+1][j+1] = ps[i][j+1] + ps[i+1][j] - ps[i][j] + grid[i][j];
        }
    }
    
    // iterate over pairs of red coordinates
    // query if rectangle is filled by checking if prefix sums match total points in rectangle
    ll area = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll ux = min(coords[i][0], coords[j][0]);
            ll dx = max(coords[i][0], coords[j][0]);
            ll uy = min(coords[i][1], coords[j][1]);
            ll dy = max(coords[i][1], coords[j][1]);

            ll val = ps[dx+1][dy+1] - ps[ux][dy+1] - ps[dx+1][uy] + ps[ux][uy];

            if (val == (dy - uy + 1) * (dx - ux + 1)) {
                area = max(area, (abs(rx[coords[i][0]] - rx[coords[j][0]]) + 1) * (abs(ry[coords[i][1]] - ry[coords[j][1]])+1));
            }
        }
    }

    cout << area << endl;
}