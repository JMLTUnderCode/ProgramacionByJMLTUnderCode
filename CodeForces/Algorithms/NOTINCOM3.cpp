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
            for(int i = 0; i < m; i++) {
                    cin >> bs[i];
            }
            sort(as.begin(), as.end());
            sort(bs.begin(), bs.end());

            int j = 0;
            int total = 0;
            for(int i = 0; i < as.size(); i++) {
                    while(j < m && bs[j] < as[i]) {
                            j++;
                    }

                    if(j < m && bs[j] == as[i])
                            total++;
            }

            cout << total << endl;
    }

    return 0;
}
