//TEMPLATE.CPP
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

//typedef
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
typedef std::vector< pii > vii;
typedef std::vector< ll > vll;
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
int power(int x, int n) //function to calculate x raise to power n 
{
	int result = 1;
	while (n > 0)
	{
		if (n % 2 == 1)
			result = result * x;
		x = x * x;
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

bool check_prime(long long n)
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


//_______________________________-code starts-______________________________________________________________________________
 



int main()
{
    
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int arr[n];
        map<int ,int>ctr;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            ctr[arr[i]]++;
        }
        
        
        
        
    }

    return 0;
}
