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
    return _2area(a,b,c) > 0;
} 

bool right(point a, point b, point c){
    return _2area(a,b,c) < 0;
}

bool is_collinear(point a, point b, point c){
    return _2area(a,b,c) == 0;
}

int main(){
    oiee;

    ll n; 
    cin >> n;

    vector<struct point> vertices(n, point(0,0));

    for(ll i=0; i<n; i++)
        cin >> vertices[i].x >> vertices[i].y;

    // area de um poligono qualquer (pode ser irregular) -> cross product 

    ll resp=0;

    for(ll i=0; i<n-1; i++){
        resp+=vertices[i]^vertices[i+1];
    }

    resp+=vertices[n-1]^vertices[0];

    cout << abs(resp) << "\n";


}

/*
6
3 -3
2 1 
4 7 
-6 2
-1 -2
-3 -5


106

*/