#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
ll k;

ll dfs(ll v, ll prof, vector<ll>& pontos, vector<vector<ll>>& P_graph, vector<bool>& vis, vector<ll>& ac){
    //cout<< "olhando o vértice " << v << endl;  
    //cout<< "pontos de " << v << " são " << pontos[v] << endl;

    ll pont_aux = pontos[v];
    ac[v]+=pontos[v];

    vis[v]=true;

    if(prof == k || P_graph[v].size()==0)
        return pontos[v];
    else if(prof>k)
        return 0;

    for(ll& u: P_graph[v]){
        if(!vis[u]){
            ac[u] += ac[v];
            pont_aux += max(pontos[v]*(k-prof), dfs(u, prof+1, pontos, P_graph, vis, ac));
        }
        else{
            if(u==v)
                pont_aux+= ac[u]*(k-prof);
            else
                pont_aux+= max(ac[u]*(k-prof-1)-pontos[v], pontos[v]*(k-prof));
            //cout<< "ac[v]: " << ac[v] << " ac[u]: " << ac[u] << endl;
            //cout<< "pinto: " << pont_aux << "\n";
        }
    }

    //vis[v]=false;

    //cout<< "vértice " << v << " retornando " << pont_aux << endl;
    return pont_aux; 
}

void solve(){
    ll n, Pb, Ps;

    cin >> n >> k >> Pb >> Ps;

    vector<ll> pontos(n+1);
    vector<vector<ll>> P_graph(n+1); 
    vector<bool> vis_B(n+1, false), vis_S(n+1, false);
    vector<ll> ac_B(n+1,0), ac_S(n+1,0);

    // lê os vizinhos do grafo direcionado
    for(ll i=1; i<=n; i++){
        ll a;
        cin >> a;

        P_graph[i].push_back(a);
    }

    // lê os valores que ganha em cada vértice
    for(ll i=1; i<=n; i++){
        ll aux;
        cin >> aux;

        pontos[i] = aux; 
    }

    ll Bodya_P = 0;
    ll Sasha_P = 0;

    //cout<< "olhando B\n"; 
    Bodya_P += dfs(Pb, 1, pontos, P_graph, vis_B, ac_B);
    //cout<< "olhando S\n";
    Sasha_P += dfs(Ps, 1, pontos, P_graph, vis_S, ac_S);

    //cout<< "pontuação " << Bodya_P << " X " << Sasha_P << endl;

    if(Bodya_P > Sasha_P){
        cout << "Bodya\n";
    }
    else if(Bodya_P < Sasha_P){
        cout << "Sasha\n";
    }
    else        
        cout << "Draw\n";
}

int main(){
    oiee;

    ll t;
    cin >> t;

    for(ll i=0; i<t; i++)
        solve();
}

/*
1
4 8 4 2
2 3 4 1
5 2 8 7



-------------------------

1 
8 10 4 1
5 1 4 3 2 8 6 7
1 1 2 1 2 100 101 102

---------------------------
1
4 2 3 1
4 1 3 2
6 8 5 3
*/
