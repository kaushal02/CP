#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i,n) for(ll i=0; i<(n); i++)
#define repp(i,a,b) for(ll i=a; i<=(b); i++)
#define IO(input_file_name) ifstream cin(input_file_name);ofstream cout("output.txt")
#define print(ans) cout<<"Case #"<<_t<<": "<<ans<<endl;
ll mod= 1e9 + 7;
ll arr[100005],prefix_s[100005],n,a,b;;

int main()
{
   //
/*1 5 8
2
1 0 777777777
7
1 777777 7777777
777777777
2 9 20
8 2
5 40 140
4 9 1 12 7
*/IO("input.txt");
    cout<<fixed<<setprecision(10);
    int t;
    cin>>t;
 int flag=0;
    repp(_t,1,t){
        flag=0;
        cin>>n>>a>>b;
        repp(i,1,n)
            cin>>arr[i];


        repp(i,1,n)prefix_s[i]=prefix_s[i-1]+arr[i];

        ll tmp=a%prefix_s[n];

        ll lef=a/prefix_s[n]*prefix_s[n];

        ll to=lower_bound(prefix_s,prefix_s+n+1,tmp)-prefix_s;

        double ans=0;

        if(to>0 && prefix_s[to]<b)

            ans+=((double)(prefix_s[to]-tmp))*(prefix_s[to]-prefix_s[to-1]+tmp-prefix_s[to-1])/(2*(b-a));

        else if(to>0)
        {
            ans += ((double)(b-tmp-lef))*(b-lef+tmp-2*prefix_s[to-1])/(2*(b-a));

           print(ans);continue;
        }



        repp(i,to+1,n){

            if((prefix_s[i])+lef>(b)){ans+=(double)(b-lef-prefix_s[i-1])*(b-lef-prefix_s[i-1])/(2*(b-a));

            flag=1;

            break;}

            ans+= (double)(prefix_s[i]-prefix_s[i-1])*(prefix_s[i]-prefix_s[i-1])/(2*(b-a));

        }

        if(flag)
           {
               print(ans);continue;
           }


        double tas=0;
        rep(i,n)
            tas+= ((double)(prefix_s[i+1]-prefix_s[i]))*(prefix_s[i+1]-prefix_s[i])/(2*(b-a));

        ll av= b-(prefix_s[n])-lef;

        ll co=av/prefix_s[n];

        ans+=tas*co;

        av%=prefix_s[n];

        repp(i,1,n){

            if(prefix_s[i]>av){ans+=(double)(av-prefix_s[i-1])*(av-prefix_s[i-1])/(2*(b-a));

            break;

            }

            ans+= (double)(prefix_s[i]-prefix_s[i-1])*(prefix_s[i]-prefix_s[i-1])/(2*(b-a));

        }

print(ans);continue;
}

return 0;
}
