#include <bits/stdc++.h>
    
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

const ll MAX = 1e6;
const ll oo = 1e18;

ll n, m; 
ll dist[MAX];
vector<vector<pair<ll,ll>>> adj;
vector<ll> parent;
ll max_r=0;

void dijkstra(ll src){
	for(ll i=1; i<=n; i++) dist[i] = oo;
	set<pair<ll,ll>> st;

	st.insert({0, src});
	dist[src] = 0;

	while(not st.empty()){
		ll cur = st.begin()->second; st.erase(st.begin());

		for(auto [viz, c] : adj[cur]){
			if(dist[cur] + c < dist[viz]){
				st.erase({dist[viz], viz});
				dist[viz] = dist[cur] + c/2;
				st.insert({dist[viz], viz});
                parent[viz]=cur;
			}
		}

	}
}

int main(){
    oiee;

    cin >> n >> m;
    // m linhas
    parent.resize(n+1, -1);
    adj.resize(n+1);

    for(ll i=0; i<m; i++){
        ll a,b,c; cin >> a >> b >> c;

        adj[a].push_back({b,c});
    }

    dijkstra(1);

    if(dist[n] == oo){
        cout << oo << "\n";
        return 0;
    }

    ll cur = n;
    ll sum=0;

    while(cur>1){
        ll aux = parent[cur];
        ll ay=0;
        for(auto elem : adj[aux])
            if(elem.first == cur){
                ay = elem.second;

                //cout << "pai do " << cur << "\n";
                break;
            }

        sum+=ay;

        if(ay > max_r)
            max_r = ay;

        cur = aux;
    }

    //cout << max_r << " " << max_r/2 << "\n";

    cout << (sum-max_r+max_r/2) << "\n";
}