#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    ll fresh = 0;

    string line;
    vector<string> ranges;
    vector<pll> diff;

    // parse input
    bool flag = false;
    while (getline(cin, line)) {
        if (line == "") {
            flag = true;
            continue;
        }

        if (!flag) {
            string curr = "";
            for (char c : line) {
                if (c == ',') ranges.pb(curr);
                if (c == ',') curr = "";
                if (c != ',') curr.pb(c);
            }
            ranges.pb(curr);
            string s = curr;
            int n = s.size();
            int j = 0;
            for (int i = 0; i < n; i++) if (s[i] == '-') j = i;

            // get the two bounds of the range
            ll start = stoll(s.substr(0,j));
            ll end = stoll(s.substr(j+1));

            diff.pb({start,-1}); // start bound -1 (for sorting)
            diff.pb({end,1}); // end bound 1
        } else {
            diff.pb({stoll(line),0}); // set any ingredient to 0
        }

    }

    // sort the pairs, we set start to -1, ingredients to 0, and end to 1
    // so that sorting retains their order
    sort(diff.begin(), diff.end());

    int curr = 0; // keep track of number of active intervals
    for (int i = 0; i < diff.size(); i++) {
        if (diff[i].second == 0) {
            if (curr > 0) { // if there is at least one active interval, this ingredient is fresh
                fresh++;
            }
        } else {
            curr -= diff[i].second; // update number of active intervals
        }
    }
    
    cout << fresh << endl;
}