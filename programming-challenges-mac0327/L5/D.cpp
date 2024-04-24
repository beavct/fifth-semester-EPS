#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

const ll MOD = 1e9+7;
const ll MAX = 1e7+2;

ll fatorial[MAX];

void pre_calc_fatorial(){
  fatorial[0] = 1;
  for(ll i=1; i < MAX; i++){
    fatorial[i] = (fatorial[i-1] * i)%MOD;
  }
}

ll bom(ll n, ll a, ll b){
    // verifica se é bom
    while(n>0){
        ll d=n%10;

        if(d !=a && d!=b){
            return 0;
        }    

        n/=10;
    }

    return 1;
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

/* Comb em O(1) */
ll comb(ll n, ll i, ll j){
  ll numerator = fatorial[n];
  ll denominator = ((fatorial[i]%MOD)*(fatorial[j]%MOD))%MOD;
	return (numerator * modular_inverse(denominator))%MOD;
}

int main(){
    oiee;

    pre_calc_fatorial();

    // a e b: números bons
    // numeros exelentes: é um número formado apenas por números bons e soma dos seus dígitos é um numero bom 
    ll a,b,n; cin >> a>>b>>n;
    
    ll cont=0;

    // ideia:
    // verificar de quantas formas posso ter um número formado apenas por x e y 
    // e antes verificar se a quant1 * x + quant2 * y é bom

    // i é a quantidade de x's no número
    for(ll i=0; i<=n; i++){
        // j é a quantidade de y's no número
        ll j=n-i;

        // verificamos se a soma é diferente de 1, pq se for, não é um número excelente
        if(!bom(i*a + j*b, a, b))
            continue;


        // combinatória -> maneiras de dispor os x's e y's no número
        // a ordem importa

        // permutação de string -> DP  e inverso modular
        cont=(cont+comb(n, i, j))%MOD;
    }

    cout << cont << "\n";

    return 0;
}