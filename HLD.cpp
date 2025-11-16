#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pq priority_queue
#define bs binary_search
#define int ll
const ll sized = 1e6;
const ll N = 1e7;
const ll inf = 1e18;
const ll MOD = 123456789;
const ll LOG = 20;
vector<int> adj[sized];
int parent[sized], depth[sized], heavy[sized];
int head[sized],pos[sized],subtree_size[sized];
int cur_pos=0;

int baseArray[sized];
int valueAtNode[sized];

int segtree[4*sized];

int dfs1(int u){
    subtree_size[u]=1;
    int max_sub_size=0;

    for(int v: adj[u]){
        if(v==parent[u]) continue;

        parent[v]=u;
        depth[v]=depth[u]+1;

        dfs1(v);
        subtree_size[u]+=subtree_size[v];
        if(subtree_size[v]>max_sub_size){
            max_sub_size=subtree_size[v];
            heavy[u]=v;
        }
    }
    return subtree_size[u];
}

void dfs2(int u,int h){
    head[u]=h;
    pos[u]= ++ cur_pos;
    baseArray[cur_pos]=valueAtNode[u];

    if(heavy[u]!=0){
        dfs2(heavy[u],h);
    }
    for(auto v: adj[u]){
        if(v!=parent[u] && v !=heavy[u]){
            dfs2(v,v);
        }
    }
}

long long merge(long long a, long long b) { return a + b; }

void build(int id, int l, int r) {
    if (l == r) {
        segtree[id] = baseArray[l];
        return;
    }
    int mid = (l+r)/2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    segtree[id] = merge(segtree[id*2], segtree[id*2+1]);
}

void update_seg(int id, int l, int r, int idx, long long val) {
    if (l == r) {
        segtree[id] = val;
        return;
    }
    int mid = (l+r)/2;
    if (idx <= mid) update_seg(id*2, l, mid, idx, val);
    else update_seg(id*2+1, mid+1, r, idx, val);

    segtree[id] = merge(segtree[id*2], segtree[id*2+1]);
}

long long query_seg(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return segtree[id];
    int mid = (l+r)/2;
    return merge(
        query_seg(id*2, l, mid, u, v),
        query_seg(id*2+1, mid+1, r, u, v)
    );
}

int query_path(int u,int v){
    int res=0;

    while(head[u]!=head[v]){
        if (depth[head[u]] < depth[head[v]])
            swap(u, v);

        int head_u=head[u];
        res+=query_seg(1,1,cur_pos,pos[head_u],pos[u]);

        u=parent[head_u];
    }

    // khi 2 bên cùng 1 đoạn
    if(depth[u]>depth[v]) swap(u,v);
    res+=query_seg(1,1,cur_pos,pos[u],pos[v]);
    return res;
}

void update_node(int u, long long new_value) {
    valueAtNode[u] = new_value;
    update_seg(1, 1, cur_pos, pos[u], new_value);
}
main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("main.inp","r",stdin);
	// freopen("main.out","w",stdout);
    int n,q;
    cin>>n>>q;

    for(int i=1;i<=n;i++){
        cin>>valueAtNode[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[1]=0;
    parent[1]=0;
    dfs1(1);
    dfs2(1,1);
    build(1,1,cur_pos);
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int u; long long val;
            cin >> u >> val;
            update_node(u, val);
        } else {
            int u, v;
            cin >> u >> v;
            cout << query_path(u, v) << "\n";
        }
    }

    return 0;
}