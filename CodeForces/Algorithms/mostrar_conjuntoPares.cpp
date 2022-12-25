void draw_set(set<pair<int,int>> N) {
	
	set<pair<int,int>> :: size_type len = N.size();
	
	cout << "{ ";
	int k = 1;
	for ( pair<int,int> i : N ) {
		if ( k == len ) {
			cout << "{" << i.first << ", " << i.second << "}";
		} else {
			cout << "{" << i.first << ", " << i.second << "}, ";
		}
		k++;
	}
	
	cout << " }"<< endl;
}
