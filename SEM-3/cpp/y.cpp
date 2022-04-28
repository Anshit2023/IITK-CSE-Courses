
#include <bits/stdc++.h>
#include <map>
#include <algorithm> 
#include <vector> 
#include <string.h> 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <chrono> 
#include <thread> 
#include <iomanip>
#include <typeinfo>
#include <algorithm>
//define
#define trav(i,v)   for(auto i: v)
#define fr(i,n)    for(int i=0;i<n;i++)
#define foru(i,k,n) for(int i=k;i<=n;i++)
#define ford(i,k,n) for(int i=k;i>=n;i--)
#define se second
#define fi first
#define pb push_back
#define mp make_pair
#define all(v)  v.begin(), v.end()
#define itn int 
#define INF (1e18+5)
#define int long long
#define fill(a, b) memset(a, b, sizeof(a))
//typedef
//typedef long long int ll;
typedef unsigned int ull;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector< pii > vii;
typedef std::vector< int > vll;
typedef std::vector< std::pair < pii, int > > vpp;
 
// const long long MOD = 1000000007;
const long long MOD = 998244353;
const long long inf = 1000000000000000000;
 
using namespace std;

bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
}

bool cmp(pair<string, int>& a, 
         pair<string, int>& b) 
{ 
    return a.second < b.second; 
} 

int power(int x, int n) //function to calculate x raise to power n 
{
	int result = 1;
	while (n > 0)
	{
		if (n % 2 == 1)
			result = (result * x)%1000000007;
		x = (x * x)%1000000007;
		n = n / 2;
	}
	return result;
}
int fact(int n); 
int nCr(int n, int r) 
{ 
    return fact(n) / (fact(r) * fact(n - r)); 
} 
  // Returns factorial of n 
int fact(int n) 
{ 
    int res = 1; 
    for (int i = 2; i <= n; i++) 
        res = res * i; 
    return res; 
} 

bool isPrime(long long n)
{
	int flag = 0;
	for (long long i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			flag = 1;
			break;
		}
	}
	if (n == 1)
		return false;
	else if (flag == 0 || n == 2 || n == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
 
}


//_____________________________-code starts-______________________________________________________________________________

int gcd( int a,  int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers 
int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}
int maxi;
void fog(int arr[],int a,int b,int x,int d[]){
	if(a>b)return;
	//maxi=max(x,maxi);
	int maxi=-1, it=-1;
	for(int i=a;i<b+1;i++){
		if(maxi<arr[i]){maxi=arr[i];it=i;}
	}
	d[it]=x;
	fog(arr,a,it-1,x+1,d);
    fog(arr,it+1,b,x+1,d);

}


// void fun(int arr[],int k,int j, int x) {
// 	int flag=0;
// 	int y;
// 			for(int i=k;i<j;i++){
// 				if(arr[i]==x){
// 					flag=1;
// 					 y=i;
// 				}
// 				if(flag){
// 					v.pb(arr[i]);
// 				}
// 			}
// 			fun(arr,k,y,x-1);
// 		}
		vector<int> v;
void primeFactors(int n)  
{  
    // Print the number of 2s that divide n  
    while (n % 2 == 0)  
    {  
        v.pb(2);   
        n = n/2;  
    }  
  
    // n must be odd at this point. So we can skip  
    // one element (Note i = i +2)  
    for (int i = 3; i <= sqrt(n); i = i + 2)  
    {  
        // While i divides n, print i and divide n  
        while (n % i == 0)  
        {  
            v.pb(n);  
            n = n/i;  
        }  
    }  
  
    // This condition is to handle the case when n  
    // is a prime number greater than 2  
    if (n > 2)  
        v.pb(n); 
}  

bool ss[10000];
int32_t main()
{
int t;
cin>>t;
while(t--){
    int n;
    cin>>n;
    int arr[n];
    int sum=0;
    fr(i,n){cin>>arr[i];}
    int flag=1;
    int count=0;
    fr(i,n)if(arr[i]==1){count=i;flag=0;break;}
    if(flag==1){
    fr(i,n){
        cout<<2*n;
    }}
    else{
        cout<<2*n-2-count;
    }
}

}
