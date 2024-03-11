#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll n, t;
    cin >> n >> t;

    vector<ll> k (n);
    for(ll i=0; i<n; i++)
        cin >> k[i];

    ll right; // máq. mais lerda * quant. produtos
    ll left=0;

    if(n>0){
        sort(k.begin(), k.end());
        right=k[n-1]*t;
    }
    else{
        right=0;
    }
    
    ll resp=right;
    

    while(left<=right){
        ll temp_medio=(right+left)/2;
        ll t_aux=0;

        for(ll i=0; i<n && t_aux<=t; i++){
            t_aux += temp_medio/k[i];
        }

        if(t_aux<t){
            left=temp_medio+1;
        }
        else{
            resp=temp_medio;
            right=temp_medio-1;
        }    

    }

    cout << resp << endl;

}