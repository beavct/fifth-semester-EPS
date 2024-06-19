#include <bits/stdc++.h>
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define int long long 

const int MAX = 1e6+100;
const int oo = 2e9;

// min, mdc, quant
typedef array<int, 3> form;

int n;
form val[4*MAX];
int arr[MAX];

const form neutral_value = {INT64_MAX, 0, 0};

form merge(form v1, form v2){
	int g = __gcd(v1[1], v2[1]);
    //int aux_m=min(v1[0], v2[0]);
    if(v1[0] == v2[0])
	    return {v1[0], g, v1[2]+v2[2]};
	else if(v1[0] < v2[0])
		return {v1[0], g, v1[2]};
		//return {aux_m, g, min(v1[2], v2[2])};
	else
		return {v2[0], g, v2[2]};


}

void build_rec(int id, int tl, int tr){
	if(tl == tr){
		val[id][0] = val[id][1] = arr[tl];
		val[id][2] = 1;
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

form query_rec(int id, int tl, int tr, int l, int r){
	if(tr < l or r < tl) return neutral_value;
	if(l <= tl and tr <= r) return val[id];
	int mid = (tl+tr)/2;
	form q1 = query_rec(2*id, tl, mid, l, r);
	form q2 = query_rec(2*id+1, mid+1, tr, l, r);
	return merge(q1, q2);
}

form query(int l, int r){
	return query_rec(1, 1, n, l, r);
}

signed main(){
    oiee;

	cin >> n;
	for(int i=1; i<=n; i++) cin >> arr[i];
	int q; cin >> q;
	build();

    while(q--){
        int l, r;
        cin >> l >> r;
        form aux = query(l,r);
        if(aux[0] == aux[1])
            cout << r-l+1-aux[2] << "\n";
        else 
            cout << r-l+1 << "\n";
    }

}