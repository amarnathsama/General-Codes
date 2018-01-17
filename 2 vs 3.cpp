#include <iostream>

using namespace std;

void build(string &s, int lo, int hi, int *segtree, int pos)
{
	if(lo == hi)
	{
		segtree[pos] = (s[lo] == '1' ? 1 : 0);
		return;
	}
	
	int mid = (lo + hi)/2;
	
	build(s, lo, mid, segtree, 2 * pos + 1);
	build(s, mid + 1, hi, segtree, 2 * pos + 2);
	
	segtree[pos] = (segtree[2 * pos + 1] + segtree[2 * pos + 2]);
}

int query(int lo, int hi, int *segtree, int pos, int qlo, int qhi)
{
	if(qlo <= lo && qhi >= hi)
	{
		return segtree[pos] % 3;
	}
	
	if(qlo > hi || qhi < lo)
	{
		return 0;
	}
	
	int mid = (lo + hi)/2;
	
	int l = query(lo, mid, segtree, 2 * pos + 1, qlo, qhi);
	int r = query(mid + 1, hi, segtree, 2 * pos + 2, qlo, qhi);
	
	return (l + r) % 3;
}

int main()
{
	freopen("in.in", "r", stdin);
	
	int n;
	cin >> n;
	
	string s;
	cin >> s;
	
	int *segtree = new int [3 * n];
	build(s, 0, n - 1, segtree, 0);
	
	int q;
	cin >> q;
	
	while(q--)
	{
		int x, qlo, qhi;
		cin >> x >> qlo >> qhi;
		
		if(!x)
		{
			cout << query(0, n - 1, segtree, 0, qlo, qhi) << endl;
		}
	}
}
