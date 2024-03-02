#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll prod(vector<ll> a){
    ll prod = 1;

    for(ll i=0; i<(ll)a.size(); i++)
        prod *= a[i];

    return prod;
}

// -1: produto negativo, 0: produto = 0, 1: produto positivo
int signal(vector<ll> a){
    int signal = 1;

    for(auto elem : a){
        if(elem < 0)
            signal *= -1;
        else if(elem == 0)
            return 0;
    }

    return signal;
}

void solve(){
    ll n; 

    cin >> n;

    vector<ll> array(n);

    // Leitura dos n números do array
    for(ll i=0; i<n;i++){
        cin >> array[i];
    }

    // Quantidade de operações
    ll ops = 0;
    // Vetores de mudanças
    vector<ll> ind;
    vector<ll> mud;

    for(ll i=0; i<n; i++){
        //vector<ll> aux(array);

        //aux[i] = 0;

        if(::signal(array) == 1){
            //array = aux;
            array[i] = 0;
            ops++;
            ind.push_back(i+1);
            mud.push_back(array[i]);
            break;
        }

    }

    //cout << "saida: " << ops << endl;
    cout << ops << endl;
    for(ll i = 0; i<(ll)mud.size(); i++)
        cout << ind[i] << " " << mud[i] << endl;

}

int main(){
    ll t;

    cin >> t;

    for(ll i=0; i<t; i++)
        solve();
}