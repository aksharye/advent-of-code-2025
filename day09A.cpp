#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    // read in coordinates
    vector<vector<ll>> coords;
    string line;
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
    }

    // iterate over all pairs of coordinates and calculate rectangle area
    ll area = 0;
    int n = coords.size(); 
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            area = max(area, (abs(coords[i][0] - coords[j][0]) + 1) * (abs(coords[i][1] - coords[j][1]) + 1));
        }
    }

    cout << area << endl;
}