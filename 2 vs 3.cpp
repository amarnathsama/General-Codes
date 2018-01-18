#include <iostream>

using namespace std;

int pow(int x, int y)
{
  int res = 1;
  
  while(y)
  {
    if(y & 1)
      res = (res * x) % 3;
      
	x = (x * x) % 3;
    y >>= 1;
  }
  
  return res;
}

int combine(int a, int b, int la, int lb)
{
	int ans;
	
	if(la == 0 || a == -1)
	return b % 3;
	
	if(lb == 0 || b == -1)
	return a % 3;
	
	ans = ((a * pow(2, lb)) % 3 + b % 3) % 3;
	
	return ans;
}


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
	
	segtree[pos] = combine(segtree[2 * pos + 1], segtree[2 * pos + 2], mid - lo + 1, hi - mid);
}

int query(int lo, int hi, int *segtree, int pos, int qlo, int qhi)
{
	if(qlo <= lo && qhi >= hi)
	{
		return segtree[pos];
	}
	
	if(qlo > hi || qhi < lo)
	{		
		return -1;
	}
	
	int mid = (lo + hi)/2;
	
	int l = query(lo, mid, segtree, 2 * pos + 1, qlo, qhi);
	int r = query(mid + 1, hi, segtree, 2 * pos + 2, qlo, qhi);
	
	return combine(l, r, mid - lo + 1, hi - mid);
}

void update(string a, int lo, int hi, int *segtree, int pos, int ind)
{
	if(lo == hi)
	{
		a[lo] = '1';
		segtree[pos] = 1;
		
		return;
	}
	
	int mid = (lo + hi)/2;
	
	if(mid <= ind)
	{
		update(a, lo, mid, segtree, 2 * pos + 1, ind);
	}
	
	else
	{
		update(a, mid + 1, hi, segtree, 2 * pos + 2, ind);
	}
	
	segtree[pos] = combine(segtree[2 * pos + 1], segtree[2 * pos + 2], mid - lo + 1, hi - mid);
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
		cin >> x;
		
		if(!x)
		{
			cin >> qlo >> qhi;
			cout << query(0, n - 1, segtree, 0, qlo, qhi) % 3 << endl;
		}
		
		else
		{
			cin >> qlo;
			update(s, 0, n - 1, segtree, 0, qlo);
		}
	}
}
