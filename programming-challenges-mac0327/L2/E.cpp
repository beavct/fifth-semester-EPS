#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define dl double long

void solve(){
    dl n; cin >> n;
    vector<ll> h(n);
    ll soma_total=0;

    for(ll i=0; i<n; i++){
        cin >> h[i];
        soma_total+=h[i];
    }

    if(n>0)
        sort(h.begin(), h.end());
    else{
        cout << "0" << endl;
        return; 
    }

    // dl aux_soma=soma_total-(soma_total*(n-2))/n;
    dl aux_soma=(2*soma_total);
    ll w=0;
    ll l=0, r=n-1;

    while(l<r){
        dl soma_atu=(h[l]+h[r])*n;

        if(soma_atu == aux_soma){
            //cout <<"h[l]= " <<  h[l] << " h[r]= " << h[r] << endl;
            //cout << "l= " << l << " r=" << r << endl;
            //cout << "oie" << endl;
            if(h[l]!=h[r]){
                // 1 pois já está contando o h[l]==h[r]
                ll contL=1; 
                ll contR=1;

                while(l<r && h[l]==h[l+1]){
                    contL++;
                    l++;
                }

                //cout << "contou os esquerdos\n";

                while(l<r && h[r]==h[r-1]){
                    contR++;
                    r--;
                }

                //cout << "contou os direitos\n";
                l++;
                r--;

                w=w+(contL*contR);

                //cout << "l= " << l << " r= " << r << " w= "<< w << endl; 
            }
            else{ // todos os elementos entre h[l] e h[r] são iguais
                //cout << "são iguaiss\n";

                w+=(((r-l+1)*(r-l))/2);
                break;
            }
        }
        else if(soma_atu < aux_soma)
            l++;
        else if(soma_atu > aux_soma)
            r--;

    }

    cout<< w << endl;
}

int main(){
    oiee;

    ll t; cin >> t;

    for(ll i=0; i<t; i++)
        solve();
}