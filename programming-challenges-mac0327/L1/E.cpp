#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int verifica_d(ll N, ll C, vector<ll> &x, ll d){
    ll pular=N-C;
    ll x_ant=-d, x_atu;

    for(ll i=0; i<N; i++){
        x_atu=x[i];

        //cout << "x_atu= " << x_atu << " x_ant= " << x_ant << " d= " << d << " pular= " << pular << endl; 

        if(x_atu<x_ant+d){
            //cout << "puts" << endl; 
            if(pular){
                //cout << "pular--" << endl;
                pular--;
            }
            else{
                //cout << "retornou 0" << endl;
                return 0;
            }
        }
        else{
            x_ant=x_atu;
        }

    }

    //cout << "retornou 1" << endl;

    return 1;
}

void solve(ll N, ll C, vector<ll> &x){
    sort(x.begin(), x.end());

    ll resp=x[N-1]-x[0];
    ll d_min=0, d_max=x[N-1]-x[0]; // dist entre primeiro e último estábulo

    //cout << "d_max= "<< d_max << endl;

    while(d_min<=d_max){
        ll d_mid=(d_min+d_max)/2;
        int aux = verifica_d(N, C, x, d_mid);

        //cout << "ANTES d_max= "<< d_max << " d_min= "<< d_min << " d_mid= "<< d_mid << " aux= "<< aux << endl;

        if(aux){
            //cout << "entrou aq1" << endl;
            resp=d_mid;
            d_min=d_mid+1;
        }
        else{
            //cout << "entrou aq2" << endl;
            d_max=d_mid-1;
        }

        //cout << "DEPOIS d_max= "<< d_max << " d_min= "<< d_min << " d_mid= "<< d_mid << " aux= "<< aux << endl;

    }

    cout << resp << endl;
}

// maior distância mínima
int main(){
    oiee;

    ll t; cin >> t;

    for(ll i=0; i<t; i++){
        ll N, C; cin >> N >> C; 
        vector<ll> x(N);
        for(ll j=0; j<N; j++)
            cin >> x[j];

        solve(N, C, x);    
    }

}