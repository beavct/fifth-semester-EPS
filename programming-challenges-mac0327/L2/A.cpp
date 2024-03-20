#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll n, k; cin >> n >> k;
    string s;
    if(n>0)
        cin >> s;

    ll resp=0;
    ll l=0, r=-1, aux=0;
    vector<ll> letras(2,0);

    while(r<n){
        if(aux<=k){
            if(resp<r-l+1)
                resp=r-l+1;

            r++;
            if(s[r]=='a')
                letras[0]++;
            else
                letras[1]++;
        }
        else{
            if(s[l]=='a')
                letras[0]--;
            else    
                letras[1]--;

            l++;
        }

        aux=min(letras[0],letras[1]);

    }

    cout << resp << endl;

}