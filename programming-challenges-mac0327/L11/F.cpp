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
    ll n; cin >> n;

    // canto inferior esquerdo e canto superior direito
    point IE(0,0), SD(0,0);

    for(ll i=0; i<n; i++){
        char aux;

        cin >> aux;

        if(aux == 'p'){
            ll aux1, aux2;

            cin >> aux1 >> aux2;

            if(n==1){
                SD.x = aux1;
                SD.y = aux2;
                IE=SD;
            }
            else{
                // superior direito
                if(aux1 > SD.x)
                    SD.x = aux1;
                if(aux2 > SD.y)
                    SD.y = aux2;


                // inferior esquerdo
                if(aux1 < IE.x)
                    IE.x = aux1;
                if(aux2 < IE.y)
                    IE.y = aux2;

            }

        }
        else if(aux == 'c'){
            ll aux1, aux2, r;

            cin >> aux1 >> aux2 >> r;

            // superior direito
            if(aux1+r > SD.x)
                SD.x = aux1+r;
            if(aux2+r > SD.y)
                SD.y = aux2+r;

            // inferior esquerdo
            if(aux1-r < IE.x)
                IE.x = aux1-r;
            if(aux2-r < IE.y)
                IE.y = aux2-r;

        }
        else{
            ll aux1, aux2, aux3, aux4;

            cin >> aux1 >> aux2 >> aux3 >> aux4;

            // superior direito
            if(aux1 > SD.x)
                SD.x = aux1;
            if(aux2 > SD.y)
                SD.y = aux2;

            // inferior esquerdo
            if(aux1 < IE.x)
                IE.x = aux1;
            if(aux2 < IE.y)
                IE.y = aux2;


            // superior direito
            if(aux3 > SD.x)
                SD.x = aux3;
            if(aux4 > SD.y)
                SD.y = aux4;

            // inferior esquerdo
            if(aux3 < IE.x)
                IE.x = aux3;
            if(aux4 < IE.y)
                IE.y = aux4;

        }

    }

    cout << IE.x << " " << IE.y << " " << SD.x << " " << SD.y << "\n";
}

int main(){
    oiee;

    ll t;
    cin >> t;

    for(ll i=0; i<t; i++)
        solve();

}