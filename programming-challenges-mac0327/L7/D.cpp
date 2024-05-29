#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

const ll MAX = 1e6;
const ll oo = 1e18;

ll dist[MAX];
ll n, m; 
vector<vector<pair<ll,ll>>> adj;
vector<vector<pair<ll,ll>>> adj_aux;
vector<ll> resp;
vector<ll> parent;

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
				dist[viz] = dist[cur] + c;
				st.insert({dist[viz], viz});
                parent[viz]=cur;
			}
		}

	}
}

void build_ans(){
    ll i=n;


    while(i > 1){
        resp.push_back(i);


        //ll aux_c = oo;
        ll aux_v = -1;
        for(auto it = adj_aux[i].begin(); it != adj_aux[i].end(); ++it){
            ll b = it->first;
            ll c = it->second;

            //cout << b << endl;
            if(dist[b]+c == dist[i]){
                aux_v = b;
                //aux_c = c;
            }
        }

        i = aux_v;
    }

    resp.push_back(1);
}

int main(){
    oiee;

    // n: # vértices, m: # arestas
	cin >> n >> m;

	adj.resize(n+1);
    //adj_aux.resize(n+1);
    parent.resize(n+1, -1);

	for(ll i=0; i<m; i++){
        // o grafo não necessariamente é simples
        // a, b: extremos da aresta, c: comprimento
		ll a, b; ll c;
        cin >> a >> b >> c;

		adj[a].push_back({b, c});
        adj[b].push_back({a, c});

        //adj_aux[b].push_back({a,c});
	}

	dijkstra(1);

    if(dist[n]==oo)
        cout << "-1\n";
    else{
        //cout << "a dist é " << dist[n] << endl;
        //build_ans();


        ll cur = n; 
        while(cur > 1){
            resp.push_back(cur);
            //cout << "adicionando " << cur << "\n";
            cur=parent[cur];

            if(parent[cur]==-1 && cur!=1){
                cout << "-1\n";
                return 0;
            }

        }
        resp.push_back(1);
        for(ll i=(ll)resp.size()-1; i>=0;i--)
            cout << resp[i] << " ";
        cout << "\n";

    }   
}

/*

8
8
1 2 1
2 3 1    
3 4 1
4 5 1
5 6 1
6 8 1
1 7 20
7 8 20 

resp: 1 2 ... 6 8


*/

/*
3 3
1 3 10
1 2 5
2 3 6


resp: 1 3


*/