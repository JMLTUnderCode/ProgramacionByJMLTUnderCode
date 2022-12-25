#include<iostream>
#include<set>
using namespace std;

int main (){
	int T;
    cin >> T;
    while(T--) {
        set<int> a;
        int bs,n,m;
        cin >> n >> m;

        for(int i =0; i< n ; i++) {
            int tmp;
            cin >>tmp;
            a.insert(tmp);
        }
        int total = 0;
        for(int i = 0; i < m; i++) {
            cin >> bs;
        	if(a.count(bs) != 0) {
                total++;
            }
        }
        
		cout << total << endl;
    }

    return 0;
}
