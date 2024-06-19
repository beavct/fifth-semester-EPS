#include <bits/stdc++.h>
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define int long long 

const int MAX = 1e6+100;
const int oo = 2e9;

typedef array<int, 2> guarda;

int N;
guarda val[4*MAX];
guarda arr[MAX];

const guarda neutral_value = {INT64_MIN, INT64_MAX};

guarda merge(guarda v1, guarda v2){
	//return v1 ^ v2;
	//cout << "merge " << v1[0] << " " << v1[1] << " " << v2[0] << " " << v2[1] << "\n";  
    return {max(v1[0], v2[0]), min(v1[1], v2[1])};
}

void build_rec(int id, int tl, int tr){
	if(tl == tr){
		val[id][0] = arr[tl][0];
		val[id][1] = arr[tl][1];
	}
	else{
		int mid = (tl+tr)/2;
		build_rec(2*id, tl, mid);
		build_rec(2*id+1, mid+1, tr);
		val[id] = merge(val[2*id], val[2*id+1]);
	}
}

void build(){
	build_rec(1, 1, N);
}

void update_rec(int id, int tl, int tr, int pos, guarda x){
	if(tl == tr){
		val[id][0] = x[0];
        val[id][1] = x[1];
	}
	else{
		int mid = (tl+tr)/2;
		if(pos <= mid)
			update_rec(2*id, tl, mid, pos, x);
		else
			update_rec(2*id+1, mid+1, tr, pos, x);
		val[id] = merge(val[2*id], val[2*id+1]);
	}
}

void update(int pos, guarda x){
	update_rec(1, 1, N, pos, x);
}

guarda query_rec(int id, int tl, int tr, int l, int r){
	if(tr < l or r < tl) return neutral_value;
	if(l <= tl and tr <= r) return val[id];
	int mid = (tl+tr)/2;
	guarda q1 = query_rec(2*id, tl, mid, l, r);
	guarda q2 = query_rec(2*id+1, mid+1, tr, l, r);
	return merge(q1, q2);
}

guarda query(int l, int r){
	return query_rec(1, 1, N, l, r);
}

signed main(){
    oiee;

	cin >> N;
	int Q; cin >> Q;
	for(int i=1; i<=N; i++) cin >> arr[i][0] >> arr[i][1];
	build();

    while(Q--){
        string op;
        cin >> op;

        
        if(op == "?"){
            int l, r;
			cin  >> l >> r; 
            guarda aux = query(l, r); 
            //cout << aux[0] << " " << aux[1] << "\n";
            cout << max(aux[1]-aux[0]+1, (int)0) << "\n";
        }
        else if(op == "C"){
            int i, l, r;
            cin >> i >> l >> r;
            update(i, {l,r});
        }

    }

}