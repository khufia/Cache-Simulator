#include<bits/stdc++.h>
#include<stdlib.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

const int N = 1e6;

// vector container to store if the line is valid or not
vector<vector<bool>> valid;
// vector container to store the tags
vector<vector<int>> Tags;
// vector container to implement LRU policy
vector<vector<int>> LRU;

// returns the index  value from the address
int getIndex(bitset<32> &s) {
	int index = 0;
	int j = 1;
	for(int i = 2; i < 16; i++) {
		index += (s[i])*j;
		j *= 2;
	}
	return index;
}

// returns the tag value from the address
int getTag(bitset<32> &s) {
	int tag = 0;
	int j = 1;
	for(int i = 16; i < 32; i++) {
		tag += (s[i])*j;
		j *= 2;
	}
	return tag;
}
            
// checks if the address is a hit or a miss
bool check(int index, int tag) {
	for(int i = 0; i < 4; i++) {
		if(valid[index][i] && Tags[index][i] == tag) {
			LRU[index][i] = *max_element(LRU[index].begin(), LRU[index].end()) + 1;  // updates the LRU value
			return 1;
		}
	}
	int id = min_element(LRU[index].begin(), LRU[index].end()) - LRU[index].begin();  // finds the way to be replaced
	valid[index][id] = 1;
	LRU[index][id] = *max_element(LRU[index].begin(), LRU[index].end()) + 1;
	Tags[index][id] = tag;
	return 0;
}

// run the file
void run(const char *filename) {

	fstream fp(filename);
	valid = vector<vector<bool>> (N, vector<bool>(4));
	LRU = vector<vector<int>> (N, vector<int>(4));
	Tags = vector<vector<int>> (N, vector<int>(4));

    int misses = 0, hits = 0, total = 0;
    string input;

    while(getline(fp, input)) {
    	// s1 stores the address in hexadecimal
    	string s1 = input.substr(4, 8);
 
    	long long x = stol(s1, 0, 16);
    	bitset<32> s(x);

    	int index = getIndex(s);
    	int tag = getTag(s);
    	// if it's a hit, increment no. of hits
    	hits += check(index, tag);
    	total++;
    }
    misses = total - hits;
    cout << "Total" << "   " << "Hits" << "  " << "Misses" << '\n';
    cout << total << " " << hits << " " << misses << '\n';
    fp.close();
    Tags.clear(); valid.clear();LRU.clear();
}


int main() {
	cout << "gcc.trace\n";
	run("gcc.trace");
	cout << '\n';

	cout << "gzip.trace\n";
	run("gzip.trace");
	cout << '\n';


	cout << "mcf.trace\n";
	run("mcf.trace");
	cout << '\n';

	cout << "swim.trace\n";
	run("swim.trace");
	cout << '\n';

	cout << "twolf.trace\n";
	run("twolf.trace");
}



