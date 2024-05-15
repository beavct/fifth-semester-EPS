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

const ll oo = 1e18;
ll N, R;

void pre_calc(vector<vector<ll>>& dist, vector<vector<pair<ll, ll>>>& srs2){
    // calcula caminho: u -> v
    for(ll u=0; u<N; u++){
        for(ll v=N-1; v>=0; v--){
            if(u==v)
                continue;

            cout << "OLHANDO " << u << " -> " << v << "\n";
            
            for(pair<ll,ll> r : srs2[v]){
                ll c = r.first;
                ll w = r.second;

                // OK
                if(w == u){
                    dist[u][v] = c;
                    break;
                }

                dist[u][v] = max({dist[w][u], c, dist[u][w]});
            }
        } 
    }

}

void pre_calc2(vector<vector<ll>>& dist, vector<vector<pair<ll, ll>>>& srs2, vector<bool>& visited, ll i, ll j){
    

}

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

void solve(ll testCase) {
    // N: cidades, R: rotas de voo;
    cin >> N >> R;

    vector<ll> ps(N, -1), ws(N, 1);
	vector<array<ll,3>> rs(R); // arestas do grafo
	//vector<array<ll,3>> srs; // arestas selecionadas    
    vector<vector<pair<ll, ll>>> srs2(N);

    // leitura dos dados
    for(array<ll,3>& r : rs){
        ll a, b, l;
        cin >> a >> b >> l;

		a--; b--;
		r = {l, a, b}; // colocamos o custo no começo para podermos ordenar
    }

	sort(rs.begin(), rs.end());

    ll quant_r=0;

    // constrói MST
	for(array<ll,3>& r : rs) {
		// se os vértices u e v da aresta uv já não estão no mesmo conjuto (ou seja, já tem uma conexão entre eles)
		if(find(ps, r[1]) != find(ps, r[2])) {
            quant_r++;
			
			// incrementa o custo
			//ct += r[0];
			
			// guarda a aresta que foi selecionada
			//srs.push_back(r);
            srs2[r[1]].push_back({r[0], r[2]});
            srs2[r[2]].push_back({r[0], r[1]});
			
			// junta as componentes dos vértices u e v
			join(ps, ws, r[1], r[2]);
			// aqui poderiamos parar quando a quantidade de ruas batesse qv-1
            if(quant_r==N-1)
                break;
		}

	}

    vector<vector<ll>> dist(N, vector<ll>(N, 0));
    vector<bool> visited(N, false);
    //for(ll i=0; i<N; i++)
    //    dist[i][i]=0;
    //pre_calc(dist, srs);

    pre_calc(dist, srs2);

    for(ll i=0; i<N; i++){
        for(ll j=0; j<N; j++){
            cout << dist[i][j] << "    ";
        }
        cout << "\n";
    }
    cout << "\n"<< "\n"<< "\n";

    // Q: consultas
    ll Q;
    cin >> Q;

    vector<pair<ll,ll>> Qs(Q);

    cout << "Case " << testCase << "\n";
    // leitura das consultas
    for(ll i=0; i<Q; i++){
        ll k, t;
        cin >> k >> t;
        k--; t--;

        cout << dist[k][t] << "\n";
    }
    cout << "\n";

}

int main(){
    oiee;

    ll t; 
    cin >> t;

    for(ll i=0; i<t; i++){
        solve(i+1);
    }
}

/*
1
8 10
1 2 1 
1 3 1
1 5 10
5 7 5 
2 3 2 
4 7 4 
1 7 7
1 6 9 
3 4 10
1 8 10
0

*/