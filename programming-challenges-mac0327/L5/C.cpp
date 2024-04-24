#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

void brute(){
    // x e y podem ser iguais
    ll n, x, y; cin >> n >> x >> y;
    vector<ll> a(n);

    for(ll i=0; i<n;i++)
        cin >> a[i];

    ll resp=0;

    for(ll i=0; i<n-1; i++){
        for(ll j=i+1; j<n; j++){
            if(((a[i]+a[j])%x==0) && ((a[i]-a[j])%y==0)){
                resp++;
                cout << "oie "<< i+1 << " " << j+1 <<"\n";
            }
        }
    }


    cout << resp << "\n";
}

void solve(){
    // x e y podem ser iguais
    ll n, x, y; cin >> n >> x >> y;
    vector<ll> a(n);

    for(ll i=0; i<n;i++)
        cin >> a[i];

    ll resp=0;
    // {resto por x, resto por y}, quant
    map<pair<ll,ll>, ll> divs;

    // pd
    for(ll i=0; i<n; i++){
        // restos do elemento atual
        pair<ll, ll> key = make_pair(a[i]%x, a[i]%y);
        //divs[key]++;

        // verifica pd

        ll aux_x = x-key.first, aux_y = key.second;
        //cout<<"auxs: " << aux_x << " " << aux_y << "\n";
        //if(divs[key] >0 && (a[i]+aux_x) ==x){
        //    resp+=divs[key];
        //    //cout<< "1: a[" << i+1 << "] "<< a[i] << "\n";
        //}
        //if(divs[{aux_x, 0}] >0){
        //    resp+=divs[{aux_x, 0}];
        //    //cout<< "2: a[" << i+1 << "] "<< a[i] << "\n";
        //}
        if(aux_x == x && divs.find({0, aux_y}) != divs.end()){
            resp+=divs[{0, aux_y}];
            //cout<< "3: a[" << i+1 << "] "<< a[i] << "\n";
        }
        if(divs.find({aux_x, key.second}) != divs.end()){
            resp+=divs[{aux_x, key.second}];
            //cout<< "4: a[" << i+1 << "] "<< a[i] << "\n";
        }

        divs[key]++;
    }

    //for(auto elem : divs){
    //    cout << elem.first.first << " " << elem.first.second << " " << elem.second << "\n";
    //}
    //cout << "\n";

    // 


    cout << resp << "\n";
}

int main(){
    oiee;

    ll t; cin >> t;

    for(ll i=0; i<t; i++)
        solve();

}