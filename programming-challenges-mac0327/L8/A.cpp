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

vector<pair<ll,ll>> estradas;

ll comp, comp_max;

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
		comp--;
		ws[a] += ws[b];

		if(ws[a]>comp_max)
			comp_max = ws[a];
			
		ms.push_back(b);
	}
	for(int m : ms){
		ws[m]=ws[a];
		ps[m] = a;
	}
}

int main(){
    oiee;

    ll n, m; 
    cin >> n >> m;

	comp=n;
	comp_max=1;

	vector<ll> ps(n, -1);
	vector<ll> ws(n, 1);
	estradas.resize(m);


	for(ll i=0; i<m; i++){
		cin >> estradas[i].first >> estradas[i].second; 
	}


	for(ll i=0; i<m; i++){
		join(ps, ws, estradas[i].first-1, estradas[i].second-1);
		cout << comp << " " << comp_max << "\n";
	}

}