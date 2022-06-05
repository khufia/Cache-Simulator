#include<bits/stdc++.h>
#include<stdlib.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

const int N = 1e6;

// vector container to store if the line is valid or not
vector<bool> valid;
// vector container to store the tags of the line
vector<int> Tags;

// returns the index  value from the address
int getIndex(bitset<32> &s) {
	int index = 0;
	int j = 1;
	for(int i = 2; i < 18; i++) {
		index += (s[i])*j;
		j *= 2;
	}
	return index;
}

// returns the tag value from the address
int getTag(bitset<32> &s) {
	int tag = 0;
	int j = 1;
	for(int i = 18; i < 32; i++) {
		tag += (s[i])*j;
		j *= 2;
	}
	return tag;
}

// checks if the address is a hit or a miss
bool check(int index, int tag) {
	if(valid[index] && Tags[index] == tag) {
		return 1;
	}
	valid[index] = 1;
	Tags[index] = tag;
	return 0;
}

// run the file
void run(const char *filename) {
	// streaming the file
	ifstream fp(filename);

	valid = vector<bool>(N);
	Tags = vector<int>(N);

    int misses = 0, hits = 0, total = 0;
    string input;

    while(getline(fp, input)) {
    	// s1 stores the address in hexadecimal
    	string s1 = input.substr(4, 8);
    	// converting address in decimal format
    	long long x = stol(s1, 0, 16);
    	// converting the address to binaryformat
    	bitset<32> s(x);
    	// get the index value
    	int index = getIndex(s);
    	// get the tag value
    	int tag = getTag(s);
    	// if it's a hit, increment no. of hits
    	hits += check(index, tag);
    	total++;
    }
    misses = total - hits;
    // print out the respective values of total, hits and misses
    cout << "Total" << "   " << "Hits" << "  " << "Misses" << '\n';
    cout << total << " " << hits << " " << misses << '\n';
    fp.close();
    Tags.clear(); valid.clear();
}

int main() {
	cout << "gcc.trace\n";
	run("gcc.trace");
	cout << '\n';

	cout << "gzip.trace";
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


