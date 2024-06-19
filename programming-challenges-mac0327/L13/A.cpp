#include <bits/stdc++.h>
using namespace std;

#define oiee ios_base::sync_with_stdio(false); cin.tie(NULL);
#define int long long 

const int MAX = 1e6+100;
const int oo = 2e9;

int n;
int val[4*MAX];
int arr[MAX];
int qs[MAX];
array<int,3> ops[MAX];

const int neutral_value = 0;

int merge(int v1, int v2){
	return v1 + v2;
}

void build_rec(int id, int tl, int tr){
	if(tl == tr){
		val[id] = arr[tl];
	}
	else{
		int mid = (tl+tr)/2;
		build_rec(2*id, tl, mid);
		build_rec(2*id+1, mid+1, tr);
		//val[id] = merge(val[2*id], val[2*id+1]);
		val[id]=0;
	}
}

void build(){
	build_rec(1, 1, n);
}

void update_rec(int id, int tl, int tr, int l, int r, int d){
    //cout << "--->" << id << " " << tl << " " << tr << " " << l << " " << r << "\n"; 
	//if(tl == tr){
    //    //cout <<"A " << val[id] << "\n";
	//	val[id] += d;
    //    //cout <<"D " << val[id] << "\n";
	//}
	if(l == tl && r == tr)
		val[id] +=d;
	else{
		int mid = (tl+tr)/2;
		//cout << "mid " << mid << "\n";
		if(l <= mid)
			update_rec(2*id, tl, mid, l, min(r, mid), d);
		if(mid+1 <= r)
			update_rec(2*id+1, mid+1, tr, max(l, mid+1), r, d);

		//val[id] = merge(val[2*id], val[2*id+1]);
	}
}

void update(int l, int r, int d){
	update_rec(1, 1, n, l, r, d);
}

int query_rec(int id, int tl, int tr, int l, int r){
	if(tr < l or r < tl) return neutral_value;
	if(l <= tl and tr <= r) return val[id];
	int mid = (tl+tr)/2;
	int q1 = query_rec(2*id, tl, mid, l, r);
	int q2 = query_rec(2*id+1, mid+1, tr, l, r);
	return merge(q1, q2);
}

int query(int l, int r){
	return query_rec(1, 1, n, l, r);
}

void print_rec(int id, int tl, int tr, int sum){
	if(tl == tr)
		cout << val[id]+sum << " ";
	else{
		int mid = (tl+tr)/2;
		int sum_aux = sum + val[id];
		print_rec(2*id, tl, mid, sum_aux);
		print_rec(2*id+1, mid+1, tr, sum_aux);
	}
}


signed main(){
    oiee;

	cin >> n;
	int m, k; cin >> m >> k;
	int save_m = m;
	for(int i=1; i<=n; i++) cin >> arr[i];
	build();

	int c=0;
    while(save_m--){
        int l, r, d;
        cin >> l >> r >> d;
		ops[c++] = {l, r, d};
    }

	for(auto elem : qs) elem=0;

    while(k--){
        int x, y;
        cin >> x >> y;
		//x--; y--;

		//update(x,y);
		qs[x]++;
		if(y+1<=m) 
			qs[y+1]--;
    }

	for(int i=1; i<=m; i++){
		qs[i] += qs[i-1];
		//cout << "op " << i << " x " << qs[i] << "\n";
	}

	for(int i=1; i<=m; i++){
		if(qs[i]>0)
			update(ops[i-1][0], ops[i-1][1],ops[i-1][2]*qs[i]);
	}

	//for(int i=1; i<=n; i++)
	//	cout << query(i, i) << " ";
	print_rec(1,1,n,0);
    cout << "\n";
}

/*
4 3 1
1 2 3 4
1 2 1
2 3 2
3 4 4
1 2

resp 2 5 5 4

-----------------
4 1 1 
1 2 3 4 
1 1 1 
1 1 

resp 2 2 3 4

*/