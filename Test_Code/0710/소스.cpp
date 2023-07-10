#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int facto(int n)
{
	//int ret = 1;
	//for (int i = 1; i <= n; i++)
	//{
	//	ret *= i;
	//}
	//return ret;

	if (n == 0 || n == 1) return 1;
	return n * facto(n - 1);
}
int fibo(int n)
{
	if (n == 0 || n == 1)
		return n;

	return fibo(n - 1) + fibo(n - 2);
}
void PrintV(vector<int>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}


vector<int> v;
void makePermutation(int n, int r, int depth)
{
	//cout << n << " : " << r << " : " << depth << endl;
	if (r == depth)
	{
		PrintV(v);
		return;
	}
	for (int i = depth; i < n; i++)
	{
		swap(v[i], v[depth]);
		makePermutation(n, r, depth + 1);
		swap(v[i], v[depth]);
	}
	return;
}

int main()
{
	//cout << facto(5) << endl;
	

	/*int a[] = { 1,2,3 };
	do {
		for (int i : a) cout << i << " ";
		cout << endl;
	} while (next_permutation(&a[0], &a[0] + 3));*/

	//vector<int> a = { 2,1,3 };
	//sort(a.begin(), a.end());
	//do
	//{
	//	for (auto i : a) cout << i << " ";
	//	cout << '\n';
	//} while (next_permutation(a.begin(), a.end()));

	//vector<int> a = { 2,1,3,100,200 };
	//sort(a.begin(), a.end());
	//do
	//{
	//	for (int i = 0; i < 2; i++)
	//	{
	//		cout << a[i] << " ";
	//	}
	//	cout << endl;
	//} while (next_permutation(a.begin(), a.end()));

	for (int i = 1; i <= 4; i++) v.push_back(i);
	makePermutation(4, 3, 0);

	//cout << facto(4) << endl;

	return 0;
}