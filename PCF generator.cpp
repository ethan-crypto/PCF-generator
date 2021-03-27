#include <iostream>
#include <vector>
using namespace ::std;

// This program lists all the positive composite numbers up to and including N, where N is a positive interger greater than 3. 
// This list is arranged from the numbers with the most amount of divisors to the least.
// Each composite number 
void print_factors(vector<int> factors) {
	for (int i = factors.size() - 1; i >= 0; i--) {
		if (i == 0) {
			cout << factors[i];
		}
		else {
			cout << factors[i] << ", ";
		}

	}
	cout << endl;
}
void sort_factors(vector<int> factors) {
	int r = 0;
	while (r < factors.size()) {
		int s_c = factors[r];
		vector<int> smallest_c{ r };
		for (int i = r + 1; i < factors.size(); i++) {
			if (factors[i] < s_c) {
				s_c = factors[i];
				smallest_c.clear();
				smallest_c.push_back(i);
			}
			else if (factors[i] == s_c) {
				smallest_c.push_back(i);
			}
		}
		for (int i = 0; i < smallest_c.size(); i++) {
			int l = smallest_c[i];
			int shift = factors[l];
			factors.erase(factors.begin() + l);
			factors.insert(factors.begin(), shift);
		}
		r += smallest_c.size();
	}
	print_factors(factors);
}

void factors(vector<vector<int>> list, vector<vector<int>> pf_powers, vector<int> primes, int C) {
	vector<vector<int>> prime_power; 
	vector<int> factors = { 1 };
	size_t d = 0;
	for (int i = 0; i < list.size(); i++) {
		if (C == list[i][0]) {
			for (int j = 0; j < pf_powers[i].size(); j++) {
				if (pf_powers[i][j] > 0) {
					prime_power.push_back({ primes[j], pf_powers[i][j] });
				}
			}
			for (int j = 0; j < prime_power.size(); j++) {
				for (int k = 1; k <= prime_power[j][1]; k++) {
					for (int l = 0; l <= d; l++) {
						int exp = 1; 
						int p_raised = prime_power[j][0];
						while (exp < k) {
							p_raised *= prime_power[j][0];
							exp++;
						}
						int factor = factors[l] * p_raised; 
						factors.push_back(factor);
					}
				}
				d = factors.size() - 1;
			}
			sort_factors(factors);
			break;
		}
		else if (i == list.size() - 1) {
			cout << "Error. Invalid input";
		}
	}
}
void print_primes(vector<int> vector, int choice) {
	if (choice == 0) {
		for (int x : vector) {
			cout << x << "\n";
		}
	}
	else if (choice == 1) {
		for (int i = (vector.size() - 1); i >= 0; i--) {
			cout << vector[i] << "\n";
		}
	}
	else {
		cout << "Error. Invalid input" << endl;
	}

}
void print_composites(vector<vector<int>> list, int choice3) {
	if (choice3 == 1) {
		for (int i = 0; i < list.size(); i++) {
			cout << list[i][0] << ", " << list[i][1] << endl;
		}
	}
	else if (choice3 == 0) {
		for (int i = (list.size() -1); i >= 0; i--) {
			cout << list[i][0] << ", " << list[i][1] << endl;
		}
	}
	else {
		cout << "Error. Invalid input" << endl;
	}
}
void sort_by_divisor_count(vector<vector<int>> list, int choice3) {

	int r = 0;
	while (r < list.size()) {
		int s_c = list[r][1];
		vector<int> smallest_c{ r };
		for (int i = r+1; i < list.size(); i++) {
			if (list[i][1] < s_c) {
				s_c = list[i][1]; 
				smallest_c.clear();
				smallest_c.push_back(i);
			}
			else if (list[i][1] == s_c) {
				smallest_c.push_back(i); 
			}
		}
		for (int i = 0; i < smallest_c.size(); i++) {
			int l = smallest_c[i];
			vector<int> shift = list[l]; 
			list.erase(list.begin() + l); 
			list.insert(list.begin(), shift);
		}
		r += smallest_c.size();
	}
	print_composites(list, choice3);
}
int main() {
	int N = 0;
	int choice1 = 0;
	int choice2 = 2;
	int choice3 = 0;
	int C = 0;
	cout << "Do you want a list of composite or prime numbers?\n0. Composite\n1. Prime\n";
	cin >> choice1;
	cout << "What positive integer value greater than 3 do you want to use to generate a list of all the primes or composites less than it?\n";
	cin >> N; 
	if (choice1 == 0) {
		cout << "Do you want to sort this list according to the amount of divisors each composite has or by their actual value?\n0. Divisors\n1. Actual value\n";
		cin >> choice2;
	}
	cout << "Do you want to sort from least to greatest or greatest to least?\n0. L to G\n1. G to L\n";
	cin >> choice3; 
	vector<int> primes{2};
	vector<vector<int>> list;
	vector<int> composite;
	vector<vector<int>> pf_powers;
	vector<int> divisors;
	for (int i = 3; i < N; i++) { 
		for (int j = 0; j < primes.size(); j++) {
			if (i % primes[j] == 0) {
				composite.push_back(i);
				pf_powers.push_back(vector<int>());
				for (int k = 0; k < primes.size(); k++) {
					if (i % primes[k] != 0) {
						pf_powers[composite.size() - 1].push_back(0);
					}
					else {
						int l = i/primes[k];
						int a = 1;
						while (l % primes[k] == 0) {
							l /= primes[k];
							a++;
						}
						pf_powers[composite.size() - 1].push_back(a);
					}
				}
				break;
			}
			else if (j == primes.size() - 1) {
				primes.push_back(i);
				break;
			}
		}
	}
	for (int i = 0; i < pf_powers.size(); i++) {
		int d = 1;
		for (int j = 0; j < pf_powers[i].size(); j++) {
			d *= (pf_powers[i][j] + 1);
		}
		divisors.push_back(d);
		list.push_back({ composite[i], divisors[i] });
	}
	switch (choice1) {
		case 0: 
			switch (choice2) {
				case 0:
					sort_by_divisor_count(list, choice3);
					break;
				case 1: 
					print_composites(list, choice3);
					break;
			}
			while (true) {
				cout << "Which of the composite numbers generated do you want all the factors of listed: " << endl;
				cin >> C;
				factors(list, pf_powers, primes, C);
			}
			break;
		case 1:
			print_primes(primes, choice3);
			break;
	}
}

