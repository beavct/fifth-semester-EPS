#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> visitados;
vector<vector<ll>> voos;
vector<ll> resp;
ll n;

void dfs(ll i, ll passadas, vector<ll> &aux){
    //visitados[i]=true;

    // não é o destino final (Cairo)
    if(i != n){
        //cout<< "olhando os vizinhos do " << i << "\n";

        // olha os voos da cidade
        for(auto cidade : voos[i]){
            aux.push_back(i);
            cout<< "aux na chamada de " << i << "->" << cidade << "\n";
            for(auto elem:aux)
                cout<< elem << " ";
            cout<< "\n";
            dfs(cidade, passadas+1, aux);
        }
    }
    else{
        aux.push_back(n);
    }

    if((ll)aux.size()>(ll)resp.size() && aux.back() == n)
        resp=aux;

    aux.clear();
}

int main(){
    oiee;

    // numero de cidades, numero de voos
    ll m; cin >> n >> m;
    voos.resize(n+1);
    //visitados.resize(n+1, false);

    for(ll i=0; i<m;i++){
        ll a, b;
        cin >> a >> b;

        voos[a].push_back(b);
    }

    vector<ll> aux;
    dfs(1, 1, aux);

    if((int)resp.size()>0){
        cout << resp.size() << endl;
        for(auto elem: resp)
            cout << elem << " ";

        cout << "\n";
    }
    else    
        cout << "IMPOSSIBLE\n";

}


/* 
ENTRADA:
17 18
1 2 
2 3 
3 4 
4 5 
5 17
1 6 
6 7 
7 8 
8 9
9 17
1 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17

SAÍDA 
10
1 10 11 12 13 14 15 16 17

*/


/*
ENTRADA:
5 5 
1 2 
2 5
1 3 
3 4
4 2


SAÍDA:
5
1 3 4 2 5

*/