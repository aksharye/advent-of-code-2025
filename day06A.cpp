#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        lines.pb(line);
    }

    ll sum = 0;
    vector<vector<ll>> nums;
    string curr = "";

    // read in numbers at each line
    for (int i = 0; i < lines.size()-1; i++) {
        nums.pb({});
        for (char c : lines[i]) {
            if (c == ' ') {
                if (curr.size() > 0) {
                    nums[i].pb(stoll(curr));
                    curr = "";
                }
            } else {
                curr.pb(c);
            }
        }
        if (curr.size() > 0) {
            nums[i].pb(stoll(curr));
            curr = "";
        }
    }

    // collect final line, compute problems from each column
    int ct = 0;
    for (char c : lines[lines.size()-1]) {
        if (c == '*') {
            ll c = 1;
            for (int i = 0; i < nums.size(); i++) {
                c *= nums[i][ct];
            }
            sum += c;
            ct++;
        } else if (c == '+') {
            ll c = 0;
            for (int i = 0; i < nums.size(); i++) {
                c += nums[i][ct];
            }
            sum += c;
            ct++;
        }
    }

    cout << sum << endl;
}