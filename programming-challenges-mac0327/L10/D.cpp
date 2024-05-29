#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAXP 32 
#define ll long long

vector<ll> altura;
vector<vector<int>> bss; // bss[a] representa a lista de adjacência do vértice a
vector<array<int, MAXP>> ps; // matriz de "pulos": ps[a][j] representa o 2**j-ésimo ancestral do vértice a
vector<int> ls, rs; // ls[a] e rs[a] representam respectivamente o tempo inicial e final da DFS no vértice a
int c=0; // contador de tempos para a DFS

void dfs(ll a, ll p, ll h) {

    altura[a]=h;
	ps[a][0] = p; // incializa o primeiro ancestral de a como o pai na DFS
	ls[a] = c++;

	for(ll b : bss[a])
		if(b != p)
			dfs(b, a, h+1);

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
    altura.resize(n);

	// lê as arestas
	for(int i=0; i<n-1; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		bss[a].push_back(b);
		bss[b].push_back(a);
        //ps[b][0] = a; 
	}

	// aplica a DFS partindo do vértice zero, fazendo com que a árvore seja enraizada nesse vértice
    dfs(0,0, 0);

	// inicializa a matriz de "pulos"
	for(ll j=0; j<MAXP-1; j++) {
		for(ll i=0; i<n; i++)
			ps[i][j+1] = ps[ps[i][j]][j];
	}

    //cout << "---------------------------\n";
    //for(auto linha : ps){
    //    for(auto elem: linha)
    //        cout << elem << " ";
    //    cout << "\n";
    //}
    //cout << "---------------------------\n\n";


	// processa as consultas
	for(ll i=0; i<q; i++) {

		ll a, b; cin >> a >> b;
		a--; b--;
        ll dist=0;
        ll flag=1;

        ll cur = b;

        // tempo inicial de a <= tempo ini. de b E tempo final de b <= tempo final de a
		if(ls[a] <= ls[b] && rs[b] <= rs[a]) // a é ancestral de b
			dist=abs(altura[b]-altura[a]);
            //cout << a + 1 << '\n';

		// tempo ini. de a >= tempo ini. de b E tempo final de a <= tempo ini. de a
		else if(ls[a] >= ls[b] && rs[a] <= rs[b]) // b é ancestral de a
			dist=abs(altura[a]-altura[b]);
            //cout << b + 1 << '\n';

		else { // a e b não são ancestrais um do outro
			// usamos a matriz do binary lifting para buscar pelo último ancestral de a que não é um ancestral de b
			// durante a busca, representaremos esse ancestral pela variável u
			int u = a;
			for(int j=MAXP-1; j>=0; j--) { // para cada tamanho de "pulo" começando pelo maior (essa ordem é importante)
				int v = ps[u][j]; // v é o 2**j-ésimo ancestral de u
				if(ls[v] > ls[b] || rs[b] > rs[v]) // v não é ancestral de b, podemos continuar a busca em v
					u = v;
			}
			// ao final da busca, o menor ancestral comum de a e b é o ancestral direto (pai) de u
			//cout << ps[u][0]+1 << '\n';
            ll anc = ps[u][0];
            dist=(altura[a]-altura[anc])+(altura[b]-altura[anc]);
		}


        cout << dist << "\n";
    }
	

	return 0;	
}
