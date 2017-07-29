#include <bits/stdc++.h>
using namespace std;
const int mod = (int) 1e9 + 7;
int Pow(int a, int n, int mod) {
	int ans = 1;
	while (n) {
		if ( n & 1) {
			ans = (1ll * ans * a) % mod;
		}
		a = (1ll * a * a) % mod;
		n >>= 1;
	}
	return ans;
}
struct matrix {
	static const int nd = 3;
	int d[nd][nd];
	int* operator[] (const int &x) {
		return d[x];
	}
	
	matrix operator + (const matrix &other) const {     //add two matrices
		matrix ans;
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				ans[i][j] = d[i][j] + other.d[i][j];
				if (ans[i][j] > mod) ans[i][j] -= mod;
			}
		}
		return ans;
	}
	matrix operator - (const matrix &other) const {   //subtract two matrices
		matrix ans;
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				ans[i][j] = d[i][j] - other.d[i][j];
				if (ans[i][j] < 0) ans[i][j] += mod;
			}
		}
		return ans;
	}
	matrix operator * (matrix other) const  {   //multiple two matrices
		matrix ans;
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				int t = 0;
				for (int k = 0; k < nd; k++) {
					t += (1ll * d[i][k] * other[k][j] + 1ll * mod * mod) % mod;
					t %= mod;
				}
				ans[i][j] = t;
			}
		}
		return ans;
	}
	matrix operator ^(int n) const {    //power matrix
		matrix x = *this;
		matrix ans;
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				if (i == j) {
					ans[i][j] = 1;
				} else ans[i][j] = 0;
			}
		}
		while (n) {
			if (n & 1) {
				ans = ans * x;
			}
			x = x * x;
			n >>= 1;
		}
		return ans;
	}
	matrix operator *(const int &x) const {    //undirected multiple
		matrix ans;
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				ans[i][j] = (1ll * d[i][j] * x + 1ll * mod * mod) % mod;
			}
		}
		return ans;
	}

//	matrix operator ~() const{     //only for 2*2 matrix
//		matrix ans = {{{d[1][1], -d[1][0]}, { -d[0][1], d[0][0]}}};
//		int det = (1ll * d[0][0] * d[1][1] - 1ll * d[0][1] * d[1][0] + 1ll * mod * mod) % mod;
//		return ans * Pow(det, mod - 2, mod);
//	}

//	void print() {
//		for (int i = 0; i < nd; i++) {
//			for (int j = 0; j < nd; j++) {
//				cout << d[i][j] << " ";
//			}
//			cout << endl;
//
//		}
//		cout << endl;
//	}



	int operator *() const {  // configure this method
		return (1ll *  d[0][0] * 2 + 1ll * d[1][0] + 1ll * d[2][0] ) % mod;
	}

};




//    http://www.spoj.com/problems/FIBOSUM/
int call(int x) {
	if (x <= 0) return 0;
	if (x == 1) return 1;
	if (x == 2) return 2;
	matrix A = {{{1, 0, 0}, {1, 0, 1,}, {1, 1, 1}}};
	A = A ^ (x - 2);
	return *A;
}
int main() {
	freopen("a.in", "r" , stdin);
	int n, l, r;
	scanf("%d", &n);
	while (n--) {
		scanf("%d %d", &l, &r);
		int x = call(r);
		int y = call(l - 1);
		x -= y;
		if (x < 0) x += mod;
		printf("%d\n", x);
	}
}
