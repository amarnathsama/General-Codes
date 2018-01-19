#include <bits/stdc++.h>

using namespace std;

struct node
{
  long sum;
  long lazy;
};

void build(long lo, long hi, node *segtree, long pos)
{
  if(lo == hi)
  {
    segtree[pos].sum = 0;
    segtree[pos].lazy = 0;
    
    return;
  }
  
  long mid = (lo + hi)/2;
  
  build(lo, mid, segtree, 2 * pos + 1);
  build(mid + 1, hi, segtree, 2 * pos + 2);
  
  segtree[pos].sum = 0;
  segtree[pos].lazy = 0;
}

void update(long lo, long hi, node *segtree, long pos, long v, long qlo, long qhi)
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
	
	long mid = (lo + hi)/2;
	
	update(lo, mid, segtree, 2 * pos + 1, v, qlo, qhi);
	update(mid + 1, hi, segtree, 2 * pos + 2, v, qlo, qhi);
}

long query(long lo, long hi, node *segtree, long pos, long qlo, long qhi)
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
	
	long mid = (lo + hi)/2;
	
	segtree[pos].sum += segtree[pos].lazy;    
	segtree[2 * pos + 1].lazy += segtree[pos].lazy;
	segtree[2 * pos + 2].lazy += segtree[pos].lazy;
	segtree[pos].lazy = 0;
	
	long x = query(lo, mid, segtree, 2 * pos + 1, qlo, qhi);
	long y = query(mid + 1, hi, segtree, 2 * pos + 2, qlo, qhi);
	
	return x + y;
}

int main() 
{
  freopen("in.in", "r", stdin);
 
  node *segtree = new node [4000001];
 
  long t;
  cin >> t;
  
  while(t--)
  {
    long n, c;
    cin >> n >> c;
      
    
    
   build(0, n - 1, segtree, 0);
    
    while(c--)
    {
      bool c;
      cin >> c;
      
      if(!c)
      {
        long p, q, v;
        cin >> p >> q >> v;
        
        update(0, n - 1, segtree, 0, v, p - 1, q - 1);
      }
      
      else
      {
        long p, q;
        cin >> p >> q;
        
        cout << query(0, n - 1, segtree, 0, p - 1, q - 1) << endl;
      }
      
      
    }
  }
}
