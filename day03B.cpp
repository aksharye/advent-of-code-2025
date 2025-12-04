#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    ll total_charge = 0;

    // read in lines
    string line;
    while (getline(cin, line)) {
        ll m = line.size();

        ll dp[m+1][13];
        bool reach[m+1][13];

        // set dp states to 9
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j < 13; j++) {
                dp[i][j] = 0;
                reach[i][j] = 0;
            }
        }

        // empty string is reachable
        reach[0][0] = 1;

        // fill out dp states
        // dp[i][j] = max j-digit number up to index i
        // reach[i][j] = existence of j-digit number up to index i
        for (int i = 0; i < line.size(); i++) {
            int d = line[i] - '0'; // digit
            reach[i+1][0] = 1; // empty string is reachable

            // loop through dp states
            for (int k = 1; k < 13; k++) {
                // if k-digit number reachable from i
                // also valid k-digit number for i+1
                if (reach[i][k]) {
                    dp[i+1][k] = max(dp[i+1][k], dp[i][k]);
                    reach[i+1][k] = 1;
                }

                // if (k-1)-digit number reachable from i
                // can append digit d to form valid k-digit number
                if (reach[i][k-1]) {
                    dp[i+1][k] = max(dp[i+1][k], 10 * dp[i][k-1] + d);
                    reach[i+1][k] = 1;
                }
            }
        }

        // obtain largest 12-digit number in whole string
        total_charge += dp[m][12];
    }

    cout << total_charge << endl;
}