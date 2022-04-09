vector<int> getPrimes() {
	vector<int> result{};
	result.push_back(2);

	for(int i = 3; i != 100100; ++i) {
		bool found = true;
		for (int v : result) {
			if (i%v==0) {
				found=false;
				break;
			}
		}

		if (found) {
			//cout<<i<<" ";
			result.push_back(i);
		}
	}

	return result;
}