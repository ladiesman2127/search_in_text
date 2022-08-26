#include <iostream>
#include <deque>
#include <vector>
#include <cmath>


const int p = 1000000007;
const int X = 1;


int hash(const std::string& s)
{
	long long result = 0;
	long long pow = 1;
	for (const auto& ch : s)
	{
		result = ((result % p) + (ch * pow % p)) % p;
		pow = (pow * X) % p;
	}
	return result % p;

}

int hasi_prev(const int& hash_next, const char& t_out, const int& xpattern, const int& ti)
{
	return ((hash_next % p - t_out * xpattern) % p * X % p + ti % p) % p;
}


int main()
{
	std::string text, pattern;
	std::cin >> pattern >> text;
	const int pattern_hash = hash(pattern);
	const int pattern_length = pattern.length();
	const int last_window_index = text.length() - pattern.length();
	std::vector<int> hash_table(last_window_index + 1);
	hash_table[last_window_index] = hash(text.substr(last_window_index));
	for (int i = last_window_index - 1; i >= 0; --i)
	{
		hash_table[i] = hasi_prev(hash_table[i + 1], text[i + pattern_length], std::pow(X, pattern_length - 1), text[i]);
	}

	for(int i = 0; i <= last_window_index; ++i)
	{
		if(hash_table[i] == pattern_hash && text.substr(i,pattern_length) == pattern)
		{
			std::cout << i << ' ';
		}
	}
	return 0;
}

