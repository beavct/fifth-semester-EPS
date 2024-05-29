#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAXP 32 
#define ll long long

vector<vector<int>> bss; // bss[a] representa a lista de adjacência do vértice a
vector<array<int, MAXP>> ps; // matriz de "pulos": ps[a][j] representa o 2**j-ésimo ancestral do vértice a
vector<int> ls, rs; // ls[a] e rs[a] representam respectivamente o tempo inicial e final da DFS no vértice a
int c=0; // contador de tempos para a DFS

void dfs(ll a, ll p) {

	ps[a][0] = p; // incializa o primeiro ancestral de a como o pai na DFS
	ls[a] = c++;

	for(ll b : bss[a])
		if(b != p)
			dfs(b, a);

	rs[a] = c++;

}

int main() {
    oiee;

    ll n, q;
    //cin >> n >> q;
    scanf("%lld %lld", &n, &q);

	// define o tamanho dos vetores
	bss.resize(n);
	ps.resize(n);
	ls.resize(n, -1);
	rs.resize(n, -1);

	// lê as arestas
	for(ll i=1; i<n; i++) {
        ll a; //cin >> a;
        scanf("%lld", &a);
        a--;
        bss[a].push_back(i);     
        //bss[i].push_back(a);
	}

	// aplica a DFS partindo do vértice zero, fazendo com que a árvore seja enraizada nesse vértice
    for(ll i=0; i<n; i++){
        if(ls[i]==-1)
            dfs(i,i);
    }

	// inicializa a matriz de "pulos"
	for(ll j=0; j<MAXP-1; j++) {
		for(ll i=0; i<n; i++)
			ps[i][j+1] = ps[ps[i][j]][j];
	}

    //cout << "------------------------\n";
    //for(auto linha : ps){
    //    for(auto elem: linha)
    //        cout << elem <<" ";
    //    cout << "\n";
    //}
    //cout << "-------------------------\n\n";

	// processa as consultas
	for(ll i=0; i<q; i++) {


		ll x, k; //cin >> x >> k;
        scanf("%lld %lld", &x, &k);
		x--; 
        ll resp=x;
        ll save=k;

        for(ll j=MAXP-1; j>=0; j--){
            if(k & (1 << j)){
                save--;
                if(ps[resp][j]==resp && save>0){
                    //cout << "entrou aq\n" << "k = " << k << "\n";
                    resp=-1;
                    break;
                }
                //cout << "k " << k << " j " << j << " respA = " << resp << "\n";
                resp=ps[resp][j];
                //cout << "respD = " << resp << " k " << k<< "\n";
                //k = (k & (1 << j));

            }


        }

        if(resp==-1){
            cout << resp << "\n";
            continue;
        }
        cout << resp+1 << "\n";

	}

	return 0;	
}

/*
8 9
1 1 3 3 4 6 2
7 1
7 2
7 3
7 4
7 5
8 1
8 2
8 3
1 3

saida:


6
4
3
1
-1
2
1
-1
-1
*/
