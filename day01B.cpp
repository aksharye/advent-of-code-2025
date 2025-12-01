#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

int main() {
    int dial = 50; // current dial position
    int zeros = 0;

    string line; // read in input line by line
    while (getline(cin, line)) {
        // parse direction and distance
        int dir, dist;
        if (line[0] == 'L') {
            dir = -1;
        } else {
            dir = 1;
        }

        dist = stoi(line.substr(1));

        // store prev dial position
        ll prev = dial;

        // update direction and distance
        dial += dir * dist;

        zeros += abs(dial) / 100; // counts zeros by number of full rotations/going right past 0
        if (prev != 0 && dial <= 0) zeros++; // count zeros by moving left past 0

        // set dial to correct value using modulo 100
        dial %= 100;
        dial += 100;
        dial %= 100;
    }

    cout << zeros << endl;
}