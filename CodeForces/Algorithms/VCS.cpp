#include<iostream>
#include<set>

using namespace std;

int main (){
	int T;
    cin >> T;
    while(T--) {
        set<int> A,B;
        int n,m,k, tmp;
        cin >> n >> m >> k;

        for(int i =0; i< m ; i++) {
            cin >> tmp;
            A.insert(tmp);
        }

        for(int i =0; i< k ; i++) {
            cin >> tmp;
            B.insert(tmp);
		}
		
        int tracked_and_ignored = 0;
        int untracked_and_unignored = 0;

        for(int i = 1 ; i<=n; i++) {
            //Implementacion mierdera, como mejoramos estas lineas \/
            if(A.count(i) != 0 && B.count(i) !=0) {
                tracked_and_ignored++;
            }
            if(A.count(i) == 0 && B.count(i) ==0) {
                untracked_and_unignored++;
            }
        }

        cout << tracked_and_ignored << " "<< untracked_and_unignored << endl;
    }

    return 0;
}
