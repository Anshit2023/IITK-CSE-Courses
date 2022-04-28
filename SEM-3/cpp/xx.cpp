#include <bits/stdc++.h>
using namespace std;

// Shortcuts for "common" data types in contests
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<char,char> pcc;
typedef pair<char,int> pci;
typedef pair<int,char> pic;
typedef vector<pii> vpii;
typedef set<int> si;
typedef set<ll> sll;
typedef map<int,int> mii;
typedef map<ll,ll> mll;
#define ff first
#define ss second
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(),v.rend()
#define rep(i, a, b) for(int i = a; i < b; i++)
#define repv(c, it) \
for(vll::iterator it = (c).begin(); it != (c).end(); it++)
#define repm(c, it) \
for(mll::iterator it = (c).begin(); it != (c).end(); it++)
#define inf 1000000007

int main() {
    //decreases the time taken by cin,cout.
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(0);
    
    ll t;
    cin>>t;
    
    while(t--)
    {
        ll n,k,x;
        cin>>n>>k>>x;
        ll ans=k;
        if(x>k)
        {
            ans=ans*pow(k-1,n-1);
            rep(i,1,n){ans=(((ans)%inf)*(k-1))%inf;}
            cout<<ans<<endl;
        }
        else
        {
            ll a[n][2];
            if(n==1){a[0][0]=k-1;a[0][1]=1;cout<<a[n-1][0]+a[n-1][1]<<endl;}
            if(n==2)
            {
                a[0][0]=k-1;a[0][1]=1;
                a[1][0]=(k-1)*(k-1);a[1][1]=k;
                cout<<a[n-1][0]+a[n-1][1]<<endl;
            }
            else
            {
            a[0][0]=k-1;a[0][1]=1;
            a[1][0]=(k-1)*(k-1);a[1][1]=k;
            rep(i,2,n)
            {
                a[i][1]=(( (a[i-1][0])%inf + (a[i-1][1])%inf )%inf );
                a[i][0]=( (a[i-1][0]*(k-1))%inf + (a[i-1][1]*k)%inf - a[i][1] + inf)%inf;
                
            }
                cout<<(a[n-1][0]+a[n-1][1])%inf<<endl;
            }
        }
       
       
    }
    
	
	return 0;
}