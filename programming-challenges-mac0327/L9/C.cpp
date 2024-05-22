#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> vis; 
vector<ll> id, lo;
vector<bool> vertice_corte;
vector<vector<ll>> adj;
vector<ll> resp;

ll quant_vc = 0;
ll timer = 0;

void dfs(ll u, ll p){
	ll tree_edges=0; 
	lo[u] = id[u] = ++timer;
	
	vis[u] = true;
	
	for(auto v : adj[u]){
		if(v==p)continue;
		
		// se não foi visitado, é uma tree edge
		if(not vis[v]){
			tree_edges++;
			dfs(v, u);
			if(id[u] <= lo[v]){
                //cout << "deu push no " << u << "\n";
                //cout << id[u] << " - lo[" << v << "] " << lo[v] << "\n";
                //resp.push_back(u);
                if(!vertice_corte[u] && u!=p){
                    vertice_corte[u] = true;
                    quant_vc++;
                }
			}
			lo[u] = min(lo[u], lo[v]);

		}
		// se já foi visitado: é uma back edge
		else{
			lo[u] = min(lo[u], id[v]);
		}
	}
	if(u == p){
        //cout << "u: " << u << " te " << tree_edges << "\n"; 
        //resp.push_back(u);
        if(!vertice_corte[u] && tree_edges>1){
            vertice_corte[u] = true;
            quant_vc++;
        }
		//vertice_corte[u] = tree_edges>1;
	}
}

int main(){
    oiee;

    // n: cidades, m: estradas
    ll n, m; 
    cin >> n >> m;

    vis.resize(n+1, false);
    id.resize(n+1);
    lo.resize(n+1);
    adj.resize(n+1);
    vertice_corte.resize(n+1, false);

    for(ll i=0; i<m; i++){
        ll a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    cout << quant_vc << "\n";
    for(ll i=1; i<=n; i++){
        if(vertice_corte[i])
            cout << i << " ";
        //cout << resp[i] << " ";
    }
    if(quant_vc>0)
        cout << "\n";

}