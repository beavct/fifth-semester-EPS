#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
const ll MOD = 1e9+7;

// teremos t consultas
// 0 <= b <= a <= 1e6
const ll MAX = 1e6+1;

ll fat[MAX];

void pre_calc_fatorial(){
    fat[0] = 1;
    for(ll i=1; i < MAX; i++){
      fat[i] = (fat[i-1] * i)%MOD;
    }
}

ll exp(ll a, ll b){
    if(b == 0) return 1;
    ll tmp = exp(a, b/2);
    tmp = (tmp * tmp)%MOD;
    if(b%2 == 1){
        tmp = (tmp * a)%MOD;
    }
    return tmp;
}

ll modular_inverse(ll a){
    return exp(a, MOD-2);
}

ll comb(ll n, ll k){
    ll numerator = fat[n];
    ll denominator =(fat[k] *fat[n-k])%MOD;
    return (numerator * modular_inverse(denominator))%MOD;
}


void solve(){
    ll a, b; cin >> a >> b;

    cout << comb(a, b) << "\n"; 
}

int main(){
    oiee;

    pre_calc_fatorial();

    ll t; cin >> t;

    for(ll i=0; i<t; i++)
        solve();

}