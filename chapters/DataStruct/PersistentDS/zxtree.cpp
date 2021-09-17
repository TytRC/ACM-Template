/*
给定 n 个整数构成的序列 a，将对于指定的闭区间 [l,r] 查询其区间内的第 k 小值。
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std; 
const int N=2e5+7;
struct PST{
	int ls,rs;
	int num;
}t[N*20];
int a[N],b[N];
int rt[N],cnt;
void pushup(int o){
	t[o].num=t[t[o].ls].num+t[t[o].rs].num;
}
void build(int &o,int l,int r){
	o=++cnt;
	if(l==r){
		t[o].num=0;
		return;
	}
	int mid=(l+r)>>1;
	build(t[o].ls,l,mid);build(t[o].rs,mid+1,r);
	pushup(o);
}
int clone(int x){
	int r=++cnt;
	t[r]=t[x];
	return r;
}
void update(int &o,int l,int r,int c){
	o=clone(o);
	if(l==r){
		t[o].num++;
		return;
	}
	int mid=(l+r)>>1;
	if(c<=mid) update(t[o].ls,l,mid,c);
	else update(t[o].rs,mid+1,r,c);
	pushup(o);
}
int query(int ox,int oy,int l,int r,int k){
	if(l>=r) return l;
	int mid=(l+r)>>1;
	int z=t[t[oy].ls].num-t[t[ox].ls].num;
	if(z>=k) return query(t[ox].ls,t[oy].ls,l,mid,k);
	else return query(t[ox].rs,t[oy].rs,mid+1,r,k-z);
}
int main(){
	int i,j,k,m,n,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int d=unique(b+1,b+n+1)-b-1;
	build(rt[0],1,d);
	for(i=1;i<=n;i++){
		x=lower_bound(b+1,b+d+1,a[i])-b;
		rt[i]=rt[i-1];
		update(rt[i],1,d,x);
	}
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&k);
		printf("%d\n",b[query(rt[x-1],rt[y],1,d,k)]);
	}
	return 0;
}