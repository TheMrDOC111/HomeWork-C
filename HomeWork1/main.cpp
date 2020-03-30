#include<iostream>
#include<cmath>
#include<set>
#include<vector>
#include<algorithm>
#include<cstdio>


using namespace std;

double f(double x) {
    return -x * x -0.5;
}

double EPS = 0.0000001;

int main() {
    freopen("g3.out", "w", stdout);

    int n, m;
    double x0, x1;
    cin >> m >> n >> x0 >> x1;

    vector<vector<char>> a(n+1, vector<char>(m));

    double mx = f(x0);
    double mn = f(x0);
    double zeroPos = 0;

    double val1 = f(x0);
    bool flag = false;
    for (int i = 0; i < m; ++i) {
        auto val = f(x0 + (x1 - x0) / m * i);

        if (((val1 < 0 && val >= 0) || (val1 > 0 && val >= 0)) && !flag) {
            zeroPos = val;
            flag = true;
        }
        mx = max(mx, val);
        mn = min(mn, val);
    }


    int zeroY = 0;


    if (zeroPos <= mn) {
        mn = zeroPos;
        zeroY = n;
    } else if (zeroPos >= mx) {
        mx = zeroPos;
        zeroY = 0;
    } else {
        zeroY = ((mx / (abs(mx) + abs(mn))) * (n + 1));
    }


    double lastVal = f(x0);

    bool dir = f(x0 + EPS) >= 0;
    n++;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {

            if (i == zeroY) {
                a[i][j] = '-';
                continue;
            }


            auto val = f(x0 + (x1 - x0) / m * j);

            if (lastVal * val < 0) {
                dir = !dir;
            }
            auto diff = abs(val - mn) / abs(mx - mn);
            diff *= n;
            auto i1 = n - diff;


            if ((i > zeroY && dir) || (i < zeroY && !dir)) {
                a[i][j] = ' ';
            } else {
                if ((i >= i1 && dir) || (i <= i1 && !dir)) {
                    a[i][j] = '#';
                } else {
                    a[i][j] = ' ';
                }
            }
            lastVal = val;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << a[i][j];
        }
        cout << endl;
    }


    return 0;
}