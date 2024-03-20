#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

typedef struct{
    ll l;
    ll r;
}info;

int main(){
    oiee;
    // n jogadores, q rounds
    ll n, q; cin >> n >> q;

    // força dos heróis
    vector<ll> a(n); 
    for(ll i=0; i<n; i++)
        cin >> a[i];
    if(n>0)
        sort(a.begin(), a.end());
    
    // descrição dos heróis que participarão do i-ésimo round
    vector<info> infos(q); 
    for(ll i=0; i<q; i++)
        cin >> infos[i].l >> infos[i].r;

    // soma acumulada, ver quais indices participam mais dos rounds e colocar o heroi de maior força pra ser ele
    
    ll resp=0;
    // indexado a partir do 1
    vector<ll> soma(n+2,0);

    for(ll i=0; i<q; i++){
        soma[infos[i].l]++;// começo do intervalo
        if(infos[i].r+1<=n)
            soma[infos[i].r+1]--; // fim do intervalo
        //for(ll j=infos[i].l; j<=infos[i].r; j++){
        //    soma[(int)j]+=1;
        //}
    }

    //for(auto elem:soma)
    //    cout << elem<< " ";
    //cout << endl;

    for(ll i=1; i<=n; i++)
        soma[i]+=soma[i-1];
    sort(soma.begin(), soma.end());

    //for(auto elem:soma)
    //    cout << elem<< " ";
    //cout << endl;
    
    for(ll i=2; i<=n+1; i++){
        resp+=soma[i]*a[i-2];
    }

    cout << resp << endl;


}