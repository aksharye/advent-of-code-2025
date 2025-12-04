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

        // iterate through the ids
        for (ll id = start; id <= end; id++) {
            string curr = to_string(id);
            
            // iterate through all divisors of the size
            int m = curr.size();
            for (int k = 1; k < m; k++) {
                if (m % k == 0) {
                    // collect the m/k parts
                    vector<string> parts;
                    for (int i = 0; i < m/k; i++) {
                        parts.pb(curr.substr(k * i, k));
                    }

                    // check if any two consecutive parts are not equal
                    bool valid = true;
                    for (int i = 1; i < m/k; i++) {
                        if (parts[i] != parts[i-1]) valid = false;
                    }

                    // if all equal, then this id is invalid
                    if (valid) {
                        invalid += id;
                        break;
                    }
                }
            }
        }
    }

    cout << invalid << endl;
}