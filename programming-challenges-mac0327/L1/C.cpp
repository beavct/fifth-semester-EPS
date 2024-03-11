#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define ld long double

int cobre_tudo(vector<ll> &a, ld d, ll l, ll n){
    ld x_atu=0;
    ld x_prox, x_ant;

    for(ll i=0; i<n; i++){
        x_ant=a[i]-d;
        x_prox=a[i]+d;

        if(x_ant>x_atu)
            return 0;

        x_atu=x_prox;
        
    }

    if(x_atu>=l)
        return 1;

    return 0;
}

int main(){
    oiee;

    ll n, l;
    cin >> n >> l;

    vector<ll> a(n);
    for(ll i=0; i<n; i++)
        cin >> a[i];

    if(n>0)
        sort(a.begin(), a.end());

    ld left=0, right=l;
    ld resp = l;
    ld eps=1e-9;

    //left<=right
    while(left-right < -eps){
        ld d = (left+right)/2;
        int aux = cobre_tudo(a, d, l, n);

        if(aux){
            resp=d;
            right=d;
        }
        else{
            left=d;
        }    
    }

    cout << fixed << setprecision(10);
    cout << resp << endl;
}