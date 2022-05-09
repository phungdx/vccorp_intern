#include<iostream>
#include <vector>
using namespace std;

int lengthOfLongestSubstring(string s){
	vector<int> cache(256, -1);
	int maxLen = 0;
	int start = -1;

	for(int i = 0; i < s.length(); ++i){
		start = max(start, cache[s[i]]);
		cache[s[i]] = i;
		maxLen = max(i - start, maxLen);
	}
	return maxLen;
}


int main(){
	string s = "abcadbcbb";
	cout << lengthOfLongestSubstring(s);
	return 0;
}