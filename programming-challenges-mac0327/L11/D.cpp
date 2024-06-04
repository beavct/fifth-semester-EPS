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

double dist(point a, point b){
    return sqrt((a-b)*(a-b));
}


int main(){
    oiee;

    // infos do circulo
    ll R;
    cin >> R;
    point c1(0,0);
    cin >> c1.x >> c1.y;

    // pontos da reta
    point r1(0,0), r2(0,0);

    cin >> r1.x >> r1.y;
    cin >> r2.x >> r2.y;

    //double dist = 

    // comprimento da reta
    double reta = dist(r1, r2);

    // area do triangulo 
    /*
    
    r1 -------- r2
     \        /
      \     /
       \  /
        c1
    
    */
    double triangulo = abs(_2area(c1, r1, r2));

    // para encontrar a altura h -> dividir pela base b
    double h = triangulo/reta;

    if(h>R)
        cout << "-1\n";
    else if(h==R)
        cout << "0\n";
    else{
        // calcular comprimento usando triangulo retangulo
        cout << fixed << setprecision(5);

        double comp_sobre2 = sqrt((R*R) - (h*h));

        cout << comp_sobre2*2 << "\n";

    }

}