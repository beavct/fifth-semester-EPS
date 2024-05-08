#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<vector<int>> bss;
vector<vector<bool>> visitados;

// verifica se a posição tá dentro da matriz
bool dentro(ll x, ll y, ll n, ll m){
    return (x>=0 && y>=0 && x<n && y<m);
}

// DFS com recursão: v(x,y) atual, matriz
void dfs(ll x, ll y, vector<vector<char>>& q) {
	visitados[x][y] = true;

    // visita os 4 lados (4 arestas) só se for um buraquinho
    //if(x-1>=0 && !visitados[x-1][y] && q[x-1][y]=='.')
    //    dfs(x-1, y, q);
    //if(y-1>=0 && !visitados[x][y-1] && q[x][y-1]=='.')
    //    dfs(x, y-1, q);
    //if(x+1<(ll)q.size() && !visitados[x+1][y] && q[x+1][y]=='.')
    //    dfs(x+1, y, q);
    //if(y+1<(ll)q[y].size() && !visitados[x][y+1] && q[x][y+1]=='.')
    //    dfs(x, y+1, q);

    // vetores de movimentos dos 4 visinhos
    ll mx[]={-1, 0, 1, 0};
    ll my[]={0, -1, 0, 1};

    for(ll i=0; i<4; i++){
        ll a = x+mx[i];
        ll b = y+my[i];

        /*
        *    verifica se a posição está dentro da matriz
        *    se já não foi visitada
        *    e se é um buraco
        */
        
        if(dentro(a, b, (ll)q.size(), (ll)q[0].size()) && !visitados[a][b] && q[a][b] == '.')
            dfs(a, b, q);
    }

}

int main(){
    oiee;

    ll n, m; cin >> n >> m;
    vector<vector<char>> queijo(n, vector<char>(m));
    visitados.resize(n, vector<bool> (m,false));
    ll buracos=0;

    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++){
            cin >> queijo[i][j];
        }
    }

    //cout << "--------------------\n\n";
    //for(ll i=0; i<n; i++){
    //    for(ll j=0; j<m; j++){
    //        cout << queijo[i][j] << " ";
    //    }
    //    cout << "\n";
    //}

    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++){
            if(!visitados[i][j] && queijo[i][j]=='.'){
                dfs(i, j, queijo);
                buracos++;
            }
        }
    }

    cout << buracos << "\n";
}