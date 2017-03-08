#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const int ROOT = 0;
const int maxn = 100100;
const int sn = 320;
const int rsn = maxn / sn + 5;
int c[maxn];
int ccnt[maxn];
int cbig[maxn];
vector<int> g[maxn];
vector<int> byCol[maxn];
vector<int> to[2 * maxn];
int h[2 * maxn];
int in[2 * maxn];
int out[2 * maxn];

int pp[17][maxn];

int timer;
int n, bigs;

int bigId[rsn][maxn];
vector<ll> bigVal[rsn];

void pre(int u, int prev = -1) {
    if (prev == -1)
        pp[0][u] = u;
    else
        pp[0][u] = prev;
    in[u] = timer++;
    for (int v: g[u]) {
        if (v == prev)
            continue;
        h[v] = h[u] + 1;
        pre(v, u);
    }
    out[u] = timer;
}

bool isPrev(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

bool used[maxn];
int BAD, CC;
void dfs1(int u) {
    used[u] = true;
    bigId[cbig[BAD]][u] = CC;
    for (int v: g[u]) {
        if (used[v])
            continue;
        dfs1(v);
    }
}

void buildBig(int id) {
    //cerr << "col " << id + 1 << '\n';
    BAD = id;
    CC = 0;
    forn (i, n) {
        used[i] = c[i] == id;
        if (used[i])
            bigId[cbig[id]][i] = -1;
    }
    forn (i, n) {
        if (!used[i]) {
            dfs1(i);
            ++CC;
        }
    }
    bigVal[cbig[id]].resize(CC);
  }

void buildSmall(int id) {
    h[n + id] = -inf;
    in[n + id] = -inf;
    out[n + id] = inf;

    vector<int> &v = byCol[id];
    v.push_back(n + id);
    sort(v.begin(), v.end(), [](int a, int b) {
                return h[a] < h[b];
            });
    for (int i = 1; i < sz(v); ++i) {
        int u = v[i];
        bool ok = false;
        for (int j = i - 1; j >= 0; --j) {
            if (isPrev(v[j], u)) {
                ok = true;
                to[v[j]].push_back(u);
                break;
            }
        }
        assert(ok);
    }
}

struct Fenwick {
    ll t[maxn];

    void add(int pos, int delta) {
        //cerr << "fwadd " << pos << ' ' << delta << '\n';
        for (int i = pos; i < maxn; i |= i + 1)
            t[i] += delta;
    }

    ll get(int r) {
        ll res = 0;
        for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
            res += t[i];
        return res;
    }
} fw;

bool isBig(int c) {
    return ccnt[c] >= sn;
}

int up(int u, int v) {
    int dh = h[u] - h[v] - 1;
    assert(dh >= 0);
    for (int bit = 16; bit >= 0; --bit)
        if (dh >= (1 << bit)) {
            dh -= 1 << bit;
            u = pp[bit][u];
        }
    assert(isPrev(v, u) && h[v] + 1 == h[u]);
    return u;
}

void add(int u, int c, ll s) {
    if (::c[u] == c)
        return;
    if (isBig(c)) {
        int pos = bigId[cbig[c]][u];
        assert(pos != -1);
        bigVal[cbig[c]][pos] += s;
    } else {
        auto &v = byCol[c];
        int pr = -1;
        for (int i = sz(v) - 1; i >= 0; --i) {
            if (isPrev(v[i], u)) {
                pr = v[i];
                break;
            }
        }
        assert(pr != -1);
        int cpr;
        if (pr < n) {
            cpr = up(u, pr);
            //cerr << "YO " << pr + 1 << '\n';
            fw.add(in[cpr], s);
            fw.add(out[cpr], -s);
        } else {
            cpr = pr;
            fw.add(0, s);
        }
        for (int x: to[pr]) {
            if (!isPrev(cpr, x))
                continue;
            //cerr << "bad " << x << '\n';
            fw.add(in[x], -s);
            fw.add(out[x], s);
        }
    }
}


ll get(int u) {
    //cerr << "get " << u + 1 << '\n';
    ll res = fw.get(in[u]);
    forn (i, bigs) {
        int pos = bigId[i][u];
        if (pos == -1)
            continue;
        res += bigVal[i][pos];
    }
    return res;
}

int main() {
    #ifdef LOCAL
    assert(freopen("e.in", "r", stdin));
    #else
    #endif
    cin >> n;
    forn (i, n) {
        scanf("%d", c + i);
        --c[i];
        ccnt[c[i]]++;
        byCol[c[i]].push_back(i);
    }
    forn (i, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    pre(ROOT);
    forn (d, 16)
        forn (i, n)
            pp[d + 1][i] = pp[d][pp[d][i]];

    forn (i, n) {
        if (isBig(i)) {
            cbig[i] = bigs++;
            buildBig(i);
        } else {
            buildSmall(i);
        }
    }

    int q;
    cin >> q;
    ll last = 0;
    forn (i, q) {
        int type;
        ll u, c, s;
        cin >> type >> u;
        u ^= last;
        --u;
        if (type == 1) {
            cin >> c >> s;
            c ^= last, s ^= last;
            --c;
            add(u, c, s);
        } else {
            last = get(u);
            cout << last << '\n';
        }
    }
}
