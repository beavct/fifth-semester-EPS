#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll n, k; cin >> n >> k;
    vector<ll> a(n);

    for(ll i=0; i<n; i++)
        cin >> a[i];

    // ordem crescente
    if(n>0)
        sort(a.begin(), a.end());

    unordered_set<ll> resp;

    // x<y
    // y = x*k => x = y/k onde y=a[i] e nós já olhamos para o x 
    for(ll i=0; i<n; i++){
        if(a[i]%k!=0 || resp.find(a[i]/k)==resp.end())
            resp.insert(a[i]);
    }


    cout << resp.size() << "\n";

}
