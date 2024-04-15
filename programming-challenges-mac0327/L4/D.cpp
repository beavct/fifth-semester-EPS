#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    ll v; cin >> v;
    vector<ll> a(9);

    for(ll i=0; i<9; i++)
        cin >> a[i];

    

    vector<string> movs(v+1);
    movs[0]="";
    vector<ll> q_movs(v+1);
    q_movs[0]=0;    

    // itera pela habilidade
    for(ll i=1; i<=v; i++){
        q_movs[0]=0;
        // itera pelos movimentos
        for(ll j=0; j<9; j++){
            // da pra fazer o movimento
            if(a[j]<=i){
                if(q_movs[i]<=q_movs[i-a[j]]+1){
                    q_movs[i]=q_movs[i-a[j]]+1;
                    movs[i]=(j+1)+'0';
                }
            }
        }

    }

    if(q_movs[v]==0)
            cout << "-1\n";
    // reconstruir a string de saida
    else{
        //cout << movs[v] <<" " << q_movs[v] << "\n";
        ll aux=v;
        ll q=q_movs[v];
        string resp="";
        while(q>0){
            ll dig=(ll)movs[aux][0]-'0';
            resp+=movs[aux];
            aux=aux-a[dig-1];
            q--;
        }
        cout << resp << "\n";
    }
}