#include <bits/stdc++.h>

using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);

#define ll long long

int main(){
    oiee;

    string s, t; cin >> s >> t;
    ll s_size = s.size(), t_size = t.size();
    ll m[s_size+1][t_size+1];
    ll max_s = 0;

    // inicializa a linha da s com o vazio
    for(int i=0; i<= s_size; i++)
        m[i][0] = 0; 

    // inicializa a coluna da t com o vazio
    for(int i=0; i<= t_size; i++)
        m[0][i] = 0;

    for(int i=1; i<=s_size; i++){
        for(int j=1; j<=t_size; j++){

            // se os caracteres são iguais
            if(s[i-1] == t[j-1]){
                m[i][j] = m[i-1][j-1]+1;
                max_s = max(max_s, m[i][j]);
            }
            else
                m[i][j] = max(m[i-1][j], m[i][j-1]);

        }
    }
        

    // for(int i=0; i<=s_size; i++){
    //     for(int j=0; j<=t_size; j++){

    //         cout << m[i][j] << " ";

    //     }

    //     cout << "\n";
    // }

    // não tem substring comum
    if(max_s == 0)
        return 0;

    // reconstruir maior substring
    string resp;
    ll i = s_size, j = t_size;

    while(i>0 && j>0){
        if(s[i-1] == t[j-1]){
            resp += s[i-1];
            i--;
            j--;
        }

        else if(m[i][j-1] > m[i-1][j])
            j--;
        else
            i--;
    }

    reverse(resp.begin(), resp.end());


    cout << resp << "\n";
}