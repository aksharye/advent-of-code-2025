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

        // update direction and distance
        dial += dir * dist;

        // set dial to correct value using modulo 100
        dial %= 100;
        dial += 100;
        dial %= 100;

        // count when dial points to 0
        if (dial == 0) zeros++;
    }

    cout << zeros << endl;
}