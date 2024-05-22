#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

vector<bool> vis; 
vector<ll> id, lo;
vector<vector<ll>> adj;
vector<ll> resp;
stack<ll> q;

ll timer = 0;

void dfs(ll u, ll p) {
	vis[u] = true;

	lo[u] = id[u] = ++timer;
            
    q.push(u);

	for(ll& v : adj[u]){

		if(v == p) continue;

		if(not vis[v]){
			dfs(v, u);
			lo[u] = min(lo[u], lo[v]);
		}
		else{
            resp.push_back(v);

            ll aux;

            while(!q.empty()) {
                aux = q.top();
                //cout << "deu push no " << aux << "\n";
                q.pop();
                resp.push_back(aux);
                if(aux == v)
                    break;

            }
			lo[u] = min(lo[u], id[v]);

                
            cout << resp.size() << "\n";
            for(auto v : resp)
                cout << v << " ";
            cout << "\n";
    
            exit(0);
            
		}
	}

    q.pop();
}

int main(){
    oiee;

    // n: jardins, m: rotas
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

    
    for(ll i=1; i<=n; i++){
        if(!vis[i]){
            dfs(i, i);
        }
    }

    cout << "IMPOSSIBLE\n";

}
