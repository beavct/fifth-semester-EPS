#include <bits/stdc++.h>

using namespace std;

#define ll long long

int main(){
    ll n;

    cin >> n;

    vector<ll> nums(n+2, 0);

    for(ll i=1; i<=n-1; i++){
        ll p;

        cin >> p;
        
        nums[p] = 1; 
    }

    for(ll i=1; i<=n; i++)
        if(nums[i] == 0){
            cout << i << endl;
            break;
        }
    
}