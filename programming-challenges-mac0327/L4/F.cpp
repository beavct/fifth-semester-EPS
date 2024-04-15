#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll n; cin>> n;
    vector<ll> sizes(3); 

    for(ll i=0; i<3; i++)    
        cin >> sizes[i];

    vector<ll> pd_fita(n+1, 0);

    for(ll i=1; i<=n; i++){
        for(auto elem : sizes){
            // não pode ter restos
            if(elem <= i && (elem == i || pd_fita[i-elem]>0))
                pd_fita[i] = max(pd_fita[i], pd_fita[i-elem]+1);
        }
    }

    //for(auto elem : pd_fita)
    //    cout << elem << " ";
    //cout << endl;

    cout << pd_fita[n] << endl;
}