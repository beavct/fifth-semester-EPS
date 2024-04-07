#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long
#define dl double long

//O(sqrt(n))
void find_divisors(int n, set<ll>& divisors){
	for(int d=1; d*d<=n; d++){
		if(n%d == 0){
			divisors.insert(d);
			divisors.insert(n/d);
		}
	}
}

void solve1(){
    ll x, n; cin >> x >> n;

    ll mdc_max=1;

    if(x%n==0){
        mdc_max=x/n;
    }
    else{
        ll div = x/n;
        set<ll> divs;
        find_divisors(x, divs);

        auto l = divs.begin(), r = prev(divs.end());
        while(distance(l, r) > 0){
            auto mid = next(l, distance(l, r) / 2);

            if(*mid <= div){
                mdc_max=max(*mid, mdc_max);
                l=next(mid);
            }
            else
                r=mid;

        }

    }

    cout << mdc_max << "\n";    
}

int main(){
    oiee;

    ll t; cin  >> t;

    for(ll i=0; i<t; i++)
        solve1();

}