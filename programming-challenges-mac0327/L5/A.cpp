#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

const int MOD = 1e9+7;
const int MAX = 1e6+1;

int fatorial[MAX];

void pre_calc_fatorial(){
  fatorial[0] = 1;
  for(int i=1; i < MAX; i++){
    fatorial[i] = (fatorial[i-1] * i)%MOD;
  }
}

int exp(int a, int b){
	if(b == 0) return 1;
	int tmp = exp(a, b/2);
	tmp = (tmp * tmp)%MOD;
	if(b%2 == 1){
		tmp = (tmp * a)%MOD;
	}
	return tmp;
}

int modular_inverse(int a){
	return exp(a, MOD-2);
}

int comb(int n, int k){
  int numerator = fatorial[n];
  int denominator = (fatorial[k] * fatorial[n-k])%MOD;
	return (numerator * modular_inverse(denominator))%MOD;
}

// não roda o último caso teste, mto grande
void brute(){
    ll n, c; 
    cin >> n >> c;
    set<ll> s;

    for(ll i=0; i<n;i++){
        ll aux;
        cin >> aux;
        s.insert(aux);
    }

    ll resp=0;

    for(ll i=0; i<=c; i++){
        for(ll j=i; j<=c; j++){
            if(s.find(i+j)==s.end() && s.find(-i+j)==s.end()){
                resp++;
                cout << "x= " << i << "y= " << j << "\n";
            }
        }
    }

    cout << resp << "\n";
}

void solve2() {
    ll n, c; cin >> n >> c;

    vector<ll> s(n);
    for (ll i = 0; i < n; i++)
        cin >> s[i];

    // sort pra depois poder fazer a busca
    sort(s.begin(), s.end()); 

    // pares que e quero excluir
    ll ex = 0;

    // pares totais: sem repetições do tipo (0,1) (1,0)
    ll pares = 0;
    // intervalo que temos que verificar
    for (ll x = 0; x <= c; x++) {
        pares += (x+1);

        // olhar elementos menores ou iguais a c-x no vetor de entrada => tirar combinação
        ll y = c - x;

        // Encontra o primeiro elemento maior do que x
        // ini, fim, valor de referência
        //ll up = std::upper_bound(s.begin(), s.end(), x+y) - s.begin(); 

        // Encontra o primeiro elemento maior ou igual a y
        // ini, fim, valor de referência
        //ll low = std::lower_bound(s.begin(), s.end(), y-x+1) - s.begin();

        //cout << x << " " << y << " " << up << " " << low << "\n "; 

        ll up1 = std::upper_bound(s.begin(), s.end(), x+y) - s.begin();
        ll up2 = std::upper_bound(s.begin(), s.end(), y-x+1) - s.begin();

        // quat de elementos entre [x,y]
        ex += abs(up1-up2);

    }

    cout << "ex=  "<< ex << "\n";
    cout << "pares=  "<< pares << "\n";

    cout << (pares-ex) << "\n";
}

int main(){
    oiee;
    

    ll t; cin >> t;

    for(ll i=0; i<t; i++)
        solve2();

}