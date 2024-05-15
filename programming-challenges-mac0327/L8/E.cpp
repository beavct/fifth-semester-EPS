#include <bits/stdc++.h>
#include<array>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

/* MST - Kruskal
 * são dadas a quantidade de cidades (qv) e a quantidade de possíveis conexões entre elas (qr)
 * é dado também o conjunto de possíveis conexões bidirecionais entre as cidades e o seu custo (a_i, b_i, c_i)
 * deve ser calculado o custo mínimo para conectar todas as cidades e as conexões a serem escolhidas para isso
 *
 * Entrada:

5 6
1 2 3
3 2 1
1 3 4
1 4 10
4 5 1
5 3 5

 * Saída:

custo mínimo: 10
conexões:
3 2
4 5
1 2
5 3

 */

ll find(vector<ll>& ps, ll a) {
	vector<ll> ms;
	while(ps[a] != -1) {
		ms.push_back(a);
		a = ps[a];
	}
	for(ll m : ms) 
		ps[m] = a;
	return a;
}

void join(vector<ll>& ps, vector<ll>& ws, ll a, ll b) {
	vector<ll> ms;	
	while(ps[a] != -1) {
		ms.push_back(a);
		a = ps[a];
	}
	while(ps[b] != -1) {
		ms.push_back(b);
		b = ps[b];
	}
	if(a != b) { // se a == b, não podemos colocar b como filho de a, ou seja, filho dele mesmo
		if(ws[a] < ws[b])
			swap(a,b);
		ws[a] += ws[b];
		ms.push_back(b);
	}
	for(ll m : ms) 
		ps[m] = a;
}

void mst() {
	// qv: quant. de vértices
	// qr: quant. de arestas
	// ct: custo da árvore

	ll qv, qr, ct = 0; cin >> qv >> qr;
	
	// ps: vetor de pais
	// ws: tamanho de cada conjunto
	
	vector<ll> ps(qv, -1), ws(qv, 1);
	vector<array<ll,3>> rs(qr); // arestas do grafo
	vector<array<ll,3>> srs; // arestas selecionadas

	for(array<ll,3>& r : rs) {
		ll a, b, c;
		
		// lê os extremos a e b da aresta e seu custo c
		cin >> a >> b >> c;
		
		// indexado do 1 ao n -> 0 ao n-1
		a--; b--;
		r = {c, a, b}; // colocamos o custo no começo para podermos ordenar
	}

	// Kruskal -> ordena o custo de forma não decrescente 
	sort(rs.begin(), rs.end());

	// percorre as arestas ordenadas pelo custo
	for(array<ll,3>& r : rs) {
		// se os vértices u e v da aresta uv já não estão no mesmo conjuto (ou seja, já tem uma conexão entre eles)
		if(find(ps, r[1]) != find(ps, r[2])) {
			
			// incrementa o custo
			ct += r[0];
			
			// guarda a aresta que foi selecionada
			srs.push_back(r);
			
			// junta as componentes dos vértices u e v
			join(ps, ws, r[1], r[2]);
			// aqui poderiamos parar quando a quantidade de ruas batesse qv-1
		}
	}

	cout << "custo mínimo: " << ct << '\n';
	cout << "conexões:\n";
	for(array<ll,3>& r : srs)
		cout << r[1]+1 << ' ' << r[2]+1 << '\n';	

}

void solve(ll testCase) {
    // N: cidades, R: rotas de voo;
    ll N, R;
    cin >> N >> R;

    vector<ll> ps(N, -1), ws(N, 1);
	vector<array<ll,3>> rs(R); // arestas do grafo
	vector<array<ll,3>> srs; // arestas selecionadas    

    for(ll i=0; i<R; i++){
        ll a, b, l;
        cin >> a >> b >> l;

        
    }


}

int main(){
    oiee;

    ll t; 
    cin >> t;

    for(ll i=0; i<t; i++){
        solve(i+1);
    }
}