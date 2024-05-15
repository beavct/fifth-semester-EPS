#include <bits/stdc++.h>
#include <array> 

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define ia3 array<ll, 3>

vector<ia3> estradas;

/* MST - Kruskal
 * são dadas a quantidade de cidades (n) e a quantidade de possíveis conexões entre elas (m)
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

ll comp;

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
		comp--;
        
        if(ws[a] < ws[b])
			swap(a,b);
		ws[a] += ws[b];
		ms.push_back(b);
	}
	for(ll m : ms) 
		ps[m] = a;
}

int main() {
    // n: pontos
    // m: estradas

	ll n, m, ct = 0; cin >> n >> m;
	vector<ll> ps(n, -1), ws(n, 1);
	vector<array<ll,3>> rs(m); // arestas do grafo
	vector<array<ll,3>> srs; // arestas selecionadas

    comp = n;

	for(array<ll,3>& r : rs) {
		ll a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		r = {c, a, b}; // colocamos o custo no começo para podermos ordenar
	}

	sort(rs.begin(), rs.end());

	for(array<ll,3>& r : rs) {
		if(find(ps, r[1]) != find(ps, r[2])) {
			ct += r[0];
			srs.push_back(r);
			join(ps, ws, r[1], r[2]);

            if(comp==1)
                break;
		}
	}

    if(comp>1)
        cout << "IMPOSSIBLE\n";
    else{
	    cout << ct << '\n';

    }
}
