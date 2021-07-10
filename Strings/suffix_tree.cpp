#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)

struct SuffixTree {
	enum { N = 200010, ALPHA = 27 }; // N ~ 2*maxlen+10
	int toi(char c) { return c - 'a'; }
	string a; // v = cur node, q = cur position
	int t[N][ALPHA],l[N],r[N],p[N],s[N],v=0,q=0,m=2;

	void ukkadd(int i, int c) { suff:
		if (r[v]<=q) {
			if (t[v][c]==-1) { t[v][c]=m;  l[m]=i;
				p[m++]=v; v=s[v]; q=r[v];  goto suff; }
			v=t[v][c]; q=l[v];
		}
		if (q==-1 || c==toi(a[q])) q++; else {
			l[m+1]=i;  p[m+1]=m;  l[m]=l[v];  r[m]=q;
			p[m]=p[v];  t[m][c]=m+1;  t[m][toi(a[q])]=v;
			l[v]=q;  p[v]=m;  t[p[m]][toi(a[l[m]])]=m;
			v=s[p[m]];  q=l[m];
			while (q<r[m]) { v=t[v][toi(a[q])];  q+=r[v]-l[v]; }
			if (q==r[m])  s[m]=v;  else s[m]=m+2;
			q=r[v]-(q-r[m]);  m+=2;  goto suff;
		}
	}

	SuffixTree(string a) : a(a) {
		fill(r,r+N,sz(a));
		memset(s, 0, sizeof s);
		memset(t, -1, sizeof t);
		fill(t[1],t[1]+ALPHA,0);
		s[0] = 1; l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
		rep(i,0,sz(a)) ukkadd(i, toi(a[i]));
	}

	// example: find longest common substring (uses ALPHA = 28)
	pii best;
	int lcs(int node, int i1, int i2, int olen) {
		if (l[node] <= i1 && i1 < r[node]) return 1;
		if (l[node] <= i2 && i2 < r[node]) return 2;
		int mask = 0, len = node ? olen + (r[node] - l[node]) : 0;
		rep(c,0,ALPHA) if (t[node][c] != -1)
			mask |= lcs(t[node][c], i1, i2, len);
		if (mask == 3)
			best = max(best, {len, r[node] - len});
		return mask;
	}
	static pii LCS(string s, string t) {
		SuffixTree st(s + (char)('z' + 1) + t + (char)('z' + 2));
		st.lcs(0, sz(s), sz(s) + 1 + sz(t), 0);
		return st.best;
	}
};

int n;
string s;
SuffixTree *st;

void dfs(int v, int de = 0) {
    bool leaf = true;
    for (int w = 0; w < 27; w++)
        if (st->t[v][w] != -1) {
            leaf = false;
            int u = st->t[v][w];
            dfs(u, de+st->r[u]-st->l[u]);
        }

    if (leaf) {
        printf("Leaf corresponding to suffix starting at %d\n", n - de);
    }
}

int main() {
    s = "banana";
    s += char('z' + 1);
    n = s.size();
    st = new SuffixTree(s);
    dfs(0);
    return 0;
}
