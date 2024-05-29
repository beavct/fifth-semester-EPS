#include <bits/stdc++.h>
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
const int oo = 1e9;

vector<vector<int>> dists(8, vector<int>(8, oo));
vector<vector<bool>> mark(8, vector<bool>(8, false));
vector<string> ans_r;


string aux[3][3] = {{"LU", "U", "RU"},
                    {"L", "C", "R"},
                    {"LD", "D", "RD"}};

// invertida
string mvs[3][3] = {{"RD", "D", "LD"},
                    {"R", "C", "L"},
                    {"RU", "U", "LU"}};

pair<int, int> orig, dest;

void bfs(pair<int, int> src) {
    queue<pair<int, int>> q;
    q.push(src);

    //mark[src.first][src.second] = true;

    //return;

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();

        mark[cur.first][cur.second]=true;

        // 8 combs (- cur)    
        int di[] = {-1, 0, 1};
        int dj[] = {-1, 0, 1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // posição atual (src)
                if (i == 1 && j == 1)
                    continue;

                int ni = cur.first + di[i];
                int nj = cur.second + dj[j];

                // fora da matriz
                if (!((ni >= 0 && ni < 8) && (nj >= 0 && nj < 8)))
                    continue;


                //if (dists[ni][nj] == oo) {
                //    q.push({ni, nj});
                //    dists[ni][nj] = dists[cur.first][cur.second] + 1;
                //    parent[ni][nj] = cur;
                //}

                // quando não é o nosso dest
                //if(!(ni == dest.first && nj == dest.second)){
                //    dists[ni][nj] = min(dists[ni][nj], dists[cur.first][cur.second] + 1);
//
                //    if(!mark[ni][nj])
                //        q.push({ni,nj});
                //}
                //else{
                //    dists[ni][nj] = min(dists[ni][nj], dists[cur.first][cur.second] + 1);
                //}

                dists[ni][nj] = min(dists[ni][nj], dists[cur.first][cur.second] + 1);
                if(!mark[ni][nj])
                    q.push({ni,nj});

            }
        }
    }
}

void build_ans(){
    pair<int,int> cur = dest;

    int di[] = {-1, 0, 1};
    int dj[] = {-1, 0, 1};

    while(cur != orig){

        pair<int, int> mov;
        int cost = oo;

        //cout << "oie\n";
        for(ll i=0; i<3;i++){
            for(ll j=0; j<3;j++){
                int ni = cur.first + di[i];
                int nj = cur.second + dj[j];


                //cout << "ni = " << ni << " nj = " << nj << "\n";


                // fora da matriz
                if (!((ni >= 0 && ni < 8) && (nj >= 0 && nj < 8)))
                    continue;


                if(dists[ni][nj] < cost){
                    //cout << dists[ni][nj] << "\n"; 
                    mov = {di[i], dj[j]};
                    cost = dists[ni][nj];
                }

            }
        }     
        //sleep(1);

        ans_r.push_back(mvs[mov.first+1][mov.second+1]);

        //cout << "deu push no " << mvs[mov.first+1][mov.second+1] << "\n";
        cur = {cur.first + mov.first, cur.second + mov.second};

        //cout << "cur agr eh " << cur.first << " " << cur.second << "\n"; 
    }
}

int main() {
    oiee;

    string s, t;
    cin >> s >> t;

    orig.second = s[0] - 'a'; // coluna
    orig.first = '8' - s[1]; // linha 
    dest.second = t[0] - 'a'; // coluna
    dest.first = '8' - t[1]; // linha 

    dists[orig.first][orig.second] = 0;
    dists[dest.first][dest.second] = oo; 

    bfs(orig);

    //for(auto linha : dists){
    //    for(auto elem : linha)
    //        cout << elem << "    ";
    //    cout << "\n";
    //}
    //cout << "\n";

    build_ans();

    cout << ans_r.size() << "\n";
    for(ll i=(ll)ans_r.size()-1; i>=0; i--)
        cout << ans_r[i] << "\n";

    return 0;
}
