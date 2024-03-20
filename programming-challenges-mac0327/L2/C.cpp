#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int tudo_menor_0(unordered_map<ll,ll> &oiii){
    for(auto [key, value]: oiii)
        if( value > (ll)0)
            return 0;

    return 1;
}

// WA teste 4
int main(){
    oiee;

    ll n; cin >> n;
    vector<ll> b(n);
    // map pq o valor de cada bandeirinha pode ser maior doq n
    unordered_map<ll, ll> oiii_entrada;
    unordered_map<ll, ll> oiii_dim;

    for(ll i=0;i <n; i++){
        cin >> b[i];
        oiii_entrada[b[i]]++;
    }  

    for(auto [key, value]: oiii_entrada){
        // quantidade mín. do elemento key que preciso ter no segmento que vou retirar
        if(value>1)
            oiii_dim[key]=value-1;
        else    
            oiii_dim[key]=0;
        //cout << "key= " << key << " value= " << oiii_dim[key] << endl;
    }

    ll l=0, r=0;
    ll resp=n;

    // intervalo do segmento: [l,r[
    while(r<=n){
        if(!tudo_menor_0(oiii_dim)){
            //cout << "1: l= " << l << " r= " << r << endl;
            oiii_dim[b[r++]]--;
        }
        else{
            //cout << "2: l= " << l << " r= " << r << endl;
            resp=min(resp, r-l);
            //cout << "resp= " << resp << endl; 
            oiii_dim[b[l++]]++;
            //cout << "3: l= " << l << " r= " << r << endl;
        }
    }

    cout<< resp << endl;

}