#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int root, top;
struct Node {
    int	val, sz, cnt, fa, ch[2];
} tree[MAXN << 2];
struct Splay {
//    void attach(int x, int y, int d) {
//        if(x) tree[x].ch[d] = y;
//        if(y) tree[y].fa = x;
//    }
    int which(int x) {
        return tree[tree[x].fa].ch[1] == x;
    }
    void clear(int rt) {
        tree[rt].val = tree[rt].sz = tree[rt].cnt = tree[rt].fa = tree[rt].ch[0] = tree[rt].ch[1] = 0;
    }
    void maintain(int rt) {
        tree[rt].sz = tree[tree[rt].ch[0]].sz + tree[tree[rt].ch[1]].sz + tree[rt].cnt;
    }
    void rotate(int x) {
        int p = tree[x].fa;
        int g = tree[p].fa;
        int d = which(x);
//        attach(p, tree[x].ch[d ^ 1], d);
//        attach(x, p, d ^ 1);
//        attach(g, x, p == tree[g].ch[1]);
		tree[p].ch[d] = tree[x].ch[d ^ 1];
        if(tree[x].ch[d ^ 1]) tree[tree[x].ch[d ^ 1]].fa = p;
        tree[x].ch[d ^ 1] = p;
        tree[p].fa = x;
        tree[x].fa = g;
        if(g) tree[g].ch[p == tree[g].ch[1]] = x;
        maintain(p);
        maintain(x);
    }
    void splay(int x, int &rt) {
        int goal = tree[rt].fa;
        for(int p = tree[x].fa; p != goal; rotate(x), p = tree[x].fa) {
            if(tree[p].fa != goal) {
                rotate(which(x) == which(p) ? p : x);
            }
        }
        rt = x;
    }
    void insert(int &rt, int key) {
        int u = rt, fa = 0;
        for(; u && tree[u].val != key; fa = u, u = tree[u].ch[tree[u].val < key]);
        if(u) {
            tree[u].cnt++;
        } else {
            u = ++top;
            if(fa) {
                tree[fa].ch[tree[fa].val < key] = u;
                
            }
            tree[u].ch[0] = tree[u].ch[1] = 0;
            tree[u].val = key; tree[u].sz = tree[u].cnt = 1;
			tree[u].fa = fa;
        }
        splay(u, rt);
    }
    void find(int &rt, int key) {
        int u = rt;
        if(!u) return;
        for(; tree[u].ch[tree[u].val < key] && tree[u].val != key; u = tree[u].ch[tree[u].val < key]);
        splay(u, rt);
    }
    int upper(int & rt, int key) {
        find(rt, key);
        int u = rt;
        if(tree[u].val > key) return u;
        for(u = tree[u].ch[1]; tree[u].ch[0]; u = tree[u].ch[0]);
        splay(u, rt);
        return u;
    }
    int lower(int & rt, int key) {
        find(rt, key);
        int u = rt;
        if(tree[u].val < key) return u;
        for(u = tree[u].ch[0]; tree[u].ch[1]; u = tree[u].ch[1]);
        splay(u, rt);
        return u;
    }
    void remove(int & rt, int key) {
//    find(rt, key);
//    if(tree[rt].cnt > 1) {
//        tree[rt].cnt--;
//        maintain(rt);
//        return;
//    }
//    if(!tree[rt].ch[0] && !tree[rt].ch[1]) {
//        clear(rt);
//        rt = 0;
//        return;
//    }
//    if(!tree[rt].ch[0]) {
//        int cur = rt;
//        rt = tree[cur].ch[1];
//        tree[rt].fa = 0;
//        clear(cur);
//        return;
//    }
//    if(!tree[rt].ch[1]) {
//        int cur = rt;
//        rt = tree[cur].ch[0];
//        tree[rt].fa = 0;
//        clear(cur);
//        return;
//    }
//    int cur = rt;
//    int u = lower(rt, tree[cur].val);
//    tree[tree[cur].ch[1]].fa = u;
//    tree[u].ch[1] = tree[cur].ch[1];
//    clear(cur);
//    maintain(rt);
        int last = lower(rt, key);
        int next = upper(rt, key);
        splay(last, rt); splay(next, tree[rt].ch[1]);
        int del = tree[next].ch[0];
        if(tree[del].cnt > 1) {
            tree[del].cnt--;
            splay(del, rt);
        } else {
        	tree[next].ch[0] = 0;	
        	maintain(next);
            maintain(rt);

		}
    }
    int kth(int & rt, int k) {
        int u = rt;
        while(true) {
            int lch = tree[u].ch[0];
            if(tree[lch].sz + tree[u].cnt < k) {
                k -= tree[lch].sz + tree[u].cnt;
                u = tree[u].ch[1];
            } else {
                if(tree[lch].sz >= k) {
                    u = tree[u].ch[0];
                } else return u;
            }
        }
    }
    void print(int rt) {
        if(!rt) return;
        if(tree[rt].ch[0]) {
            cout << tree[rt].val << " " << tree[tree[rt].ch[0]].val << "\n";
        }
        if(tree[rt].ch[1]) {
            cout << tree[rt].val << " " << tree[tree[rt].ch[1]].val << "\n";
        }
        print(tree[rt].ch[0]);
        print(tree[rt].ch[1]);
    }
} bst;
int main() {

    root = 0;

    bst.insert(root, INT_MIN);
    bst.insert(root, INT_MAX);

    int n;
    int op,a;

    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        assert(!tree[root].fa);
        scanf("%d%d",&op,&a);
        switch(op) {
            case 1:
                bst.insert(root, a);
                break;
            case 2:
                bst.remove(root, a);
                break;
            case 3:
                bst.find(root, a);
                printf("%d\n", tree[tree[root].ch[0]].sz);
                break;
            case 4:
                printf("%d\n",tree[bst.kth(root, a + 1)].val);
                break;
            case 5:
                printf("%d\n",tree[bst.lower(root, a)].val);
                break;
            case 6:
                printf("%d\n",tree[bst.upper(root, a)].val);
                break;
        }
    }
    return 0;
}

