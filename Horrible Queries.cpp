#include <bits/stdc++.h>

using namespace std;

struct node
{
  int sum;
  int lazy;
};

void build(int lo, int hi, node *segtree, int pos)
{
  if(lo == hi)
  {
    segtree[pos].sum = 0;
    segtree[pos].lazy = 0;
    
    return;
  }
  
  int mid = (lo + hi)/2;
  
  build(lo, mid, segtree, 2 * pos + 1);
  build(mid + 1, hi, segtree, 2 * pos + 2);
  
  segtree[pos].sum = 0;
  segtree[pos].lazy = 0;
}

void update(int lo, int hi, node *segtree, int pos, int v, int qlo, int qhi)
{
    if(qlo <= lo && qhi >= hi)
    {
    	segtree[pos].lazy += v;
        return;
    }
  
  	if(qlo > hi || qhi < lo)
	{
		return;
	}
	
	int mid = (lo + hi)/2;
	
	update(lo, mid, segtree, 2 * pos + 1, v, qlo, qhi);
	update(mid + 1, hi, segtree, 2 * pos + 2, v, qlo, qhi);
}

int query(int lo, int hi, node *segtree, int pos, int qlo, int qhi)
{
	if(qlo <= lo && qhi >= hi)
	{
		segtree[pos].sum += segtree[pos].lazy;
        
	    segtree[2 * pos + 1].lazy += segtree[pos].lazy;
	    segtree[2 * pos + 2].lazy += segtree[pos].lazy;
	    
	    segtree[pos].lazy = 0;
	    
	    return segtree[pos].sum;
	}
	
	if(qlo > hi || qhi < lo)
	{
		return 0;
	}
	
	int mid = (lo + hi)/2;
	
	int x = query(lo, mid, segtree, 2 * pos + 1, qlo, qhi);
	int y = query(mid + 1, hi, segtree, 2 * pos + 2, qlo, qhi);
	
	return x + y;
}

int main() 
{
  freopen("in.in", "r", stdin);
 
  int t;
  cin >> t;
  
  while(t--)
  {
    int n, c;
    cin >> n >> c;
      
    node *segtree = new node [4 * n];
    
    build(0, n - 1, segtree, 0);
    
    while(c--)
    {
      bool c;
      cin >> c;
      
      if(!c)
      {
        int p, q, v;
        cin >> p >> q >> v;
        
        update(0, n - 1, segtree, 0, v, p - 1, q - 1);
      }
      
      else
      {
        int p, q;
        cin >> p >> q;
        
        cout << query(0, n - 1, segtree, 0, p - 1, q - 1) << endl;
      }
    }
  }
}
