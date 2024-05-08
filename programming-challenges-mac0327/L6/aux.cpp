#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> visitados;
vector<vector<ll>> voos;
vector<ll> resp;
vector<ll> dist;
vector<vector<ll>> cam;
ll n;

void dfs(ll i, ll passadas, vector<ll> &aux){
    visitados[i]=true;
    dist[i]=max(dist[i], passadas);

    for(auto cidade : voos[i]){
        //cout<< "aux na chamada de " << i << "->" << cidade << "\n";
        //for(auto elem:aux)
        //    cout<< elem << " ";
        //cout<< "\n";
        if(!visitados[cidade]){
            dfs(cidade, passadas+1, aux);
        }
        else{
            dist[cidade]=max(dist[cidade],passadas+1);
        }   
    }

    //for(auto elem:dist)
    //    cout << elem << " ";
    //cout << "\n";
}

void build_ans(){
    ll i=n;

    while(i>=1){
        resp.push_back(i);

        ll j=0;
        ll aux_d=-1;

        for(auto cidade : cam[i]){
            if(dist[cidade]>aux_d){
                aux_d=dist[cidade];
                j=cidade;
            }
        }

        i=j;
        aux_d=-1;
    }
}

int main(){
    oiee;

    // numero de cidades, numero de voos
    ll m; cin >> n >> m;
    voos.resize(n+1);
    visitados.resize(n+1, false);
    dist.resize(n+1, 0);
    cam.resize(n+1);

    for(ll i=0; i<m;i++){
        ll a, b;
        cin >> a >> b;

        voos[a].push_back(b);
        cam[b].push_back(a);
    }

    vector<ll> aux;
    dfs(1, 0, aux);

    if(dist[n]==0)
        cout << "IMPOSSIBLE\n";
    else{
        build_ans();
        cout << resp.size() << "\n";
        for(ll i=(ll)resp.size()-1; i>=0; i--)
            cout << resp[i] << " ";

        cout << "\n";        
    }


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


/*
ENTRADA:
9 10
1 2 
1 9 
2 3 
2 4 
3 5 
3 6
4 6
6 7
6 8
7 8


SAÍDA:
2
1 9

*/