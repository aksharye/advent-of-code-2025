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

    ll ct = 0;
    while (ct < lines[0].size()) {
        // iterate through operations in final line
        char op = lines[lines.size()-1][ct];

        ll c = 0;
        if (op == '*') c = 1;

        // read in digits in each column until column is blank
        while (ct < lines[0].size()) {
            string curr = "";
            for (int i = 0; i < lines.size()-1; i++) {
                if (lines[i][ct] != ' ' && lines[i][ct] != '\n') curr.pb(lines[i][ct]);
            }
            ct++;

            if (curr == "") break; // break if column is blank

            // compile numbers based on operation
            if (op == '*') {
                c *= stoll(curr);
            } else {
                c += stoll(curr);
            }
        }
        sum += c;
    }

    cout << sum << endl;
}