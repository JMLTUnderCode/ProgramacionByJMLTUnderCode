#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

int main (){
	int T;
    cin >> T;
    while(T--) {
            vector<int> as,bs;
            int n,m;
            cin >> n >> m;

            as.resize(n);
            bs.resize(m);
            
            for(int i =0; i< n ; i++) {
                cin >> as[i];
            }
            int total = 0;
            for(int i = 0; i < m; i++) {
                cin >> bs[i];
            }
            sort(as.begin(), as.end());
            sort(bs.begin(), bs.end());

            for(int i = 0; i < as.size(); i++) {
                vector<int>::iterator it = lower_bound(bs.begin(), bs.end(), as[i]);
                if( it != bs.end() && *it == as[i]) {
                    total++;
                }
            }

            cout << total << endl;
    }

    return 0;
}
