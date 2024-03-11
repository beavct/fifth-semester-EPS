#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

void bin_search(ll moeda, vector<ll> &precos){
    ll left=0, right=(ll)precos.size()-1;
    ll resp=0;

    while(left<=right){
        ll mid = (left+right)/2;

        if(precos[mid] > moeda)
            right=mid-1;
        else if(precos[mid] <= moeda){
            resp = mid+1;
            left = mid+1;   
        }
    }

    cout << resp << endl;
}

int main(){
    oiee;

    ll n; cin >> n;

    vector<ll> precos (n); 
    for(ll i=0; i<n; i++)
        cin >> precos[i];

    ll q; cin >> q;

    vector<ll> moedas(q);
    for(ll i=0; i<q; i++)
        cin >> moedas[i];

    if(n>0)
        sort(precos.begin(), precos.end());

    //for(auto elem : precos )
    //    cout << elem << " ";

    for(ll i=0; i<q; i++)
        bin_search(moedas[i], precos);        


}