#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> vis; 
vector<ll> id, lo;
vector<vector<ll>> adj;
set<pair<ll,ll>> resp;

ll timer = 0;

void dfs(ll u, ll p) {
	ll tree_edges = 0;

    //cout<< "visitando o " << u << "\n";
 
	vis[u] = true;
	lo[u] = id[u] = ++timer;
	for(ll& v : adj[u]){

        //cout<< "adicionando " << u << " " << v << "\n";
        if(resp.find({v,u}) == resp.end())
            resp.insert({u,v});

		if(v == p) continue;
		if(not vis[v]){
			tree_edges++;
			dfs(v, u);

            if(id[u]<lo[v]){
                cout << "IMPOSSIBLE\n";
                exit(0);
            }

			lo[u] = min(lo[u], lo[v]);
		}
		else{
			lo[u] = min(lo[u], id[v]);
		}
	}
	
}

// grafo SIMPLES

int main(){
    oiee;

    ll n, m; 
    cin >> n >> m;

    vis.resize(n+1, false);
    id.resize(n+1);
    lo.resize(n+1);
    adj.resize(n+1);

    for(ll i=0; i<m; i++){
        ll a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    dfs(1,1);
    // não é conexo
    for(ll i=2; i<=n; i++){
        if(!vis[i]){
            cout << "IMPOSSIBLE\n";
            return 0;            
        }
    }


    for(auto [u,v] : resp)
        cout << u << " " << v << "\n"; 

}