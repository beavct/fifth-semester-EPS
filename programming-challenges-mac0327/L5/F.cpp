#include <bits/stdc++.h>
#include <map> // Include the map header

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
const ll MOD = 1e9+7;

// com inverso modular, pois o tamanho da string pode ser até 1e6
// muito grande para alocar em uma matriz

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

ll comb(ll n, map<char, ll> &rep){
    int numerator = 1, denominator = 1;

    for(ll i=1; i<=n; i++){
        numerator = (numerator*i)%MOD;
    }

    for(auto k : rep){
        for(ll i=1; i<=k.second; i++){
            denominator= (denominator*i)%MOD;
        }
    }

    return (numerator * modular_inverse(denominator))%MOD;
}


int main(){
    oiee;
    string s;   cin >> s;

    // tomar cuidado com caracteres repetidos
    sort(s.begin(), s.end());
    // conta as letras repetidas
    map<char, ll> rep;
    for(ll i=0; i<(ll)s.size();i++){
        if(i!=(ll)s.size()-1&&  s[i] == s[i+1])
            rep[s[i]]++;
        
        else{
            if(i>0 && s[i]==s[i-1])
                rep[s[i]]++;
            
        }
    }

    cout << comb((ll)s.size(), rep) << "\n";

}