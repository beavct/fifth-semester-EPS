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


int main(){
    oiee;

    ll n; 
    cin >> n;

    vector<struct point> vertices(n, point(0,0));
    map<ll,bool> jafoi;
    ll cont=0;

    for(ll i=0; i<n; i++){
        cin >> vertices[i].x >> vertices[i].y;
        jafoi[i]=false;
    }

    cont=2;

    

    

}