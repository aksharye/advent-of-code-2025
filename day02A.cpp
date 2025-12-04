#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    string line; // read in all ranges
    vector<string> ranges;
    while (getline(cin, line)) {
        string curr = "";
        for (char c : line) {
            if (c == ',') ranges.pb(curr);
            if (c == ',') curr = "";
            if (c != ',') curr.pb(c);
        }
        ranges.pb(curr);
    }

    ll invalid = 0;
    for (string s : ranges) {
        int n = s.size();
        int j = 0;
        for (int i = 0; i < n; i++) if (s[i] == '-') j = i;

        // get the two bounds of the range
        ll start = stoll(s.substr(0,j));
        ll end = stoll(s.substr(j+1));

        // iterate through the ids, check if they have equal halves
        for (ll id = start; id <= end; id++) {
            string curr = to_string(id);
            if (curr.size() % 2 == 0) {
                if (curr.substr(0, curr.size()/2) == curr.substr(curr.size()/2)) invalid += id;
            }
        }
    }

    cout << invalid << endl;
}