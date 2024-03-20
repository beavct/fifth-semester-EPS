#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int tds_sobremesas(vector<ll> &b){
    for(ll i=1; i<4; i++)
        if(b[i]==0)
            return 0;

    return 1;
}

void solve(){
    string s; cin >> s;

    ll l=0, r=0;
    ll min=s.size();
    //int flag=0;
    int oie=0;
    vector<ll> sobremesas(4,0);

    while(r<(ll)s.size()){

        //cout << "l= " << l << " r= " << r << endl;

        //flag=tds_sobremesas(sobremesas);
        //cout << "flag= " << flag << endl;
//
        //if(flag){
        //    //cout << "entrou aq1" << endl;
        //    oie=1;
        //    if(min>r-l+1){
        //        min=r-l+1;
        //        //cout << "entrou aq1.2" << endl;
        //    }
        //    sobremesas[(int)s[l]-48]--;
        //    l++;
        //}
        //else{
        //    //cout << "entrou aq2" << endl;
        //    r++;
        //    sobremesas[(int)s[r]-48]++;
        //}

        sobremesas[(int)s[r]-48]++;
        while(tds_sobremesas(sobremesas) && l<(ll)s.size()){

            if(min>r-l+1){
                min=r-l+1;
            }

            sobremesas[(int)s[l]-48]--;
            l++;

            oie=1;

        }
        r++;

    }

    if(oie)
        cout<< min << endl;
    else    
        cout<< "0" << endl;
}

int main(){
    oiee;

    ll t; cin >> t; 

    for(ll i=0; i<t; i++)
        solve();
}