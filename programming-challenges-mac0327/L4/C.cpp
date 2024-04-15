#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll a, b; cin >> a >> b;

    vector<vector<ll>> bolo(a+1, vector<ll>(b+1, INT64_MAX));

    for(ll i=0; i<=a; i++)
        bolo[i][0]=i;

    for(ll i=0; i<=b; i++)
        bolo[0][i]=i;

    for(ll i=1; i<=a; i++){
        for(ll j=1; j<=b; j++){
            // já é um quadrado, 0 movs
            if(i==j)
                bolo[i][j] = 0;
            else{
                for(ll k=1; k<i && i>k; k++)
                    bolo[i][j] = min(bolo[i][j], bolo[k][j]+bolo[i-k][j]+1);

                for(ll k=1; k<j && j>k; k++)
                    bolo[i][j] = min(bolo[i][j], bolo[i][k]+bolo[i][j-k]+1);
            }


            //for(ll aux1=0; aux1<=a; aux1++){
            //    for(ll aux2=0; aux2<=b; aux2++)
            //        cout << bolo[aux1][aux2] << " ";
            //    cout << "\n";
            //}
            //cout << "\n--------------------------------------------------\n";
        }
    }

    //for(ll i=0; i<=a; i++){
    //    for(ll j=0; j<=b; j++)
    //        cout << bolo[i][j] << " ";
//
    //    cout << "\n";
    //}

    cout << bolo[a][b] << "\n";

}