#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

const ll MOD = 998244353;
const ll MAX = 1e7;

/* funcao que pre calcula os fatoriais.
* perceba que, a chamada dessa funcao ira realizar MAX operacoes
* apesar disso, uma vez chamada a funcao, toda chamada de fatorial 
* fica O(1), o que faz com que nossa funcao comb() seja O(1).
*/
ll fatorial[MAX];

void pre_calc_fatorial(){
    fatorial[0] = 1;
    for(ll i=1; i < MAX; i++){
      fatorial[i] = (fatorial[i-1] * i)%MOD;
    }
}

// exponenciação rápida
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

/* Comb em O(1) */
ll comb(ll n, ll k){
    ll numerator = fatorial[n];
    ll denominator = (fatorial[k] * fatorial[n-k])%MOD;    	
    return (numerator * modular_inverse(denominator))%MOD;
}

signed main(){
    oiee;
    pre_calc_fatorial();

    ll n, m, k; cin >> n >> m >> k;
    // o tijolo [0] não conta
    ll ans = (comb(n-1, k)*m)%MOD;
	cout << (ans*exp(m-1,k))%MOD << endl;
}