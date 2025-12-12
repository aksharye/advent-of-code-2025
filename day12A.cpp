#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    // read in grids and grid sizes
    // note that from the input that when the sum of # over all grids is less than the region size
    // its significantly lower than the region size, thus its always tileable (you can pack together closely)
    vector<ll> sizes;
    ll ct = 0;
    ll k = 0;
    ll regions = 0;
    string line;
    while (getline(cin, line)) {
        for (char c : line) {
            if (c == '#') ct++;
        }
        k++;

        if (k % 5 == 0) {
            sizes.pb(ct);
            ct = 0;
        }

        if (line.size() < 6) continue;

        string curr = "";
        vector<string> nodes;
        for (char c : line) {
            if (c == ' ') nodes.pb(curr);
            if (c == ' ') curr = "";
            if (c != ' ') curr.pb(c);
        }
        nodes.pb(curr);

        vector<ll> vals;
        ll sumtiles = 0;
        for (int i = 1; i < nodes.size(); i++) {
            vals.pb(stoll(nodes[i]));
            sumtiles += vals[i-1] * sizes[i-1];
        }

        ll H = stoll(nodes[0].substr(0,2));
        ll W = stoll(nodes[0].substr(3,5));

        // cout << H << " " << W << " " << (W*H) << " " << sumtiles << endl;
        if (sumtiles <= (W*H)) regions++;
    }

    cout << regions << endl;
}