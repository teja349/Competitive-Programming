// Same idea as discussed here. http://codeforces.com/blog/entry/4018

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
int cnt=0;
int visit[423456];
int haha[423456],dp[423456],pre[423456],post[423456],timer=0,par[423456];
vector<vi> adj(423456),rev(423456);
int dfs(int cur){
	pre[cur]=timer++;
	cnt++;
	visit[cur]=1;
	int i;
	rep(i,adj[cur].size()){
		if(!visit[adj[cur][i]]){
			par[adj[cur][i]]=cur;
			dfs(adj[cur][i]);
		}
	}
	post[cur]=timer++;

}
int revdfs(int cur){
	cnt++;
	visit[cur]=1;
	int i;
	rep(i,rev[cur].size()){
		if(!visit[rev[cur][i]]){
			revdfs(rev[cur][i]);
		}
	}
	return 0;
}
int flag=0;
int dpdfs(int cur){
	int i;
	visit[cur]=1;
	dp[cur]=haha[cur];
	rep(i,adj[cur].size()){
		if(!visit[adj[cur][i]]){
			dpdfs(adj[cur][i]);
			dp[cur]+=dp[adj[cur][i]];
		}
	}
	if(cur!=0){
		if(dp[cur]!=1){

			flag=1;
		}
	}
	else{
		if(dp[cur]!=0){
			
			flag=1;
		}
	}
	return 0;

}
int main(){
    std::ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
    	timer=0;
    	par[0]=-1;
    	vii vec;
    	vec.clear();
    	int n,m;
    	cin>>n>>m;
    	int i,u,v;
    	rep(i,n){
    		adj[i].clear();
    		rev[i].clear();
    	}
    	rep(i,m){
    		cin>>u>>v;
    		vec.pb(mp(u,v));
    		adj[u].pb(v);
    		rev[v].pb(u);
    	}
    	cnt=0;
    	rep(i,n){
    		visit[i]=0;
    		haha[i]=0;
    	}
    	dfs(0);
    	if(cnt!=n){
    		cout<<"NO"<<endl;
    		continue;
    	}
    	rep(i,n){
    		visit[i]=0;
    		haha[i]=0;
    	}
    	cnt=0;
    	revdfs(0);
    	if(cnt!=n){
    		cout<<"NO"<<endl;
    		continue;
    	}
    	flag=0;
    	//cout<<"Das"<<endl;
    	rep(i,m){
    		if(par[vec[i].ss]==vec[i].ff)
    			continue;
    		if(pre[vec[i].ss]<pre[vec[i].ff] && post[vec[i].ff]<post[vec[i].ss]){
    			haha[vec[i].ff]++;
    			haha[vec[i].ss]--;
    		}
    		else{
    			flag=1;
    		}
    	}
    	if(flag){
    		cout<<"NO"<<endl;
    		continue;
    	}
    	rep(i,n){
    		visit[i]=0;
    	}
    	flag=0;
    	dpdfs(0);
    	if(flag){
    		cout<<"NO"<<endl;
    	}
    	else{
    		cout<<"YES"<<endl;
    	}
    }
    return 0;     
}

