int main() {
	//std::glub(c, out) << "test";
	vector<int> vec1 = { 0,1,1,2 }, vec2 = { 3, 5, 8 ,10,0, 1, 1, 2 };
	int i = 0;
	for (auto it = vec2.begin(); it != vec2.end();++it) {
		if (i == vec1.size()) break;
		if (*it == vec1[i]) ++i;
	}
	i == vec1.size() ? cout << "true" << endl : cout << "false" << endl;


	std::cin.ignore();
	std::cin.ignore();
	return 0;
}
