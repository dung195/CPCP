#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pq priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define bs binary_search
const ll sized = 1e6;
const ll N = 1e7;
const ll inf = 1e18;
const ll MOD = 123456789;
const ll LOG = 20;
//https://oj.vnoi.info/problem/lis
int F[sized];
int a[sized];
main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("main.inp","r",stdin);
	// freopen("main.out","w",stdout);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    F[1]=1;
    int res=1;
    for(int i=2;i<=n;i++){
        int l=1,r=res,j=0;
        while(l<=r){
            int m=(l+r)/2;
            if(a[i]>a[F[m]]){
                j=m;
                l=m+1;
            }
            else r=m-1;
        }
        if(j==res) F[++res]=i;
        if(a[i]<a[F[j+1]]) F[j+1]=i;
    }
    cout<<res<<endl;
    return 0;
}