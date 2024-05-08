#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> visitados;

ll dfs(ll i, vector<vector<ll>> &r){
    visitados[i] = true;
    ll ult_bairro=i;

    for(auto bairro:r[i]){
        if(!visitados[bairro]){
            dfs(bairro, r);

            ult_bairro=bairro;
        }
    }

    return ult_bairro;
}

int main(){
    oiee;

    // quant. minima de ruas necessárias e quais ruas devem ser construídas

    // n: bairros. m: ruas
    ll n, m; cin >> n >> m;

    vector<vector<ll>> ruas_e(n+1);

    for(ll i=0; i<m; i++){
        ll a, b; 
        cin >> a >> b;

        // grafo não dirigido
        ruas_e[a].push_back(b);
        ruas_e[b].push_back(a);
    }

    visitados.resize(n+1, false);
    vector<pair<ll,ll>> novas_ruas;
    ll aux_bairro = 0;

    for(ll i=1; i<=n; i++){
        if(!visitados[i]){
            if(aux_bairro > 0)
                novas_ruas.push_back(make_pair(i, aux_bairro)); 
            
            aux_bairro = dfs(i, ruas_e);

        }
        
    }

    cout << novas_ruas.size() << "\n";
    if(novas_ruas.size() >0){
        for(auto par: novas_ruas)
            cout << par.first << " " << par.second << "\n";
    }
}