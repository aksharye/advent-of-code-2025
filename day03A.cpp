#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    int total_charge = 0;

    // read in lines
    string line;
    while (getline(cin, line)) {
        int max_charge = 0;
        // loop through all pairs of positions to find max charge per line
        for (int i = 0; i < line.size(); i++) {
            for (int j = i+1; j < line.size(); j++) {
                string battery = "";
                battery.pb(line[i]);
                battery.pb(line[j]);
                max_charge = max(max_charge, stoi(battery));
            }
        }
        total_charge += max_charge;
    }

    cout << total_charge << endl;
}