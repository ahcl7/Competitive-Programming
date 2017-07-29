
//http://lightoj.com/volume_showproblem.php?problem=1052


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
    static const long long mod = (long long) 1e9+7;
	static const int nd = 2;
	unsigned long long d[nd][nd];
	unsigned long long* operator[] (const int &x) {
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
//		if (n==0) return {{{0,1},{1,0}}};
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

	void print() {
		for (int i = 0; i < nd; i++) {
			for (int j = 0; j < nd; j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;

		}
		cout << endl;
	}



	int operator *() const {  // configure this method
		return (1ll *  d[0][0] * 2 + 1ll * d[1][0] + 1ll * d[2][0] ) % mod;
	}

};





long long gcd(long long a,long long b) {
    if (a%b==0) return b;
    return gcd(b , a % b);
}
long long lcd(long long a,long long b) {
    return a * b / gcd(a,b);
}
bool solve(long long a,long long b,long long c,long long a1,long long b1,long long c1,long long &x,long long &y) {
//    cout<<a<<" "<<b<<" "<<c<<endl;
    long long t = gcd(a,a1);
    b = b * a1 / t;
    c = c * a1 / t;
    b1 = b1 * a / t;
    c1 = c1 * a / t;
    long long t1 = (c-c1);
    long long t2 = (b-b1);
    if (b==b1) return false;
    if (t1%t2!=0) return false;
    if (t1 / t2 <0) return false;
    y = t1 / t2;
    b = b * t / a1;
    c = c * t / a1;
    if (a==0) return false;
    if ((c - b * y) % a !=0) return false;
    if ((c-b*y) / a <0) return false;
    x = (c-b*y) / a;
    return true;
}
int main() {
//    freopen("a.in", "r", stdin);
//    freopen("a.out", "w", stdout);
	matrix A = {{{0,1},{1,1}}};
    int test = 0 ;
    int n,x,m,y,k;
    matrix B,C;
    scanf("%d", &test);
    int cnt = 0;
    while (test--) {
        cout<<"Case " << ++ cnt <<": ";
        scanf("%d %d %d %d %d", &n,&x,&m,&y,&k);
        B = A ^ (n-1);
        C = A ^ (m-1);
        if (n > 43 || m>43) {
            cout<<"Impossible"<<endl;
            continue;
        }
        long long a,b;
        bool hasSolution = solve(B[0][1] + B[0][0] ,B[1][0] + B[1][1],x,C[0][1]+C[0][0],C[1][0] + C[1][1],y,a,b);
        if (hasSolution) {
            B = A ^ (k-1);
            cout<<(b * B[1][0] + a * B[0][1] + a * B[0][0] +  b * B[1][1] + 1ll * mod * mod)%  mod<<endl;
        } else {
            cout<<"Impossible"<<endl;
        }
    }

}

