#include <bits/stdc++.h>
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define int long long 

// max. subseq. , abertos n usados, fechados n usados
typedef array<int,3> infos;

const int MAX = 1e6+100;
const int oo = 2e9;

// "( " -> 0
// ") " -> 1

int n;
infos val[4*MAX];
int arr[MAX];
string s;

const infos neutral_value = {0,0,0};

infos merge(infos v1, infos v2){
	// abertos, fechados
	int bemf = min(v1[1], v2[2]);
	return {v1[0]+v2[0]+bemf, v1[1]+v2[1]-bemf, v1[2]+v2[2]-bemf};
}

void build_rec(int id, int tl, int tr){
	if(tl == tr){
		if(s[tl-1] == '(')
			val[id] = {0, 1, 0};
		else
			val[id] = {0, 0, 1};
		//val[id] = arr[tl];
	}
	else{
		int mid = (tl+tr)/2;
		build_rec(2*id, tl, mid);
		build_rec(2*id+1, mid+1, tr);
		val[id] = merge(val[2*id], val[2*id+1]);
	}
}

void build(){
	build_rec(1, 1, n);
}

infos query_rec(int id, int tl, int tr, int l, int r){
	if(tr < l or r < tl) return neutral_value;
	if(l <= tl and tr <= r) return val[id];
	int mid = (tl+tr)/2;
	infos q1 = query_rec(2*id, tl, mid, l, r);
	infos q2 = query_rec(2*id+1, mid+1, tr, l, r);
	return merge(q1, q2);
}

infos query(int l, int r){
	return query_rec(1, 1, n, l, r);
}

signed main(){
    oiee;

	//cin >> n;
	cin >> s;
	n = s.size();
	int q; cin >> q;
	build();

    while(q--){
        int l, r;
        cin >> l >> r;

		infos aux = query(l, r);
        cout << aux[0]*2 << "\n";
    }

}