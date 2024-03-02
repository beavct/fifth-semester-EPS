#include <bits/stdc++.h>

using namespace std;

#define ll long long

//ll soma(vector<ll> a){
//    ll soma = 0;
//
//    for(auto elem : a)
//        soma+= elem;
//
//    return soma;
//}

// retorna 1 se é não mod 3
int mod3(ll a){
    return a%3!=0;
}

// retorna 1 se todos são diferentes
int diff(ll a, ll b, ll c){
    return (a!=b && b!=c && a!=c);
}

void solve(){
    ll n;

    cin >> n;

    // Inteiros positivos distintos que não devem ser divisíveis por 3
    ll x, y, z;

    for(x=1; x<n; x++){
        for(y=x+1; y<n; y++){
            z = n-x-y;

            // diferentes, n são mod 3, z>0
            if(z>0 && diff(x,y,z) && mod3(x) && mod3(y) && mod3(z)){
                cout << "YES" << endl << x << " " << y << " " << z << endl;
                return;
            }
        }
    }

    cout << "NO" << endl;
}

int main(){
    ll t;

    cin >> t;

    for(ll i=0;i <t; i++){
        solve();
    }

}