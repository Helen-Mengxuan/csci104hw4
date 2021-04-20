#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename F>
void forEach(vector<int>& values, F&& func) {
	// TO DO: change to range based loop 
	for( auto& idx : values ) { 
		func(idx);
	}
}

// TO DO: turn into lambda function
/*void square(int& number) {
  number *= number;
}
*/

void print(const vector<int>& values) {
	// TO DO: change to range based loop 
	for(const auto& idx : values) { 
		cout << idx << " ";
	}
	cout << endl;
}

int main() {
	vector<int> values = {4, 8, 15, 16, 23, 42};
	cout << "BEFORE:" << endl;
	print(values);

	//lambda function here
	auto square = [](int& number){ number *= number; };

	forEach(values, square);

	cout << "AFTER:" << endl;
	print(values);
	
}