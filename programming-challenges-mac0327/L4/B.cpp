#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll n, m, b, mod; cin >> n >> m >> b >> mod; 
    vector<ll> a(n);

    for(ll i=0; i<n; i++)
        cin >> a[i];

    vector<ll> pd(n+1,0);
    vector<ll> erros(n+1,0);
    vector<ll> mmm(n+1,0);
    vector<ll> foram(n+1,0);

    for(ll i=1;i<=n;i++){
        for(ll j=0; j<m;j++){
            if(erros[i]+pd[i]<=b && !foram[i]){
                mmm[i]+=
            }
        }
    }

    cout << erros[v]%mod<<"\n";
}