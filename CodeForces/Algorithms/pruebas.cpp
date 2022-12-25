#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int a[200005];
map<int, long long>mp[20];
int main() {
	int n, k;
	cin >> n >> k;
	for( int i = 1; i < n+1; i++ ) {
		scanf("%I64d", &a[i]);
		long long x = a[i];
		for( int j = 1; j < 11; j++ ) {
			x = x * 10 % k;
			mp[j][x]++;
		}
	}
	
	for( int i = 1; i < n+1; i++ ) {
		cout << map[i] << " ";
	}
	cout << endl;
	
	return 0;
}
