#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAXP 32 
#define ll long long

vector<vector<int>> bss; // bss[a] representa a lista de adjacência do vértice a
vector<array<int, MAXP>> ps; // matriz de "pulos": ps[a][j] representa o 2**j-ésimo ancestral do vértice a
vector<int> ls, rs; // ls[a] e rs[a] representam respectivamente o tempo inicial e final da DFS no vértice a
int c=0; // contador de tempos para a DFS

void dfs(ll a, ll p) {

	ps[a][0] = p; // incializa o primeiro ancestral de a como o pai na DFS
	ls[a] = c++;

	for(ll b : bss[a])
		if(b != p)
			dfs(b, a);

	rs[a] = c++;

}

int main() {
    oiee;

    ll n, q;
    cin >> n >> q;

	// define o tamanho dos vetores
	bss.resize(n);
	ps.resize(n);
	ls.resize(n, -1);
	rs.resize(n, -1);

    //bss[0].push_back(0);

	// lê as arestas
	for(ll i=1; i<n; i++) {
        ll a; cin >> a;
        a--;
        bss[a].push_back(i);  
	}

	// aplica a DFS partindo do vértice zero, fazendo com que a árvore seja enraizada nesse vértice
    dfs(0,0);

	// inicializa a matriz de "pulos"
	for(ll j=0; j<MAXP-1; j++) {
		for(ll i=0; i<n; i++)
			ps[i][j+1] = ps[ps[i][j]][j];
	}

	// processa as consultas
	for(ll i=0; i<q; i++) {

		ll a, b; cin >> a >> b;
		a--; b--;

		if(ls[a] <= ls[b] && rs[b] <= rs[a]) // a é ancestral de b
			cout << a + 1 << '\n';

		else if(ls[a] >= ls[b] && rs[a] <= rs[b]) // b é ancestral de a
			cout << b + 1 << '\n';

		else { // a e b não são ancestrais um do outro
			// usamos a matriz do binary lifting para buscar pelo último ancestral de a que não é um ancestral de b
			ll u = a;
			for(ll j=MAXP-1; j>=0; j--) { // para cada tamanho de "pulo" começando pelo maior (essa ordem é importante)
				ll v = ps[u][j]; // v é o 2**j-ésimo ancestral de u
				if(ls[v] > ls[b] || rs[b] > rs[v]) // v não é ancestral de b, podemos continuar a busca em v
					u = v;
			}
			// ao final da busca, o menor ancestral comum de a e b é o ancestral direto (pai) de u
			cout << ps[u][0]+1 << '\n';
		}

	}

	return 0;	
}

/*
8 10
1 1 3 3 4 6 2
7 1 
4 5 
8 6
6 7 
2 3
3 5
2 8
4 6 
1 1 
4 7
1
3
1
6
1
3
2
4
1
4

----------------------------

6 3

1
1
2
2
3

4 5
4 6
6 3

 * Saída:

2
1
3

*/
