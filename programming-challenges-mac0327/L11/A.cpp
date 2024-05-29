#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

struct point{
    ll x, y;
    point(ll x, ll y) : x(x), y(y) {}

    point operator+(const point& other) const {
        return point(x+other.x, y+other.y);
    }

    point operator-(const point& other) const {
        return point(x-other.x, y-other.y);
    }

    ll operator*(const point& other) const{
        return x*other.x + y * other.y;
    }

    ll operator^(const point& other) const{
        return x * other.y - y * other.x;
    }

    point operator*(const ll t) const{
        return point(x * t, y * t);
    }


};

// dá duas vezes a área de um triângulo
ll _2area(point a, point b, point c){
    return (b-a) ^(c-a);
}

bool left(point a, point b, point c){
    return (b-a) ^ (c-a) > 0;
} 

bool right(point a, point b, point c){
    return (b-a) ^(c-a) < 0;
}

bool is_collinear(point a, point b, point c){
    return (b-a) ^(c-a) == 0;
}

int main(){
    oiee;

    pair<ll,ll> a1, a2, a3;
    cin >> a1.first >> a1.second;
    cin >> a2.first >> a2.second;
    cin >> a3.first >> a3.second;

    struct point P1(a1.first, a1.second), P2(a2.first, a2.second), P3(a3.first, a3.second);


}