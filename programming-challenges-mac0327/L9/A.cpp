#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<char> letras;
vector<pair<ll,ll>> filhos;

ll dfs(ll v, ll mud){

    ////cout<< "olhando o vértice " << v << "\n";

    ll aux_mud1 = mud;
    ll aux_mud2= mud;
    //aux_mud1 = aux_mud2 = mud;

    ll u1 = filhos[v].first;  
    ll u2 = filhos[v].second;

    if(u1!=0){
        //cout<< "vai olhar " << u1 << "\n";
        if(letras[v]!='L'){
            ////cout<< "oie1\n";
            aux_mud1++;
        }
        aux_mud1 = dfs(u1, aux_mud1);

    }

    if(u2!=0){
        //cout<< "vai olhar " << u2 << "\n";
        if(letras[v]!='R'){
            ////cout<< "oie2\n";
            aux_mud2++;
        }
        aux_mud2 = dfs(u2, aux_mud2);

    }

    ////cout<< aux_mud1 << " " <<  aux_mud2 << "\n";

    if(u1==0)
        return aux_mud2;
    else if(u2==0)
        return aux_mud1;

    return min(aux_mud1, aux_mud2);
}

void solve(){
    ll n;
    cin >> n;

    letras.resize(n+1);
    filhos.resize(n+1);

    for(ll i=1; i<=n; i++)
        cin >> letras[i];

    for(ll i=1; i<=n;i++){
        cin >> filhos[i].first >> filhos[i].second; 
    }
    
    ll min = dfs(1, 0);

    cout << min << "\n";
}

int main(){
    oiee;

    ll t;
    cin >> t;

    for(ll i=0; i<t; i++)
        solve();

}