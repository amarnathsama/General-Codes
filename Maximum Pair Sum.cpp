#include <bits/stdc++.h>

using namespace std;

int *ar;

struct node
{
  int a, b;
};

void build(int *a, int lo, int hi, node *segtree, int pos)
{
  if(lo == hi)
  {
    segtree[pos].a = a[lo];
    segtree[pos].b = INT_MIN;
    
    return;
  }
  
  int mid = (lo + hi)/2;
  
  build(a, lo, mid, segtree, 2 * pos + 1);
  build(a, mid + 1, hi, segtree, 2 * pos + 2);
  
  node l = segtree[2 * pos + 1], r = segtree[2 * pos + 2];
  
  segtree[pos].a = max(l.a, r.a);
  segtree[pos].b = min(max(l.a, r.b), max(l.b, r.a));
}

node query(int lo, int hi, node *segtree, int pos, int qlo, int qhi)
{
	if(qlo <= lo && qhi >= hi)
	{		
		return segtree[pos];
	}
	
	if(qlo > hi || qhi < lo)
	{
		node ret;
		ret.a = INT_MIN, ret.b = INT_MIN;
		
		return ret;
	}
	
	int mid = (lo + hi)/2;
	
	node l = query(lo, mid, segtree, 2 * pos + 1, qlo, qhi);
	node r = query(mid + 1, hi, segtree, 2 * pos + 2, qlo, qhi);
	
	node ans;
	ans.a = max(l.a, r.a);
	ans.b = min(max(l.a, r.b), max(l.b, r.a));
	
	return ans;
}

void update(int *a, int lo, int hi, node *segtree, int pos, int ind, int val)
{
	if(lo == hi)
	{
		segtree[pos].a = val;
		a[ind] = val;
		
		return;
	}
	
	int mid = (lo + hi)/2;
	
	if(ind <= mid)
	{
		update(a, lo, mid, segtree, 2 * pos + 1, ind, val);
	}
	
	else
	{
		update(a, mid + 1, hi, segtree, 2 * pos + 2, ind, val);
	}
	
	node l = segtree[2 * pos + 1];
	node r = segtree[2 * pos + 2];
	
	node ans;
	ans.a = max(l.a, r.a);
	ans.b = min(max(l.a, r.b), max(l.b, r.a));
	
	segtree[pos] = ans;
}


int main() 
{
  freopen("in.in", "r", stdin);
	
  int n;
  cin >> n;
  
  ar = new int[n];
  
  for(int i = 0 ; i < n ; i++)
  {
    cin >> ar[i];
  }
  
  node *segtree = new node [n * 4];
  
  build(ar, 0, n - 1, segtree, 0);
  
  int q;
  cin >> q;
  
  while(q--)
  {
  	char ch;
  	int qlo, qhi;
  	
  	cin >> ch >> qlo >> qhi;
  	
  	if(ch == 'Q')
  	{
  		node ans = query(0, n - 1, segtree, 0, qlo - 1, qhi - 1);
  		cout << ans.a + ans.b << endl;
	}
	
	else
	{
		update(ar, 0, n - 1, segtree, 0, qlo - 1, qhi);
	}	
  }
}
