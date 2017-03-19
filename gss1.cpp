#include<iostream>
#include<map>

using namespace std;

struct node
{
	long best, lsum, rsum, total;
};

map<long, node>segtree;
map<long, long>a;

void pg(long pos)
{
	segtree[pos].total = segtree[2*pos+1].total + segtree[2*pos+2].total;
	segtree[pos].lsum = max(segtree[2*pos + 1].lsum, segtree[2*pos + 1].total + segtree[2*pos+2].lsum);
	segtree[pos].rsum = max(segtree[2*pos + 2].rsum, segtree[2*pos + 2].total + segtree[2*pos+1].rsum);
	segtree[pos].best = max(max(segtree[2*pos+1].best, segtree[2*pos+2].best), segtree[2*pos+1].rsum + segtree[2*pos+2].lsum);
}

void construct(long lo, long hi, long pos)
{
	if(lo == hi)
	{
		segtree[pos].best = a[lo];
		segtree[pos].lsum = a[lo];
		segtree[pos].rsum = a[lo];
		segtree[pos].total = a[lo];
		
		return;
	}
	
	long mid = (lo + hi)/2;
	
	construct(lo, mid, 2*pos+1);
	construct(mid+1, hi, 2*pos+2);
	
	pg(pos);
}

long query(long qlo, long qhi, long lo, long hi, long pos)
{
	if(qlo>hi || qhi<lo)
	{
		return 0;
	}
	
	if(qlo<=lo && qhi>=hi)
	{
		return segtree[pos].best;
	}
	
	long mid = (lo + hi)/2;
	
	return max(query(qlo, qhi, lo, mid, 2*pos+1), query(qlo, qhi, mid+1, hi, 2*pos+2));
}

int main()
{

	//freopen("C:\\Users\\Shraeyas\\Documents\\pg\\pr_ag\\prag_gss1.txt", "r", stdin);
	
	long n;
	scanf("%ld", &n);
	
	for(long i=0;i<n;i++)
	{
		scanf("%ld", &a[i]);
	}
	
	construct(0, n-1, 0);
	
	long q;
	scanf("%ld", &q);
	
	while(q--)
	{
		long x,y;
		scanf("%ld %ld", &x, &y);
		x--, y--;
		
		printf("%ld\n",query(x, y, 0, n-1, 0));
	}
}

