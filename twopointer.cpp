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
class Solution {
    public:
        vector<int>ans;
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            int i=0;
            int j=0;
            while(i<m && j<n){
                if(nums1[i]<=nums2[j]){
                    ans.push_back(nums1[i]);
                    i++;
                }
                else{
                    ans.push_back(nums2[j]);
                    j++;
                }
            }
            if(i<m){
                for(int k=i;k<m;k++){
                    ans.push_back(nums1[k]);
                }
            }
            if(j<n){
                for(int k=j;k<n;k++){
                    ans.push_back(nums2[k]);
                }
            }
            nums1.clear();
            for(int i=0;i<m;i++){
                nums1.push_back(ans[i]);
            }
        }
    };
main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // freopen("main.inp","r",stdin);
	// freopen("main.out","w",stdout);

    return 0;
}