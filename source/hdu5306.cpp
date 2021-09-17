#include <iostream>
#include <cstdio>
#define ls (o << 1)
#define rs (o << 1 | 1)
using namespace std;
const int N = 1E6 + 7;
long long a[N];
struct SGT{
    long long mx, sec, sum, tag;
    int num;
}t[N << 2];
void pushup(int o){
    t[o].sum = t[ls].sum + t[rs].sum;
    if(t[ls].mx == t[rs].mx){
        t[o].mx = t[ls].mx;
        t[o].sec = max(t[ls].sec, t[rs].sec);
        t[o].num = t[ls].num + t[rs].num;
    }
    else if(t[ls].mx > t[rs].mx){
        t[o].mx = t[ls].mx;
        t[o].sec = max(t[ls].sec, t[rs].mx);
        t[o].num = t[ls].num;
    }
    else{
        t[o].mx = t[rs].mx;
        t[o].sec = max(t[rs].sec, t[ls].mx);
        t[o].num = t[rs].num;
    }
}
void change(int o, long long tag){
    if(t[o].mx <= tag) return;
    t[o].sum -= (t[o].mx - tag) * t[o].num;
    t[o].mx = t[o].tag = tag;
}
void pushdown(int o){
    if(t[o].tag == -1) return;
    change(ls, t[o].tag); change(rs, t[o].tag);
    t[o].tag = -1;
}
void build(int o, int l, int r){
    t[o].tag = -1; t[o].sec = -1;
    if(l == r){
        t[o].mx = t[o].sum = a[l];
        t[o].num = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(ls, l, mid); build(rs, mid + 1, r);
    pushup(o);
}
void update(int o, int l, int r, int cl, int cr, int k){
    if(cl > r || cr < l) return;
    if(cl <= l && r <= cr && t[o].sec <= k){
        change(o, k);
        return;
    }
    pushdown(o);
    int mid = (l + r) >> 1;
    if(cl <= mid) update(ls, l, mid, cl, cr, k);
    if(cr > mid) update(rs, mid + 1, r, cl, cr, k);
    pushup(o);
}
long long qrysum(int o, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return t[o].sum;
    pushdown(o);
    int mid = (l + r) >> 1;
    long long res = 0;
    if(ql <= mid) res += qrysum(ls, l, mid, ql, qr);
    if(qr > mid) res += qrysum(rs, mid + 1, r, ql, qr);
    return res;
}
long long qrymx(int o, int l, int r, int ql, int qr){
    if(ql <= l && r <= qr) return t[o].mx;
    pushdown(o);
    int mid = (l + r) >> 1;
    long long res = -1;
    if(ql <= mid) res = max(res, qrymx(ls, l, mid ,ql, qr));
    if(qr > mid) res = max(res, qrymx(rs, mid + 1, r, ql, qr));
    return res;
}
void solve(){
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    int opt, x, y, k;
    for(int i = 1; i <= m; i++){
        scanf("%d%d%d", &opt, &x, &y);
        if(opt == 0){
            scanf("%d", &k);
            update(1, 1, n, x, y, k);
        }
        else if(opt == 1){
            printf("%lld\n", qrymx(1, 1, n, x, y));
        }
        else if(opt == 2){
            printf("%lld\n", qrysum(1, 1, n, x, y));
        }
    }
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        solve();
    }
}
