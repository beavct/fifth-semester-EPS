#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main(){
    ll n;
    ll x = 0;

    cin >> n;

    for(ll i=0; i<n; i++){
        string d;

        cin >> d;

        if(d[0] == '+' or d[2] == '+')
            x++;
        else 
            x--;
    }

    cout << x << endl;

}