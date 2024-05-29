#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

ll n, m;
vector<vector<ll>> adj;
vector<ll> times;
vector<bool> mark;

bool bfs(ll src){
    queue<ll> q;

    q.push(src);
    mark[src] = true;

    times[src]=1;

    while(!q.empty()){
        ll cur = q.front(); q.pop();

        for(auto viz : adj[cur]){
            if(mark[viz]){
                if(times[viz]==times[cur])
                    return false;
                continue;
            }
            q.push(viz);
            mark[viz] = true;

            times[viz] = (times[cur] == 1 ? 2 : 1);
        }
    }

    return true;
 }

int main(){
    oiee;

    cin >> n >> m;

    adj.resize(n+1);
    times.resize(n+1);
    mark.resize(n+1, false);

    for(ll i=0; i<m; i++){
        ll a, b; 
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    
    bool ok;
    for(ll i=1; i<=n; i++){
        if(!mark[i])
            ok = bfs(i);
        if(!ok)
            break;
    }

    if(!ok)
        cout << "IMPOSSIBLE\n";
    else{
        for(ll i=1; i<=n; i++)
            cout << times[i] << " ";
        cout << "\n";
    }

}