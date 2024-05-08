#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long


vector<bool> visitados;
vector<int> times;

bool dfs(int i, int time, vector<vector<ll>> &amgs){
    times[i]=time;
    visitados[i] = true;

    for(ll j=0; j<(ll)amgs[i].size();j++){

        if(!visitados[amgs[i][j]]){
            int aux_t = 3-time; 
            int ret = dfs(amgs[i][j], aux_t, amgs);

            if(!ret)
                return false;
        }
        else if(times[amgs[i][j]] == time)
            return false;
    }

    return true;
}

int main(){
    oiee;

    // vértices indexados a partir do 1

    // n: amigos, m: arestas
    ll n, m; cin >> n >> m;
    // vetor de arestas
    vector<vector<ll>> amigues(n+1);
    // vai guardar os times de cada vértice 
    times.resize(n+1, 0);
    visitados.resize(n+1, false);

    // leitura das arestas  
    for(ll i=0; i<m; i++){
        ll pessoa, amigo;

        cin >> pessoa >> amigo;

        // vai adicionando os amigos da pessoa
        // grafo não direcionado
        amigues[pessoa].push_back(amigo);
        amigues[amigo].push_back(pessoa);
    }

    bool ret=true;

    for(ll i=1; i<=n; i++){
        if(!visitados[i])
            ret = dfs(i, 1, amigues);
        if(!ret)
            break;
    }

    if(ret){
        for(ll i=1; i<(ll)times.size(); i++)
            cout << times[i] << " ";
    }
    else    
        cout << "IMPOSSIBLE"; 
    cout << "\n";

}