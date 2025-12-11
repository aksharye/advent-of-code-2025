#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    // read in machines
    string line;
    ll total_presses = 0;
    while (getline(cin, line)) {
        int n = line.size();

        int ct = 0;
        string curr = "";
        vector<string> entries;
        while (ct < n) {
            if (line[ct] == ' ') {
                entries.pb(curr);
                curr.clear();
            } else {
                curr.pb(line[ct]);
            }
            ct++;
        }
        entries.pb(curr);

        // read in machine
        string machine = entries[0].substr(1,entries[0].size()-2);

        int buttons = entries.size()-2;

        // read in button list
        vector<vector<ll>> blist;
        for (int i = 1; i < entries.size()-1; i++) {
            string y = entries[i].substr(1, entries[i].size()-2);
            curr = "";
            vector<ll> coord;
            for (char c : y) {
                if (c == ',') coord.pb(stoll(curr));
                if (c == ',') curr = "";
                if (c != ',') curr.pb(c);
            }
            coord.pb(stoll(curr));
            blist.pb(coord);
        }

        // calculate target bitmask
        int target = 0;
        for (int i = 0; i < machine.size(); i++) {
            if (machine[i] == '#') target += (1 << i);
        }

        // calculate minimum presses by brute forcing all subsets via masks
        // as pressing the same button twice is same as never pressing it
        ll min_presses = 1000;
        for (int i = 0; i < (1 << buttons); i++) {
            ll curr = 0;
            int presses = 0;
            for (int j = 0; j < buttons; j++) {
                if (i & (1 << j)) {
                    presses++;
                    for (int k : blist[j]) {
                        curr ^= (1 << k);
                    }
                }
            }

            // if subset gets target mask, compare to minimum
            if (curr == target) {
                min_presses = min(min_presses, (ll) presses);
            }
        }
        total_presses += min_presses;
    }

    cout << total_presses << endl;
}
