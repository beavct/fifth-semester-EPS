#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

#define MAXP 32 

vector<vector<ll>> bss; // bss[a] representa a lista de adjacência do vértice a
vector<array<ll, MAXP>> ps; // matriz de "pulos": ps[a][j] representa o 2**j-ésimo ancestral do vértice a
vector<ll> ls, rs; // ls[x] e rs[a] representam respectivamente o tempo inicial e final da DFS no vértice a
ll c=0; // contador de tempos para a DFS

void dfs(ll a, ll p) {

    cout << "ini filho " << a << " com pai " << p << "\n";

    if(ps[a][0]==-1)
	    ps[a][0] = p; // incializa o primeiro ancestral de a como o pai na DFS
	ls[a] = c++;

	for(ll b : bss[a])
		if(b != p)
			dfs(b, a);

	rs[a] = c++;

}

int main() {
    oiee;

	ll n, q; // quantidade de vértices e quantidade de consultas
	cin >> n >> q;

	// define o tamanho dos vetores
	bss.resize(n);
	ps.resize(n);
	ls.resize(n, -1);
	rs.resize(n, -1);

	// lê as arestas
	for(ll i=0; i<n; i++) {
		ll a; cin >> a;
		a--; 
		bss[i].push_back(a);
        ps[i][0]=a;
	}

	// aplica a DFS partindo do vértice zero, fazendo com que a árvore seja enraizada nesse vértice
	// aqui, o zero no segundo argumento é muito importante, pois faz com que o ancestral da raiz seja ela mesma
	// isso garante que ficaremos na raiz em caso de "pulos" maiores que a altura da árvore
    //dfs(0,0);
    //for(ll i=0; i<n;i++){
    //    if(ls[i]==-1)
    //        dfs(i,i);
    //}
    

	// inicializa a matriz de "pulos"
	// cada linha da matriz é construída a partir das informações da linha anterior
	for(ll j=0; j<MAXP-1; j++) {
		for(ll i=0; i<n; i++)
			ps[i][j+1] = ps[ps[i][j]][j];
	}

    /*
    cout << "----------------------\n";
    for(auto linha : ps){
        for(auto elem : linha)
            cout << elem << " ";
        cout << "\n";
    }
    cout << "-----------------------\n";
    */

	// processa as consultas
	for(ll i=0; i<q; i++) {
        ll x, k;
        cin >> x >> k;
        x--;

        ll cur = x;

        for(ll j=0; j<MAXP; j++){       
            // bit: move o 1 i casas para a direita
            if(k & (1 << j)){
                //cout << "cuurr " << cur+1 << " j: " << j << "\n"; 
                cur = ps[cur][j];


                //k-=j;
            }
        }

        cout << cur+1 << "\n";

	}

	return 0;	
}