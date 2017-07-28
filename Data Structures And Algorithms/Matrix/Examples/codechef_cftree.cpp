#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 100;
const int nd = 2;
int Pow(int x, int n, int mod)
{
	int ans = 1;
	while (n)
	{
		if (n & 1)
		{
			ans = (1ll * ans * x) % mod;
		}
		x = (1ll * x * x) % mod;
		n >>= 1;
	}
	return ans;
}
struct matrix
{
	int d[nd][nd];
	matrix operator + (const matrix &other) const
	{
		matrix ans;
		for (int i = 0; i < nd; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				ans.d[i][j] = d[i][j] + other.d[i][j];
				if (ans.d[i][j] > mod) ans.d[i][j] -= mod;
			}
		}
		return ans;
	}
	matrix operator - (const matrix &other) const
	{
		matrix ans;
		for (int i = 0; i < nd; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				ans.d[i][j] = d[i][j] - other.d[i][j];
				if (ans.d[i][j] < 0) ans.d[i][j] += mod;
			}
		}
		return ans;
	}
	matrix operator * (const matrix &other) const
	{
		matrix ans;
		for (int i = 0; i < nd; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				int t = 0;
				for (int k = 0; k < nd; k++)
				{
					t += (1ll * d[i][k] * other.d[k][j] + 1ll * mod * mod) % mod;
					t %= mod;
				}
				ans.d[i][j] = t;
			}
		}
		return ans;
	}
	matrix operator ^(int n) const
	{
		matrix x = *this;
		matrix ans = {{{1, 0}, {0, 1}}};
		while (n)
		{
			if (n & 1)
			{
				ans = ans * x;
			}
			x = x * x;
			n >>= 1;
		}
		return ans;
	}
	matrix operator *(const int &x) const
	{
		matrix ans;
		for (int i = 0; i < nd; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				ans.d[i][j] = (1ll * d[i][j] * x + 1ll * mod * mod) % mod;
			}
		}
		return ans;
	}
	matrix operator ~() const     //only for 2*2 matrix
	{
		matrix ans = {{{d[1][1], -d[1][0]}, { -d[0][1], d[0][0]}}};
		int det = (1ll * d[0][0] * d[1][1] - 1ll * d[0][1] * d[1][0] + 1ll * mod * mod) % mod;
		return ans * Pow(det, mod - 2, mod);
	}
	void print()
	{
		for (int i = 0; i < nd; i++)
		{
			for (int j = 0; j < nd; j++)
			{
				cout << d[i][j] << " ";
			}
			cout << endl;

		}
		cout << endl;
	}
	int operator *() const
	{
		return d[0][0];
	}
};
matrix f[2][maxn];
int in[maxn], out[maxn];
vector<int> vt[maxn];
matrix K ;
int cnt;
int h[maxn];

matrix pre[maxn];

const matrix base = {{{1, 1}, {1, 0}}};
const matrix I = {{{1, 0}, {0, 1}}};
void dfs(int u, int p)
{
	in[u] = cnt++;
	for (int i = 0; i < vt[u].size(); i++)
	{
		int v = vt[u][i];
		if (v != p)
		{
			h[v] = h[u] + 1;
			dfs(v, u);
		}
	}
	out[u] = cnt++;
}

void update(matrix  *f, int x, matrix val)
{
	x += 2;
	if (x <= 0)return;
	while (x < maxn)
	{
		f[x] = f[x] + val;
		x += x & -x;
	}
}
matrix get(matrix *f, int x)
{
	x += 2;
	matrix ans = {{{0, 0}, {0, 0}}};
	if (x <= 0) return ans;
	while (x)
	{
		ans = ans +  f[x];
		x -= x & -x;
	}
	return ans;
}
void update1(int l, matrix T) {
	update(f[0], l, T);
	update(f[1], l,   T * (l - 1));
}
void update(int u, int k)
{
	int t = (k - 1 - h[u]);
	int l = in[u];
	int r = out[u];
	matrix T;
	if (t >= 0)
	{
		T = pre[t];
	}
	else
	{
		T = ~pre[-t];
	}
	update1(l, T);
	update1(r + 1, T * -1);
}
matrix get1(int x)
{
	matrix a = get(f[0], x);
	matrix b = get(f[1], x);
	return a * x - b;
}
int get(int x)
{
	return *((get1(in[x]) - get1(in[x] - 1)) * pre[h[x]]);
}
int main()
{
	freopen("a.in", "r", stdin);
	int n, q, u;
	scanf("%d %d\n", &n, &q);
	for (int i = 0; i + 1 < n; i++)
	{
		scanf("%d\n", &u);
		u--;
		int v = i + 1;
		vt[u].push_back(v);
		vt[v].push_back(u);
	}
	pre[0] = I;
	pre[1] = base;
	for (int i = 2; i < maxn; i++)
	{
		pre[i] = pre[i - 1] * base;
	}

	h[0] = 1;
	dfs(0, -1);
	char c;
	int  k ;
	while (q--)
	{
		scanf("%c", &c);
		if (c == 'U')
		{
			scanf("%d %d\n", &u, &k);
			u--;
			update(u, k);
		}
		else
		{
			scanf("%d\n", &u);
			u--;
			printf("%d\n", get(u));
		}
	}
}

