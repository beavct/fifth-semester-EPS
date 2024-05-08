#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<vector<bool>> visitados;

int dentro(ll x, ll y, ll n, ll m){
    return (x>=0 && y>=0 && x<n && y<m);
}

ll dfs(ll x, ll y, ll k, vector<vector<char>>& lab) {
    visitados[x][y] = true;

    ll mx[]={0, -1, 0, 1};
    ll my[]={1, 0, -1, 0};
    ll conta=0;

    for(ll i=0; i<4; i++){
        ll a = x+mx[i];
        ll b = y+my[i];

        if(dentro(a, b, (ll)lab.size(), (ll)lab[0].size()) && lab[a][b] == '.'){
            if(!visitados[a][b] && k>0){
                conta++;
                k=dfs(a, b, k,lab);
                if(lab[a][b]=='X')
                    conta--;
            }
        }
    }

    if(conta<=1 && k>0){
        lab[x][y]='X';
        k--;
    }

    return k;
}

int main(){
    oiee;

    // n: altura, m: largura, k: # de paredes que quer add
    ll n, m, k; cin >> n >> m >> k; 
    vector<vector<char>> lab(n, vector<char>(m));
    visitados.resize(n, vector<bool> (m,false));

    // '.': vazio, '#' parede
    for(ll i=0; i<n; i++)   
        for(ll j=0; j<m; j++)
            cin >> lab[i][j];
    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++){
            if(!visitados[i][j] && lab[i][j]=='.'){
                k=dfs(i, j, k, lab);
            }
            if(k==0)
                break;
        }
        if(k==0)
            break;
    }

    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++)
            cout << lab[i][j];
        cout << "\n";
    }   
}

    
/*

...
.#.
...


*/