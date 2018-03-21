#include <iostream>
#include <vector>
#include <tr1/unordered_map>

using namespace std;

vector <string> v;
vector <char> name;
tr1 :: unordered_map <char, bool> e;

void solve(string s, int i, string ans)
{
	if(i == s.length())
	{
		cout << ans << " | ";
		return;
	}
	
	if(e[s[i]])
	{
		solve(s, i + 1, ans + s[i]);
		solve(s, i + 1, ans);
	}
	
	else
	{
		if(s[i] != '|' && s[i] != '~')
		solve(s, i + 1, ans + s[i]);
		
		else
		solve(s, i + 1, ans);
	}
}

int main()
{
	freopen("in.in", "r", stdin);
	
	cout << "Input Productions" << endl;
	string s;
	
	while(getline(cin, s), s != "0")
	{
		cout << s << endl;
		string st = "";
		
		for(int i = 2 ; i < s.length() ; i++)
		{
			st += s[i];
		}
		
		name.push_back(s[0]);
		v.push_back(st);
	}
	
	cout << endl << "Null Productions" << endl;
	
	while(getline(cin, s), s != "0")
	{
		cout << s << endl;
		e[s[0]] = 1;
	}
	
	cout << endl << "Productions" << endl;
	
	for(int i = 0 ; i < v.size() ; i++)
	{
		cout << name[i] << " -> ";
		solve(v[i], 0, "");
		cout << endl;
	}
}
