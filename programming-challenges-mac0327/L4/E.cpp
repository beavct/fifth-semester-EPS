#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define MOD 1000000007


int main(){
    oiee;

    ll n; cin >> n;
    vector<vector<char>> matrix(n, vector<char>(n));

    for(ll i=0; i<n; i++)
        for(ll j=0; j<n; j++)
            cin >> matrix[i][j];

    vector<vector<ll>> tab(n,vector<ll>(n,0));

    // como só anda para direita e para baixo, só há uma forma de chegar nessas casas
    for(ll i=0; i<n; i++){
        if(matrix[0][i]!='*')
            tab[0][i]=1;   
        else
            break;

    }

    for(ll i=0; i<n; i++){
        if(matrix[i][0]!='*')
            tab[i][0]=1;
        else
            break;    
    }

    for(ll i=1; i<n; i++){
        for(ll j=1; j<n; j++){
            // não pisamos na grama
            if(matrix[i][j] != '*'){
                // caminhos possiveis p/ chegar na celula a esquerda e de cima
                tab[i][j] = (tab[i-1][j] + tab[i][j-1])%(ll)MOD;
            }

        }
    }

    cout << tab[n-1][n-1] << endl;
}