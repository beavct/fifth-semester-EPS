#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

ll calc_custo(vector<ll> &custos_base, ll a_j, ll p){
    return custos_base[a_j]+a_j*p;
}

int main(){
    oiee;

    ll n, k; cin >> n >> k;

    vector<ll> custos_base(n+1, 0);
    for(ll i=1; i<=n; i++)
        cin >> custos_base[i];

    ll left=0, right=n;
    ll c_atu=0, p=n, C_resp=0;
    ll p_resp=0;

    while(left <= right){
        ll mid = (left+right)/2;
        //cout << "mid: " << mid << endl; 

        ll C_aux=0, p_aux=0;
        vector<ll> aux_custos(n+1);

        for(ll i=1; i<=n; i++)
            aux_custos[i] = calc_custo(custos_base, i, mid);

        // precisa deixar o sort
        sort(aux_custos.begin(), aux_custos.end()); 


        //cout << "p_resp: " << p_resp << endl;
        //for(auto elem : aux_custos)
        //    cout << elem << " ";
        //cout << endl;

        ll i=1;
        // enquanto não ultrapassa o orçamento e a quantidade de itens <=mid
        while(C_aux+aux_custos[i] <=k && p_aux<mid){
            C_aux+=aux_custos[i];
            p_aux++;
            i++;
        }

        
        if(p_aux==mid){
            //cout << "entrou2" << endl;
            left=mid+1;
            //left++;
            p_resp=mid;
            //p_resp=mid;
            C_resp=C_aux;
            //cout << "p_resp: " << p_resp << " C_resp: " << C_resp << endl;

        }
        else{
            //cout << "entrou3" << endl;
            right=mid-1;
            //right--;
        }            

    }
    cout << p_resp << " " << C_resp << endl;
    
}

/////////////////////////////////////////////////////////////////    
   
    //while(p > 0){
//
    //    ll C_aux=0, p_aux=0;
    //    vector<ll> aux_custos(n+1);
//
    //    for(ll i=1; i<=n; i++)
    //        aux_custos[i] = calc_custo(custos_base, i, p);
    //    
    //    sort(aux_custos.begin(), aux_custos.end()); 
//
    //    ll i=1;
    //    while(C_aux+aux_custos[i] <=k){
    //        C_aux+=aux_custos[i];
    //        p_aux++;
    //        i++;
    //    }
//
    //    //cout << "P: " << p << " CUSTO: " << C_aux << endl;
//
    //    if(p_aux == p){
    //        C_resp = C_aux;
    //        break;
    //    }
    //    else{
    //        p--;
    //    }
    //}
    //cout << p << " " << C_resp << endl;

//}