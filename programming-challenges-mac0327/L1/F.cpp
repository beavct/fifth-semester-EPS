#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

// só pra saber o resultado certo quando o valor nçao é mto grande
void teste(ll n, ll m, ll k){
    vector<ll> tab(n*m);

    for(ll i=0; i<n; i++){
        for(ll j=0; j<m; j++){
            tab[(i*m)+j] = (i+1)*(j+1);
            //cout << tab[(i*m)+j] << " ";
        }

        //cout << endl;
    }

    //cout << "-------------------------------------------" << endl << endl;

    sort(tab.begin(), tab.end());

    for(auto elem : tab)
        cout << elem << " ";
    cout << endl;

    cout << tab[k-1] << endl;
}

void solve(ll n, ll m, ll k){
    ll left=1, right=n*m;
    ll resp=right;

    while(left<=right){
        // elemento da matriz
        ll mid = (left+right)/2;

        //cout <<" ANTES right= " << right << " left= " << left <<" mid= " << mid << endl;

        ll menores=0;
        for(ll i=1; i<=n; i++){
            if(m<mid/i)
                menores+=m;
            else    
                menores+=mid/i;

            //cout << "menores= " << menores << " i= " << i << endl;
        }

        //cout <<" DEPOIS menores= " << menores <<  " right= " <<  right << " left= " << left <<" mid= " << mid << endl;

        if(menores < k){
            left = mid+1;
        }
        else{
            //cout << "RESP= " << resp << endl;
            resp = mid;
            right = mid-1;

        }
    }

    cout<< resp << endl;
}

int main(){
    oiee;

    ll n, m, k; cin >> n >> m >> k;

    //teste(n, m, k);

    solve(n,m,k);

}