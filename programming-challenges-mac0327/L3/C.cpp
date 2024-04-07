#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll m; cin >> m;

    vector<ll> resp;
    ll fat5=0;

    for(ll i=1; i<INT64_MAX; i++){
        ll aux1=i;
        while(aux1/5>0 && aux1%5==0){
            aux1/=5;
            fat5++;
        }

        
        if(fat5==m)
            resp.push_back(i);
        else if(fat5>m)
            break;

    }

    cout << resp.size() << "\n";
    if(resp.size()>0){
        for(auto elem:resp)
            cout << elem << " ";
        cout << "\n";
    }

    return 0;
}