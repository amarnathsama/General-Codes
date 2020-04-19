#include<iostream>
#include<map>
#include<vector>

using namespace std;
const int MX=100001;//check limits
vector<int> vis(MX);
vector<int>adj[MX];

void dfs(int s)
{
	vis[s] = 1;
	cout<<s<<" ";
	
	for(int i=0;i<adj[s].size();i++)
	{
		if(!vis[adj[s][i]])
		{
			dfs(adj[s][i]);
		}
	}
}

int main()
{
	int n, m;
	cin>>n>>m;
	
	for(int i=0;i<m;i++)
	{
		int x, y;
		cin>>x>>y;
		
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	cout<<"The Depth First Traversal will be:"<<endl;
	
	dfs(1);
}
