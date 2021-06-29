#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <vector>

using namespace std;

int MAX_N = 16200, MAX_M = 16200;

vector <vector <int> > a, b;

//int a[MAX_N][MAX_N], b[MAX_N][MAX_N];

int st, fs;

int getRand() {
	return (rand() << 16) | rand();
}

void transpose(int x, int delx, int y, int dely) {
	if ((delx == 1) && (dely == 1)) {
		b[y][x] = a[x][y];
		return;
	}
	if (delx >= dely) {
		int xmid = delx / 2;
		transpose(x, xmid, y, dely);
		transpose(x + xmid, delx - xmid, y, dely);
		return;
	}
	int ymid = dely / 2;
	transpose(x, delx, y, ymid);
	transpose(x, delx, y + ymid, dely - ymid);
}

void naive() {
	for (int i = 0; i < MAX_N; i++) {
		for (int j = i + 1; j < MAX_M; j++) {
			a[j][i] = b[i][j];
			a[i][j] = b[j][i];
		}
	}
}

void print() {
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_M; j++) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_M; j++) {
			cout << b[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

void filling() {
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_M; j++) {
			a[i][j] = getRand();
		}
	}

}

void solve() {
    MAX_M = MAX_N;
    for (int i = 0; i < 6; ++i) {
        filling();

        unsigned int start_time = clock();

        transpose(0, MAX_N, 0, MAX_M);

        unsigned int end_time = clock();
        unsigned int search_time = end_time - start_time;
        fs += search_time;
        cout << search_time << " ";
        //print();
        start_time = clock();

        naive();

        end_time = clock();
        search_time = end_time - start_time;
        st += search_time;
        cout << search_time << '\n';
        //print();
    }
    cout << fs << " " << st << '\n';
    cout << "Fast " << fs / 6.0 << " ms, naive " << st / 6.0 << " ms\n";
    cout << "-------------\n\n";
}


int main() {
    //freopen("ans.out", "w", stdout);
    cout << "Enter the size of the matrix N*N (from 1000 to 16200)\n";
    cin >> MAX_N;

    vector <vector<int>> a2(MAX_N, vector<int>(MAX_N)), b2(MAX_N, vector<int>(MAX_N));
    swap(a, a2);
    a2.clear();

    swap(b, b2);
    b2.clear();

    st = 0, fs = 0;
    solve();

    a.clear();
    b.clear();

}

