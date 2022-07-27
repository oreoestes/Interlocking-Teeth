#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//function to remove spaces from the input text
string removeSpaces(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

int main() {
	vector<int> x{};
	vector<int> y{};

	string filename = "input.txt";
	string line0, line1, line2;

	fstream input_file(filename);

	if (!input_file.is_open()) {
		cout << "Could not open the file: " << filename << endl;
		return 0;
	}

	//get each individual line, line 0 is unneeded due to how the program handles uneven sizes for the arrays
	getline(input_file, line0);
	getline(input_file, line1);
	getline(input_file, line2);

	//load the integers from the input arrays into the vectors
	for (char c : removeSpaces(line1)) {
		y.push_back(c - '0');
	}

	for (char c : removeSpaces(line2)) {
		x.push_back(c - '0');
	}

	
	//size of vectors
	int n = x.size();
	int m = y.size();

	//calculate max height from sum of last and first array elements
	int possMin1 = x.front() + y.front();
	int possMin2 = x.back() + y.back();
	int trueMin;

	if (possMin1 > possMin2)
		trueMin = possMin1;
	else
		trueMin = possMin2;

	//check if input is empty array
	ofstream output_file("output.txt");
	if (n == 0) {
		output_file << trueMin << endl;

		for (auto i : y) {
			output_file << i << ' ';
		}

		output_file << endl;
		return 0;
	}
	else if (m == 0) {
		output_file << trueMin << endl;

		for (auto i : x) {
			output_file << i << ' ';
		}

		output_file << endl;
		return 0;
	}
	else if (n == 0 && m == 0)
		return 0;

	//for loop which iterates through the vectors and inserts any required duplicates while keeping the sums below the optimized height
	for (int i = 1; i < n; i++) {
		n = x.size();
		m = y.size();

		if (x.at(i) + y.at(i) <= trueMin){}
	
		else {
			if (x.at(i) + y.at(i + 1) <= trueMin && x.at(i - 1) + y.at(i) <= trueMin) {
				x.insert(x.begin() + i, x.at(i - 1));
			}
			else if (x.at(i) + y.at(i - 1) <= trueMin && x.at(i + 1) + y.at(i) <= trueMin) {
				y.insert(y.begin() + i, y.at(i - 1));
			}
			else if (y.at(i) + x.at(i + 1) <= trueMin && y.at(i - 1) + x.at(i) <= trueMin) {
				y.insert(y.begin() + i, y.at(i - 1));
			}
			else if (y.at(i) + y.at(i - 1) <= trueMin && y.at(i + 1) + y.at(i) <= trueMin) {
				y.insert(y.begin() + i, y.at(i - 1));
			}
		}

		if (i == x.size() - 2) {
			if (m < n) {
				y.insert(y.begin() + i, y.back());
			}
			else if (n < m) {
				x.insert(x.begin() + i, x.back());
			}
		}
	}

	//create and write to output file

	output_file << trueMin << endl;

	for (auto i : x) {
		output_file << i << ' ';
	}

	output_file << endl;

	for (auto i : y) {
		output_file << i << ' ';
	}

	output_file.close();
	return 0;
}
