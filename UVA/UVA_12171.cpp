// IDEA : construct the grid and then do dfs from 0,0,0. all those unreachable contribute to volume. All those with air on one side and solid on one side contribute to area. Naively it wont pass, we need to coordinate compress.

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
int a[55][7];
int grid[312][312][312];
int visit[312][312][312];
int counter[4];
int valid(int a,int b,int c){
    if(a<0 || a>=counter[0])
        return 0;
    if(b<0 || b>=counter[1])
        return 0;
    if(c<0 || c>=counter[2])
        return 0;
    return 1;
}
int dfs(int a,int b,int c){
    visit[a][b][c]=1;
    if( valid(a,b,c-1) && !grid[a][b][c-1] && !visit[a][b][c-1]){
        dfs(a,b,c-1);
    }
    if( valid(a,b,c+1) && !grid[a][b][c+1] && !visit[a][b][c+1]){
        dfs(a,b,c+1);
    }

    if( valid(a-1,b,c) && !grid[a-1][b][c] && !visit[a-1][b][c]){
        dfs(a-1,b,c);
    }
    if( valid(a+1,b,c) && !grid[a+1][b][c] && !visit[a+1][b][c]){
        dfs(a+1,b,c);
    }

    if( valid(a,b+1,c) && !grid[a][b+1][c] && !visit[a][b+1][c]){
        dfs(a,b+1,c);
    }
    if( valid(a,b-1,c) && !grid[a][b-1][c] && !visit[a][b-1][c]){
        dfs(a,b-1,c);
    }
    return 0;
}
vector<map<int,int> > mapi(3),inv(3);
int main(){
    //std::ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
    	int n;
    	cin>>n;
        int i,j,k;
        rep(i,3){
            mapi[i].clear();
            inv[i].clear();
        }
    	rep(i,n){
    		rep(j,6){
                //cin>>a[i][j];
                scanf("%d",&a[i][j]);
                if(j>2){
                    a[i][j]+=a[i][j-3];
                    a[i][j]--;
                  //  cout<<a[i][j]<<endl;
                }
                f(k,-1,2){
                    // if(j/3==1 && i==-1){
                    //     continue;
                    // }
                    // if(j/3==0 && i==1){
                    //     continue;
                    // }
                    mapi[j%3][a[i][j]-k]=1;
                }
            }
        }
        map<int,int>::iterator it;
        rep(i,3){
            counter[i]=0;
            //cout<<mapi[i].size()<<endl;
            for(it=mapi[i].begin();it!=mapi[i].end();it++){
                it->ss=counter[i]++;
                inv[i][counter[i]-1]=it->ff;
            }
            counter[i]++;
        }
       
        rep(i,counter[0]){
            rep(j,counter[1]){
                rep(k,counter[2]){
                    grid[i][j][k]=0;
                    visit[i][j][k]=0;
                }
            }
        }
        rep(i,n){
            rep(j,6){
                a[i][j]=mapi[j%3][a[i][j]];
            }
            f(j,a[i][2],a[i][5]+1){
                grid[a[i][0]][a[i][1]][j]++;
                grid[a[i][3]+1][a[i][1]][j]--;
                grid[a[i][0]][a[i][4]+1][j]--;
                grid[a[i][3]+1][a[i][4]+1][j]++;
            }
        }
        
        rep(k,counter[2]){
            f(i,1,counter[0]){
                f(j,1,counter[1]){
                    grid[i][j][k]+=grid[i][j-1][k]+grid[i-1][j][k]-grid[i-1][j-1][k];
                    
                    
                }
                
            }
        }
        dfs(0,0,0);
        ll area=0,volume=0;
        int flag=1;
        rep(k,counter[2]){
            rep(i,counter[0]){
                rep(j,counter[1]){
                    //assert(visit[i][j][k]+grid[i][j][k]==1);
                    
                    if(!visit[i][j][k]){
                        if(visit[i-1][j][k]){
                            area+= (inv[1][j+1]-inv[1][j])*(inv[2][k+1]-inv[2][k]);
                        }
                        if(visit[i+1][j][k]){
                            area+= (inv[1][j+1]-inv[1][j])*(inv[2][k+1]-inv[2][k]);
                        }
                        if(visit[i][j-1][k]){
                            area+= (inv[0][i+1]-inv[0][i])*(inv[2][k+1]-inv[2][k]);
                        }
                        if(visit[i][j+1][k]){
                            area+= (inv[0][i+1]-inv[0][i])*(inv[2][k+1]-inv[2][k]);
                        }
                        if(visit[i][j][k-1]){
                            area+= (inv[0][i+1]-inv[0][i])*(inv[1][j+1]-inv[1][j]);
                        }
                        if(visit[i][j][k+1]){
                            area+= (inv[0][i+1]-inv[0][i])*(inv[1][j+1]-inv[1][j]);
                        }
                        volume+=(inv[0][i+1]-inv[0][i])*(inv[1][j+1]-inv[1][j])*(inv[2][k+1]-inv[2][k]);                        
                        //cout<<volume<<endl;
                    }
                }
                
            }
            //cout<<k<<" "<<volume<<endl;
            
        }
        printf("%d %d\n",area,volume);

    }
    return 0;     
}

