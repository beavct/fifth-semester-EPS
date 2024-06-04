#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

struct point{
    double x, y;
    point(double x, double y) : x(x), y(y) {}

    point operator+(const point& other) const {
        return point(x+other.x, y+other.y);
    }

    point operator-(const point& other) const {
        return point(x-other.x, y-other.y);
    }

    double operator*(const point& other) const{
        return x*other.x + y * other.y;
    }

    double operator^(const point& other) const{
        return x * other.y - y * other.x;
    }

    point operator*(const ll t) const{
        return point(x * t, y * t);
    }


};

// dá duas vezes a área de um triângulo
double _2area(point a, point b, point c){
    return (b-a) ^(c-a);
}

bool left(point a, point b, point c){
    return _2area(a,b,c) > 0;
} 

bool right(point a, point b, point c){
    return _2area(a,b,c) < 0;
}

bool is_collinear(point a, point b, point c){
    return _2area(a,b,c) == 0;
}

void solve(){

    pair<double,double> a1, a2, a3;
    cin >> a1.first >> a1.second;
    cin >> a2.first >> a2.second;
    cin >> a3.first >> a3.second;

    struct point P1(a1.first, a1.second), P2(a2.first, a2.second), P3(a3.first, a3.second);

    if(is_collinear(P1,P2,P3))
        cout << "TOUCH\n";
    else if(left(P1,P2,P3)) 
        cout << "LEFT\n";
    else
        cout << "RIGHT\n";
}

int main(){
    oiee;

    ll t;
    cin >> t;

    for(ll i=0; i<t; i++)
        solve();
}