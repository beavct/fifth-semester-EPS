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

// fios existentes
vector<pair<ll,ll>> fios_E;

ll comp;

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
		comp--;
	}
	for(int m : ms){
		ws[m]=ws[a];
		ps[m] = a;
	}
}

int main(){
    oiee;

    ll N, M; 
    cin >> N >> M;

	comp=N;

	vector<ll> ps(N, -1);
	vector<ll> ws(N, 1);
	fios_E.resize(M);
	unordered_map<ll,ll> arestasoie;

    // índice é o número do fio
    // leitura de todos os fios
	for(ll i=0; i<M; i++){
		ll u, v;
		cin >> u >> v;
		fios_E[i].first = u-1;
		fios_E[i].second = v-1;
		arestasoie[i+1]=0;
	}

    ll Q;
    cin >> Q;

    // fios que serão cortados
    vector<ll> fios_C;

    // leitura dos fios q serão cortados
	for(ll i=0; i<Q; i++){
        ll aux;
		cin >> aux;

        fios_C.push_back(aux); 
		arestasoie[aux]=1;

	}

    vector<ll> resp;


	for(ll i=1; i<=M; i++){

		if(!arestasoie[i]){
			join(ps, ws, fios_E[i-1].first, fios_E[i-1].second);
		}
	}

	for(ll i=(ll)fios_C.size()-1; i>=0; i--){

		resp.push_back(comp);
		join(ps, ws, fios_E[fios_C[i]-1].first, fios_E[fios_C[i]-1].second);
	}


    for(ll i=(ll)resp.size()-1; i>=0; i--)
        cout << resp[i] << " ";
    cout << "\n";

}