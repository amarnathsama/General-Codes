#include <iostream>
#include <vector>

using namespace std;

int n, w, k;

void solve(int i, int q)
{
  if(i == n)
  return;

  int lost = -1, cur_win = 0;

  for(int j = i ; j <= i + w - 1 ; j++)
  {
    cur_win ++;

    if(j > n)
    return;

    cout << j << " ";

    q++;

    if(q == k)
    {

      lost = j;
    }
  }

  if(lost == -1)
  {
    solve(i + w, q);
  }

  else
  {
    solve(lost, cur_win - 1);
  }

}

int main()
{
  freopen("in.in", "r", stdin);

  cout << "Frame Size" << endl;
  cin >> n;
  cout << n << endl;

  cout << endl << "Window Size" << endl;
  cin >> w;
  cout << w << endl;

  cout << endl << "Lost Packet" << endl;
  cin >> k;
  cout << k << endl << endl;

  solve(1, 0);
  cout << endl;

}
