#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define dl double long

ll pot2(ll n){

    ll q=0;

    if(n==0)
        return -1;

    while(n%2==0){
        n/=2;
        q++;
    }

    //if(n==1)
    return q;

    //return -1;
}

void solve(){
    // # pedaços de maça, # assaltantes
    ll n, m; cin >> n >> m;

    if(m == 0 || n%m==0){
        cout << "0\n";
        return;        
    }

    ll pot_m = pot2(m); 

    // se n>m, podemos dar uma maçã pra cada inicialmente
    if(n > m)
        n-=m;

    ll i= 0;
    ll ops=0;
    while(n > 0 && pot_m>=i){
        ops+=(n%m);
        n=2*(n%m);
        if(n!=0)
            i++;
    }

    if(i<=pot_m)
        cout << ops << "\n";
    else
        cout << "-1\n";
}

int main(){
    oiee;

    ll t; cin >> t;

    for(ll i=0; i<t; i++){
        solve();
    }

    exit(0);
}

/*
TESTE1
9
10 5
10 4
3 4
3 3
9 7
1 5
4 7
5 8
15 60
*/

/*
RESP1
0
2
5
0
-1
-1
-1
11
45
*/