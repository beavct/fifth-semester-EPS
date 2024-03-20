#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

typedef struct{
    ll l;
    ll r;
}info;

int main(){
    oiee;

    string s; cin >> s;
    ll m; cin >> m;
    vector<info> infos(m);
    vector<ll> sums(s.size()+1, 0); 

    for(ll i=0; i<m; i++)
        cin >> infos[i].l >> infos[i].r;

    for(ll i=0;i<(ll)s.size();i++){
        if(s[i]==s[i+1])
            sums[i+1] += 1;
        //if(i>0 && s[i-1] == s[i])
        sums[i+1]+=sums[i]; 
    }
    

    //for(auto elem : sums)
    //    cout << elem << " ";
    //cout << endl;

    for(ll i=0; i<m; i++){
        cout << sums[infos[i].r-1] - sums[infos[i].l-1] << endl; 
    }
}