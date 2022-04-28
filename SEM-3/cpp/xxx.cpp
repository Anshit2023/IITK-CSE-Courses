#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fuck vector<int>
#define ff push_back
#define mp make_pair
#define pi 3.141592653589793238
#define none(i,a,b) for(int i=a;i<b;i++)
#define rnone(i,a,b) for(int i=a;i>=b;i--)
#define ll unsigned int
#define test int t;cin>>t; while(t--)
#define en '\n'
typedef pair<int, int>     pii;
typedef vector<pii>       fucki;
typedef long double ld;
#define INF (1e18+5)
#define inf (1e9+5)
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void print(T t, V... v) {_print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif


const int gf = 1e6 + 9;

int32_t main()
{
	
	//__________-code starts-________________


	int t;
	cin >> t;
	for (int tet = 1; tet <= t; tet++){
		int n, c; cin >> n >> c;
		int a[n];
		none(i, 0, n){
			a[i] = i + 1;
		}
		int mkb = 0;

		fuck v;
		do {
			int chut = 0;
			int b[n];
			none(i, 0, n)b[i] = a[i];
			none(i, 0, n - 1){
				int pos;
				int ludo = inf;
				none(j, i, n){
					if (b[j] < ludo){
						ludo = b[j];
						pos = j;
					}
				}
				chut += (pos - i + 1);
				reverse(b + i, b + pos + 1);
			}
			if (chut == c){
				mkb = 1;
				cout << "Case #" << tet << ": ";
				none(i, 0, n)
				cout << a[i] << " ";
				cout << en;
				break;
			}
			v.ff(chut);
		} while (next_permutation(a, a + n));
		if (mkb == 0){
			cout << "Case #" << tet << ": ";
			cout << "IMPOSSIBLE" << en;
		}
	}
	return 0;
}