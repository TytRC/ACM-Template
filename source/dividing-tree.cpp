#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1E5 + 7;
int sorted[N];
int t[20][N], toLeft[20][N];
void build(int dep, int l, int r){
    if(l == r) return;
    int mid = (l + r) >> 1;
    int sup = mid - l + 1;
    for(int i = l; i <= r; i++){
        if(t[dep][i] < sorted[mid]) sup--;
    }
    int sl = l, sr = mid + 1;
    for(int i = l; i <= r; i++){
        if(i == l) toLeft[dep][i] = 0;
        else toLeft[dep][i] = toLeft[dep][i - 1];
        if(t[dep][i] < sorted[mid] || (t[dep][i] == sorted[mid] && sup > 0)){
            toLeft[dep][i]++;
            t[dep + 1][sl++] = t[dep][i];
            if(t[dep][i] == sorted[mid]) sup--;
        }
        else t[dep + 1][sr++] = t[dep][i];
    }
    build(dep + 1, l, mid); build(dep + 1, mid + 1, r);
}
int query(int dep, int l, int r, int ql, int qr, int k){
    if(l == r) return t[dep][l];
    int mid = (l + r) >> 1;
    int le, qtl;
    le = (ql == l)?0:toLeft[dep][ql - 1];
    qtl = toLeft[dep][qr] - le;
    if(k <= qtl) return query(dep + 1, l, mid, l + le, l + le + qtl - 1, k);
    else return query(dep + 1, mid + 1, r, mid + ql - l - le + 1, mid + qr - l - le - qtl + 1, k - qtl);
}
int main(){
    int n, m, l, r, k;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &t[0][i]), sorted[i] = t[0][i];
    sort(sorted + 1, sorted + n + 1);
    build(0, 1, n);
    for(int i = 1; i <= m; i++){
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", query(0, 1, n, l, r, k));
    }
    return 0;
}