/*
	vector<vector<vector<int>>> sub_vectors(1, vector<vector<int>>(1, factors));
	int i = 0;
	int size_initial = factors.size();
	vector<vector<int>> size(1, { size_initial });
	while (size[i][0] > 1) {
		i++;
		int previous = i - 1;
		int j = 0;
		size.push_back(vector<int>());
		sub_vectors.push_back(vector<vector<int>>());
		for (int l = 0; l < sub_vectors[previous].size(); l++) {
			int split = size[previous][l] / 2 + size[previous][l] % 2;
			int shift = 0;
			for (int b = 0; b < 2; b++) {
				sub_vectors[i].push_back(vector<int>());
				int j = sub_vectors[i].size() - 1;
				size[i].push_back(split);
				for (int k = shift; k < split + shift; k++) {
					sub_vectors[i][j].push_back(sub_vectors[previous][l][k]);
				}
				shift = size[i][l];
				split = size[previous][l] - split;
			}
		}
	}
	for (int i = sub_vectors.size() - 1; i > 0; i--) {
		int j = 0;
		int previous = i - 1;
		while (j < sub_vectors[i].size()) {
			int right_branch = j + 1;
			int parent = j / 2;
			for (int k = 0; k < sub_vectors[i][right_branch].size(); k++) {
				for (int l = sub_vectors[i][j].size() - 1; l >= 0; l--) {
					if (sub_vectors[i][right_branch][k] > sub_vectors[i][j][l]) {
						sub_vectors[i][j].insert(sub_vectors[i][j].begin() + l + 1, sub_vectors[i][right_branch][k]);
						break;
					}
					else if (l == 0) {
						sub_vectors[i][j].insert(sub_vectors[i][j].begin(), sub_vectors[i][right_branch][k]);
					}
				}
				sub_vectors[previous][parent] = sub_vectors[i][j];
				j = j + 2;
			}
		}
		factors = sub_vectors[0][0];
		print_factors(factors);
	}
*/