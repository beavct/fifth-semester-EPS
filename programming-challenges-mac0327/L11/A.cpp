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

    pair<double,double> a1, a2, a3;
    cin >> a1.first >> a1.second;
    cin >> a2.first >> a2.second;
    cin >> a3.first >> a3.second;

    struct point P1(a1.first, a1.second), P2(a2.first, a2.second), P3(a3.first, a3.second);

    // formula de dist entre dois pontos
    //double per = sqrt((P2.x - P1.x)*(P2.x - P1.x) + (P2.y - P1.y)*(P2.y - P1.y)) +
    //            sqrt((P3.x - P2.x)*(P3.x - P2.x) + (P3.y - P2.y)*(P3.y - P2.y)) +
    //            sqrt((P1.x - P3.x)*(P1.x - P3.x) + (P1.y - P3.y)*(P1.y - P3.y));

    double per = sqrt((P1-P2)*(P1-P2)) +
                sqrt((P1-P3)*(P1-P3))+
                sqrt((P2-P3)*(P2-P3));


    double area2 = _2area(P1, P2, P3);

    cout << fixed << setprecision(4);

    cout << per << " " << abs(area2)/2.0 << "\n";

}