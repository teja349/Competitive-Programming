//IDEA: convert to manhattan distance and then solve it using prefix sums

//teja349
#include <bits/stdc++.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <iomanip> 
//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val

using namespace std;
#define f(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) f(i,0,n)
#define fd(i,a,b) for(i=a;i>=b;i--)
#define pb push_back
#define mp make_pair
#define vi vector< int >
#define vl vector< ll >
#define ss second
#define ff first
#define ll long long
#define pii pair< int,int >
#define pll pair< ll,ll >
#define sz(a) a.size()
#define inf (1000*1000*1000+5)
#define all(a) a.begin(),a.end()
#define tri pair<int,pii>
#define vii vector<pii>
#define vll vector<pll>
#define viii vector<tri>
#define mod (1000*1000*1000+7)
#define pqueue priority_queue< int >
#define pdqueue priority_queue< int,vi ,greater< int > >

//std::ios::sync_with_stdio(false);   
vl vec,vec1;
ll x[123456],y[123456],xx[123456],yy[123456];
map<ll,ll> map1,mapi;
ll pre[123456],pre1[123456];
int main(){
    std::ios::sync_with_stdio(false);
    int n;
    cin>>n;
    ll i,j,k;
    
    
    rep(i,n){
    	cin>>xx[i]>>yy[i];
    	x[i]=(xx[i]+yy[i]);
    	y[i]=xx[i]-yy[i];
    	vec.pb(x[i]);
    	vec1.pb(y[i]);
    	//cout<<x[i]<<endl;
    }
    sort(all(vec1));
    sort(all(vec));
   
    //mini*=inf;
    pre[0]=vec[0];
    pre1[0]=vec1[0];
    f(i,1,n){

    	pre[i]=vec[i]+pre[i-1];
    	pre1[i]=vec1[i]+pre1[i-1];
    	//cout<<i<<" "<<vec[i]<<endl;
    }
    rep(i,n){
    	mapi[vec[i]]=i;
    	map1[vec1[i]]=i;
    }

    ll mini=inf;
    mini*=inf;
    ll ans=0;
    rep(j,n){
    	i=mapi[x[j]];
    	ans=pre[n-1]-(n-i-1)*x[j]+(i+1)*x[j]-2*pre[i];
    	//cout<<ans<<endl;
    	i=map1[y[j]];
    	ans+=pre1[n-1] - (n-i-1)*y[j]+(i+1)*y[j]-2*pre1[i];
    	mini=min(mini,ans);
    }
    cout<<mini/2<<endl;



    return 0;  
    
}

