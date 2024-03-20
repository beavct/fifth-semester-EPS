#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

typedef struct{
    ll x1;
    ll x2;
}info;

int main(){
    oiee;

    ll n, h; cin >> n >> h;

    vector<info> infos(n);
    // vetores soma acumulada
    vector<ll> d_sol(n+1,0);
    vector<ll> d_nublados(n+1,0);

    for(ll i=1; i<=n; i++){
        cin >> infos[i-1].x1 >> infos[i-1].x2;
        d_nublados[i]+=d_nublados[i-1];
        d_nublados[i]+=(infos[i-1].x2-infos[i-1].x1);
    }

    // dias de sol entre intervalo i e i+1 está em i+1
    for(ll i=0; i<n-1; i++){
        d_sol[i+1]+=d_sol[i];
        d_sol[i+1]+=(infos[i+1].x1-infos[i].x2);
    }
    d_sol[n]=INT64_MAX;

    //for(auto elem:d_nublados){
    //    cout << elem << " ";
    //}
    //cout << endl;
//
    //    for(auto elem:d_sol){
    //    cout << elem << " ";
    //}
    //cout << endl;

    ll max_d=0,h_aux=0;
    ll l=0,r=0;

    while(l<n){
        if(h_aux<h){
            h_aux=d_sol[r]-d_sol[l];
            if(h_aux<h)
                r++;
            //cout << "1: h_aux= " << h_aux << " l= " << l << " r= " << r << endl;
        }
        else{
            h_aux=d_sol[r-1]-d_sol[l];
            ll aux_d_rest=max(h-h_aux,(ll)0);
            //cout << "3: h_aux= " << h_aux << " aux_d_rest= " << aux_d_rest << " max_d= " << max_d << endl;
            max_d=max(max_d, d_nublados[r]-d_nublados[l]+aux_d_rest+h_aux);
            //cout << "4: d_nublados[r-1]= " << d_nublados[r] << " d_nublados[l]= " << d_nublados[l] << endl;
            //cout << "5: h_aux= " << h_aux << " aux_d_rest= " << aux_d_rest << " max_d= " << max_d << endl;
            //cout << "---------------------------------------------------------------------------------------------\n";
            h_aux-=d_sol[l++];
            //cout << "2: h_aux= " << h_aux << " l= " << l << " r= " << r << endl;

        }
    }
        // l<n-1, pq o d_sol na casa n é o int_max

    cout<< max_d << endl;    
}