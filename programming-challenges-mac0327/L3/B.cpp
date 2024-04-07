#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

// mmc(a,b) = (a*b)/mdc(a,b)
ll mmc(ll a, ll b){
    if(a<b)
        swap(a,b);

    ll res=1;
    ll a_aux=a, b_aux=b;

    while(res!=0){
        res = a_aux%b_aux;

        a_aux=b_aux;
        b_aux=res;
    }
    
    return (a*b)/a_aux;
}


bool is_prime(int n){
	if(n == 1) 
        return false;

    

	bool flg = true;
	for(int i=2; i*i<=n; i++)
		if(n%i == 0){
            flg = false;

        }

	return flg;
}

void solve(){
    ll n; cin >> n;

    if(n%2==0){
        cout << n/2 << " " << n/2 << "\n";
        return;
    }
    else if(is_prime(n)){
        cout << n-1 << " " << 1 << "\n";
    }
    else{
        ll div=1;
        for(ll i=3; i<n/2;i++)
            if(n%i==0){
                div=i;
                break;
            }
        cout << n/div << " " << n-(n/div) << endl;        
    }
}

int main(){
    oiee;

    ll t; cin  >> t;

    for(ll i=0; i<t; i++)
        solve();

    //cout << "-------------------------\n";
//
    //for(ll i=1; i<t; i++){
    //    cout << i << " " << t-i << " " << mmc(i, t-i) << endl;
    //}

}