#include <bits/stdc++.h>
using namespace std;
 
double calc(double a, double b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}
 
int main() {
    string s,s1;
    cin>>s1;
    int n=5;
    double arr1[n],arr2[n],arr3[n],arr4[n],z[n][4];
    string z1[n],z2[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr1[i];
        z[i][0]=arr1[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>arr2[i];
        z[i][1]=arr2[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>arr3[i];
        z[i][2]=arr3[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>arr4[i];
        z[i][3]=arr4[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>z1[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>z2[i];
    }
    s[0]=s1[2];
    s[1]=s1[5];
    s[2]=s1[8];
    int k[4]={0};
    k[0]=int(s1[1])-int('1');
    k[1]=int(s1[4])-int('1');
    k[2]=int(s1[7])-int('1');
    k[3]=int(s1[10])-int('1');
    double ans,a,b,c,d,a1,b1,c1,d1;
    for(int i=0;i<n;i++)
    {
        a=z[i][k[0]];
        b=z[i][k[1]];
        c=z[i][k[2]];
        d=z[i][k[3]];
        if(s[0]<s[1])
        {
            if(s[1]>=s[2])
            {
                b1=calc(b,c,s[1]);
                if(s[0]>=s[2])
                {
                    a1=calc(a,b1,s[0]);
                    d1=calc(a1,d,s[2]);
                    ans=d1;
                }
                else
                {
                    c1=calc(b1,d,s[2]);
                    a1=calc(a,c1,s[0]);
                    ans=a1;
                }
            }
            else if(s[1]<s[2])
            {
                c1=calc(c,d,s[2]);
                b1=calc(b,c1,s[1]);
                a1=calc(a,b1,s[0]);
                ans=a1;
            }
        }
        else if(s[0]>=s[1])
        {
            a1=calc(a,b,s[0]);
            if(s[1]>=s[2])
            {
                b1=calc(a1,c,s[1]);
                c1=calc(b1,d,s[2]);
                ans=c1;
            }
            else if(s[1]<s[2])
            {
                c1=calc(c,d,s[2]);
                b1=calc(a1,c1,s[1]);
                ans=b1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
