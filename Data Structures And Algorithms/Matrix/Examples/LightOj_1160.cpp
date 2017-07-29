#include <bits/stdc++.h>
#define cbit(x) __builtin_popcount(x)
using namespace std;
const int mod = (int) 1e9+7;
struct matrix {
    static const int nd = 36;
    static const int mod = (int) 1e9+7;
    int d[nd][nd];
    int * operator[](int n) {
        return d[n];
    }

    matrix operator + (matrix &other)  const{
        matrix ans;
        for(int i=0;i<nd;i++) {
            for(int j=0;j<nd;j++) {
                ans[i][j] = d[i][j] + other[i][j];
                if (ans[i][j] > mod) ans[i][j] -= mod;
            }
        }
        return ans;
    }
    matrix operator  * (matrix &other) const{
        matrix ans;
        for(int i=0;i<nd;i++) {
            for(int j =0;j<nd;j++) {
                int t = 0;
                for(int k=0;k<nd;k++) {
                    t  += (1ll * d[i][k] * other[k][j]) % mod;
                    if (t> mod) t -= mod;
                }
                ans[i][j] = t;
            }
        }
        return ans;
    }
    void print() {
        for(int i=0;i<nd;i++) {
            for(int j=0;j<nd;j++) {
                cout<<d[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    matrix operator ^(int n) {
        matrix ans;
        for(int i=0;i<nd;i++) {
            for(int j=0;j<nd;j++) {
                if(i==j) {
                    ans[i][j] = 1;
                } else ans[i][j]  = 0;
            }
        }
        matrix x = *this;
        while (n) {
            if(n&1) {
                ans = ans * x;
            }
            x = x * x;
            n>>=1;
        }
        return ans;
    }
};
vector <int> vt;
int m[1<<7];

void Try(int u,int x,int t,matrix &A) {
    if (u==4) {
        int cnt = cbit(t);
        if (cnt==4) {
            A[m[x]][m[t]] = 1;
        }
    } else {
        int pos = vt[u];
        if (pos >0) {
            Try(u+1,x,t|(1<<(pos-1)),A);
        }
        if (pos+1<7) {
            Try(u+1,x,t|(1<<(pos+1)),A);
        }
    }
}
int main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int test = 0;
    scanf("%d", &test);
    int cnt = 0;
    matrix A;
    for(int i=0;i<A.nd;i++) {
        for(int j=0;j<A.nd;j++) {
            A[i][j] = 0;
        }
    }
    int sl = 0;
    for(int i=0;i<(1<<7);i++) {
        int cnt = cbit(i);
        if (cnt==4) {
            m[i] = sl++;
        }
    }
    for(int i=0;i<(1<<7);i++) {
        int cnt = cbit(i);
        if (cnt==4) {
            vt.clear();
            for(int j=0;j<7;j++) {
                if((i>>j) & 1) {
                    vt.push_back(j);
                }
            }
            Try(0,i,0,A);
        }
    }
    int n,x;
    int mask;
    while (test--) {
        mask = 0;
        cout<<"Case "<<++cnt<<": ";
        scanf("%d", &n);
        for(int i=0;i<7;i++) {
            scanf("%d", &x);
            if(x!=0) mask |= (1<<(i));
        }
        matrix B = A ^ (n-1);
        int ans = 0;
        for(int i=0;i<B.nd;i++) {
            ans += B[m[mask]][i];
            ans %= mod;
        }
        cout<<ans<<endl;
    }
}
