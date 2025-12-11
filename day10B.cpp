#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using plc = pair<ll,char>;
using pss = pair<string, string>;
#define pb push_back

/* 
    this is a really tricky, but cool problem, so I will explain this solution
    if we let the n x m matrix A encode our button presses, and b the joltage vector, we need to find
    integer vector x such that Ax=b, x>=0
    this is a linear program, but we can solve Ax=b generally with row reduction, being careful not to introduce any fractions
    (note that I don't divide for this reason, the solve method will ensure i find integer values of x before performing the division)

    it turns out that there are at most 3 free variables per test case, so we can just brute force the free variables
    and return the minimal solution
*/

ll solve(vector<ll> x, int i, ll prop, vector<vector<ll>>& A, vector<ll>& target, set<ll>& free, int& n, int& m) {
    if (i == -1) {
        // if we have exhausted all variables, check feasibility and return sum
        ll sum = 0;
        for (int i = 0; i < m; i++) {
            if (x[i] < 0) return 1e9;
            sum += abs(x[i]);
        }
        return sum;
    }
    
    if (free.count(i)) {
        ll ret = 1e9;

        // if variable is free, brute force the value from 0 to maximum joltage value
        // then return the minimum found solution
        ll mv = 0;
        for (ll x : target) mv = max(mv, x);

        for (int k = 0; k <= mv; k++) {
            vector<ll> y = x;
            y[i] = k;
            ret = min(ret, solve(y, i-1, prop, A, target, free, n, m));
        }
        return ret;
    }

    // find the row corresponding to this variable
    int c = -1;
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < m; b++) {
            if (A[a][b] != 0) {
                if (b == i) c = a;
                break;
            }
        }
        if (c >= 0) break;
    }

    // use prop value to ensure values avoid fractional values
    ll entry = prop * A[c][m];
    for (int j = i+1; j < m; j++) {
        entry -= A[c][j] * x[j];
    }
    
    // if fractional value about to be introduced, update prop so all stay integers
    ll prevprop = prop;
    if (A[c][i] != 0 && entry != 0 && abs(entry) % abs(A[c][i]) != 0) {
        prop = lcm(prop, lcm(abs(A[c][i]), abs(entry))/ (abs(entry)));
    }

    for (int k = 0; k < m; k++) {
        x[k] /= prevprop;
        x[k] *= prop;
    }

    // compute entry and continue solving path
    entry = prop * A[c][m];
    for (int j = i+1; j < m; j++) {
        entry -= A[c][j] * x[j];
    }
    entry /= A[c][i];

    vector<ll> y = x;
    y[i] = entry;
    if (entry < 0) return 1e9; // feasibility check to prune search
    return solve(y, i-1, prop, A, target, free, n, m);
}

ll gaussjordan(vector<vector<ll>> A, vector<ll> b) {
    vector<ll> target = b;
    int n = A.size();
    int m = A[0].size();

    // augment matrix A
    for (int i = 0; i < n; i++) {
        A[i].pb(b[i]);
    }

    // initial set of free vars
    set<ll> free;
    for (int i = 0; i < m; i++) free.insert(i);

    int col = 0;
    for (int i = 0; i < n; i++) {
        // find pivot row (swap if needed)
        while (true) {
            if (col > m) break;
            if (A[i][col] != 0) break;
            for (int j = i+1; j < n; j++) {
                if (A[j][col] != 0) {
                    swap(A[i], A[j]);
                    break;
                }
            }
            if (A[i][col] != 0) break;
            col++;
        }
        if (col > m) break;

        free.erase(col); // no longer free var
        ll L = A[i][col];

        // row reduce such that we don't introduce fractions, hence use of LCM
        for (int j = i+1; j < n; j++) {
            if (A[j][col] != 0) L = lcm(L, A[j][col]);
        }

        for (int j = i+1; j < n; j++) {
            if (A[j][col] == 0) continue;
            ll f1 = L / A[j][col];
            ll f2 = L / A[i][col];
            for (int k = 0; k < m+1; k++) {
                A[j][k] = f1 * A[j][k] - f2 * A[i][k];
            }
        }
    }
    
    // we now have row-reduced A and set of free variables
    // brute force values of free variables to find minimal sol
    return solve(vector<ll> (m, 0), m-1, 1, A, target, free, n, m);
}

int main() {
    // read in machines
    string line;
    ll total_presses = 0;
    while (getline(cin, line)) {
        int len = line.size();

        int ct = 0;
        string curr = "";
        vector<string> entries;
        while (ct < len) {
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

        // read in button list
        vector<vector<ll>> blist;
        for (int i = 1; i < entries.size(); i++) {
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

        // get joltage list
        vector<ll> jolt = blist[blist.size()-1];
        blist.pop_back();

        int n = jolt.size();
        int m = blist.size();

        // calculate an n x m binary array
        // entry ij is 1 if jth button increments ith cunter
        vector<vector<ll>> A (n, vector<ll> (m, 0));
        for (int i = 0; i < m; i++) {
            for (auto y : blist[i]) A[y][i] = 1;
        }

        // our goal is to find the integer vector x with minimal sum such that x >= 0, Ax=b
        // this is an integer linear program, but we can solve the system Ax=b with gaussian elimination
        // and then brute force the values of the free variables (at most 3 per test case)
        total_presses += gaussjordan(A, jolt);
    }

    cout << total_presses << endl;
}
