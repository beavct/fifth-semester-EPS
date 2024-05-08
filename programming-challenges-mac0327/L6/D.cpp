#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

// v. globais
vector<bool> visitados;
vector<ll> distancias;
vector<ll> v_pocas;
vector<vector<ll>> arvore;

ll dfs(ll m, ll i, ll pocas){
    visitados[i] = true;
    ll quant=0;

    //cout<< "olhando " << i << endl;

    if(v_pocas[i])
        pocas++;
    else    
        pocas=0;


    if(pocas>m)
        return 0;

    for(auto filho : arvore[i]){
        if(!visitados[filho]){
            quant+=dfs(m, filho, pocas);
        }
    }

    // chegou em uma folha//
    if((int)arvore[i].size()==1  && i != 1){
        quant++;
    }

    return quant;
}

int main(){
    oiee;

    // saída: quant. de restaurantes que dá pra ir

    // parque: raíz no vértice 1, n vértices

    // n: numero de vértices, m: passar em mais de m poças de água
    ll n, m; cin >> n >> m;
    v_pocas.resize(n+1);
    arvore.resize(n+1);
    visitados.resize(n+1, false);

    v_pocas[0]=0;
    visitados[0]=true;

    // ai==1 => tem poça
    // ai == 0 => não tem poca
    for(ll i=1; i<=n; i++)
        cin >> v_pocas[i];

    for(ll i=0; i<n-1; i++){
        ll a, b;

        cin >> a >> b;

        arvore[a].push_back(b);
        arvore[b].push_back(a);
    }

    ll quant = dfs(m, 1, 0);

    cout << quant << "\n";


}
/*
ENTRADA
7 3
1 1 1 1 1 1 1
1 2
1 3
2 4
2 5
3 6
3 7

SAÍDA
4
*/


/* 
ENTRADA
4 1 
0 0 0 0
1 2 
2 3 
2 4

SAÍDA
2
*/