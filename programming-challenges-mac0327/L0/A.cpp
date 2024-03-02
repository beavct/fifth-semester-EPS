#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve(){
    ll x, y;
    ll elem;

    cin >> y >> x;

    if(x<y){
        if(y%2==0)
            elem = y*y-x+1;
        else
            elem = (y-1)*(y-1)+x;

    }
    else{
        if(x%2==0)
            elem= (x-1)*(x-1)+y;
        else
            elem = x*x-y+1;
    }

    cout << elem << endl;
}

//void solve(){
//        ll x, y;
//        ll elem;
//
//        // x: coluna
//        // y: linha
//
//        cin >> y >> x;
//
//        if(y%2 == 0){
//
//            if(x%2 == 0)
//                if(x<y)
//                    elem = y*y - x + 1;
//                else
//                    elem = pow((x-1),2) + y;
//            else 
//                if(x<y)
//                    elem = y*y-x+1;
//                else 
//                    elem = x*x-y+1;
//        }
//        else{
//
//            if(x%2==0)
//                if(x<y)
//                    elem = pow((y-1),2) + x;
//                else
//                    elem = pow((x-1),2) + y;
//            else 
//                if(x<y)
//                    elem = pow((y-1),2)+x;
//                else
//                    elem = x*x-y+1;
//
//        }
//
//        cout << elem << endl;
//
//}

int main(){
    ll t;

    cin >> t;

    for(ll i=0; i<t; i++){
        solve();
    }

}