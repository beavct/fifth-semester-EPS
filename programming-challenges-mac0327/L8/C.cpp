#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

/* DSU
 * são dadas uma quantidade de elementos (qv), e uma quantidade de informações e perguntas (qq)
 * é dado também um conjunto de qq informações e perguntas
 * informação (a b !): a e b estão no mesmo conjunto
 * pergunta (a b ?): deve ser respondido se a e be estão no mesmo conjunto
 *
 * Entrada:

5 6
1 2 !
3 2 !
4 5 !
1 3 ?
1 5 ?
3 4 !
1 5 ?

 * Saída:

1 3 ? sim
1 5 ? não
1 5 ? sim

 */

#include<iostream>
#include<vector>

using namespace std;

ll find(vector<ll>& ps, int a) {
	vector<ll> ms;
	while(ps[a] != -1) {
		ms.push_back(a);
		a = ps[a];
	}
	for(int m : ms) 
		ps[m] = a;
	return a;
}

void join(vector<ll>& ps, vector<ll>& ws, int a, int b) {
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
	for(int m : ms){
		ws[m]=ws[a];
		ps[m] = a;
	}
}

int main(){
    oiee;

    ll n; 
    cin >> n;

	vector<ll> ps(n, -1);
	vector<ll> ws(n, 1);
    vector<pair<ll,ll>> resp_d;
    vector<pair<ll,ll>> resp_c;


	for(ll i=0; i<n-1; i++){
		ll u, v;
        cin >> u >> v; 

		// não precisa dar join pois os vértices já estão na mesma componente
		// pode guardar a aresta supérflua
        if(find(ps, u-1) == find(ps, v-1)){
            resp_d.push_back({u,v});
        }
        else{
		    join(ps, ws, u-1, v-1);
        }
	}

    for(ll i=1; i<n; i++){
		for(ll j=i+1; j<=n; j++){
			if(find(ps, i-1) != find(ps,j-1)){
				resp_c.push_back({i,j});
				join(ps, ws, i-1, j-1);
			}
		}
    }

    cout << resp_c.size() << "\n";
    for(ll i=0; i<(ll)resp_c.size(); i++){
        cout << resp_d[i].first << " " << resp_d[i].second;
        cout << " " << resp_c[i].first << " " << resp_c[i].second << "\n";  
    }


}