
// IDEA: do sqrt decomposition with fft

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
#pragma GCC optimize "-O3"
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
#define flush fflush(stdout) 
#define primeDEN 727999983
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
template <typename T>
void printvec(vector<T>& vec){
	for(int i=0;i<vec.size();i++){
		cout<<vec[i]<<" ";
	}
	cout<<endl;
}
#define ld long double
const ld pi=4.0*atan(1.0);
struct base{
	ld x,y;
	base(){
		x=0;
		y=0;
	}
	base(ld xx){
		x=xx;
		y=0;
	}
	base(ld xx,ld yy){
		x=xx;
		y=yy;
	}
	base operator + (base &o){
		return base(x+ o.x,y+o.y);
	}
	base operator - (base &o){
		return base(x-o.x,y-o.y);
	}
	base operator * (base &o){
		return base(x*o.x-y*o.y,x*o.y +o.x*y);
	}
};

int N,K;
int rev[1234567];
int pre(){
	int i,ans=0,j;
	rep(i,N){
		ans=0;
		rep(j,K){
			if((1<<j)&i){
				ans+=(1<<(K-1-j));
			}
		}
		rev[i]=ans;
	}
}

int fft(base a[],bool inv){
	int i,gap,j;
	rep(i,N){
		if(rev[i]<i){
			swap(a[rev[i]],a[i]);
		}
	}
	base w,cur,u,v;
	for(gap=1;gap<N;gap*=2){
		w=base(cos(pi/gap), sin(pi/gap*(inv?-1:1)));
		for(i=0;i<N;i+=2*gap){
			cur=base(1,0);
			rep(j,gap){
				u=a[i+j];
				v=a[i+j+gap]*cur;
				a[i+j]=u+v;
				a[i+j+gap]=u-v;
				cur=cur*w;
				
			}
		}
	}
	return 0;
}

base a[1234567],b[1234567];
ll haha[123456],wow[123456];
ll B=6000;
base gg[1234567];
ll answ[112][412345];
int main(){
   // std::ios::sync_with_stdio(false);
    int t;
    scanf("%d",&t);
    while(t--){
    	int n,q;
    	int timer=clock();
    	//cin>>n>>q;
    	scanf("%d%d",&n,&q);
    	int i,j;
    	int val;
    	rep(i,n){
    		//val=i;
    		scanf("%d",&val);
    		a[i]=base(val,0);
    		haha[i]=val;
    	}
    	rep(i,n){
    		//val=i;
    		scanf("%d",&val);
    		b[i]=base(val,0);
    		wow[i]=val;
    	}
    	K=0;
    	while((1<<K)<=n) K++;
    	K++;
    	N=(1<<K);
    	f(i,n,N){
    		a[i]=base(0,0);
    	}
    	pre();
    	fft(a,0);
    	int block=1;
    	//int j;
    	while(B*block+B<=n){
    		// block++;
    		// continue;
    		rep(i,N){
    			gg[i]=base(0,0);
    		}
    		j=B-1;
    		f(i,B*block,B*block+B){
    			gg[j]=b[i];
    			//cout<<j<<" "<<gg[j].x<<endl;
    			j--;
    		}
    		fft(gg,0);
    		rep(i,N){
    			gg[i]=gg[i]*a[i];
    		}
    		fft(gg,1);
    		rep(i,N){
    			answ[block][i]=(gg[i].x/N)+0.5;
    			if(answ[block][i]==0)
    				continue;
    		}
    		block++;
    	}
    	int x,y,l,en,enx;
    	rep(i,q){
    		x=1;
    		y=1;
    		l=n;
    		scanf("%d%d%d",&x,&y,&l);
    		//continue;
    		x--;
    		y--;
    		en=y+l-1;
    		enx=x+l-1;
    		j=y;
    		ll ans=0;
    		int hh=y/B*B+B;
    		while(j<=en && j<hh){
    			//cout<<"dsa"<<endl;
    			ans+=haha[x]*wow[j];
    			x++;
    			j++;
    		}
    		if(y/B!=en/B){
    			j=en;
    			hh=en/B*B;
    			while(j>=hh){
    				ans+=haha[enx]*wow[j];
    				enx--;
    				j--;
    			}
    		}
    		f(j,y/B+1,en/B){
    			ans+=answ[j][x+B-1];
    			x+=B;
    		}
    		//cout<<ans<<endl;
    		printf("%lld\n",ans);
    	}  
    	//cout<<clock()-timer<<endl;
    }
    return 0;   
}

