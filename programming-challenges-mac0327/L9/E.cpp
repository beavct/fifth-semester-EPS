#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> vis; 
vector<ll> id, lo;
vector<vector<ll>> adj;
vector<pair<ll,ll>> resp;

ll quant_vc = 0;
ll timer = 0;

void dfs(int u, int p) {
	vis[u] = true;
	lo[u] = id[u] = ++timer;
	for(ll& v : adj[u]){
		if(v == p) continue;
		if(not vis[v]){
			dfs(v, u);
			if(id[u] < lo[v]) 
				resp.push_back({u, v});
			lo[u] = min(lo[u], lo[v]);
		}
		else{
			lo[u] = min(lo[u], id[v]);
		}
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

    for(ll i=0; i<m; i++){
        ll a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    cout << resp.size() << "\n";
    for(auto [u,v] : resp)
        cout << u << " " << v << "\n";

}