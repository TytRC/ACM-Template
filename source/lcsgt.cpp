#include <iostream>
#include <cstdio>
#define ls (o << 1)
#define rs (o << 1 | 1)
using namespace std;
const int N = 1E5 + 7;
const int M = 39989;
const int M2 = 1E9;
struct Line{
    double k, b;
}ll[N];
int cnt;
void add(int x0, int y0, int x1, int y1){
    cnt++;
    if(x0 == x1){
        ll[cnt].k = 0; ll[cnt].b = max(y0, y1);
    }
    else{
        ll[cnt].k = 1.0 * (y1 - y0) / (x1 - x0);
        ll[cnt].b = y0 - ll[cnt].k * x0;
    }
}
int t[M << 2];
double cal(int x, int id){
    return ll[id].k * x + ll[id].b;
}
void update(int o, int l, int r, int xl, int xr, int id){
    if(xl > r || xr < l) return;
    int mid = (l + r) >> 1;
    int nw = t[o];
    double ynw = cal(mid, nw), yid = cal(mid, id);
    if(xl <= l && r <= xr){
        if(l == r){
            if(ynw < yid) t[o] = id;
            return;
        }
        if(ll[nw].k == ll[id].k){
            if(ll[nw].b < ll[id].b) t[o] = id;
        }
        else if(ll[nw].k < ll[id].k){
            if(ynw >= yid){
                update(rs, mid + 1, r, xl, xr, id);
            }
            else{
                t[o] = id;
                update(ls, l, mid, xl, xr, nw);
            }
        }
        else if(ll[nw].k > ll[id].k){
            if(ynw >= yid){
                update(ls, l, mid, xl, xr, id);
            }
            else{
                t[o] = id;
                update(rs, mid + 1, r, xl, xr, nw);
            }
        }
        return;
    }
    if(xl <= mid) update(ls, l, mid, xl, xr, id);
    if(xr > mid) update(rs, mid + 1, r, xl, xr, id);
}
typedef pair<double, int> pdi;
bool cmp(const pdi &a, const pdi &b){
    if(a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}
pdi query(int o, int l, int r, int x){
    if(x > r || x < l) return {0, 0};
    pdi res = {cal(x, t[o]), t[o]};
    if(l == r) return res;
    int mid = (l + r) >> 1;
    pdi tmp;
    if(x <= mid) tmp = query(ls, l, mid, x);
    else tmp = query(rs, mid + 1, r, x);
    if(cmp(tmp, res)) res = tmp;
    return res;
}
int main(){
    int n, op, k, x, x0, y0, x1, y1, xx0, yy0, xx1, yy1;
    scanf("%d", &n);
    int ans = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d", &op);
        if(op == 0){
            scanf("%d", &k);
            x = (k + ans - 1) % M + 1;
            ans = query(1, 1, M, x).second;
            printf("%d\n", ans);
        }
        else{
            scanf("%d%d%d%d", &xx0, &yy0, &xx1, &yy1);
            x0 = (xx0 + ans - 1) % M + 1;
            x1 = (xx1 + ans - 1) % M + 1;
            y0 = (yy0 + ans - 1) % M2 + 1;
            y1 = (yy1 + ans - 1) % M2 + 1;
            if(x0 > x1){
                swap(x0, x1);
                swap(y0, y1);
            }
            add(x0, y0, x1, y1);
            update(1, 1, M, x0, x1, cnt);
        }
    }
    return 0;
}
