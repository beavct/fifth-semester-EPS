#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int is_prime(int n){
	if(n == 1 || n==0) 
        return 0;

	//bool flg = true;

	for(int i=2; i*i<=n; i++)
		if(n%i == 0) 
            return 0;
	return 1;
}


int teste(ll n){
    if(n==1 || is_prime(n) || sqrt(n) == (int)sqrt(n)){
        return 0;
    }

    ll cont=0;
    if(n%2==0){
        cont++;
        while(n%2==0){
            n/=2;
        }
    }
    
    if(is_prime(n))
        cont++;
    else if(n%2==1){
        for(ll i=3; i<=n/2;i++){
            if(n%i==0){
                //cout << "i= " << i << "\n";
                if(is_prime(i))
                    cont++;
            }
        }
    }

        
    if(cont==2)
        return 1;
    return 0;
}

void crivo(int n, vector<int>& primes){
	vector<bool> is_composite(n+1, false);
	for(int i=2; i<=n; i++){
		if(not is_composite[i]){
			primes.push_back(i);
			for(int j=i*i; j<=n; j+=i)
				is_composite[j] = true;
		}
	}
}

int solve(ll n){
    vector<int> primes;

    if(n==1)
        return 0;

    ll cont=0;

    if(n%2==0){
        cont++;
        while(n%2==0){
            n/=2;
        }        
    }

    crivo(n, primes);

    for(ll i=cont; i<(ll)primes.size(); i++){
        if(n%primes[i]==0)
            cont++;
    }

    return cont==2;
}

int main(){
    oiee;

    ll n; cin >> n;
    ll resp=0;

    for(ll i=1; i<=n; i++){
        //if(solve(i)){
        //    resp++;
        //    cout << "i= " << i << " SIM\n";
        //}
        
        resp+=solve(i);
    }

    cout << resp << "\n";
}