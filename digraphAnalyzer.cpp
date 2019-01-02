/*
 * digraphAnalyzer.cpp
 * Created on: Oct 25, 2018
 * Author: Shuhao Lai
 */
#include <string>
#include <iostream>
#include<fstream>
#include<vector>
#include<map>
#include<cctype>
#include<algorithm>
#include <utility>

using std::ifstream;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::make_pair;

/*
 * Converts a string to an int.
 * Returns a false bool if nums is not a number. Handles negative numbers.
 */
pair<int, bool> string_to_num(string nums)
{
	int factor = 1;
	int real_num = 0;
	bool negative = false;
	if(nums[0] == '-')
	{
		nums = nums.substr(1, nums.length()-1);
		negative = true;
	}
	for (int i = (int) nums.length() - 1; i >= 0; --i)
	{
		if (!isdigit(nums[i]))
			return make_pair(0, false);
		real_num += ((int) nums[i] - 48) * factor;
		factor *= 10;
	}
	if(negative)
		return make_pair(real_num*-1, true);
	return make_pair(real_num, true);
}

/*
 * Returns 1 if digraph is a substring of word. 0 otherwise.
 */
int contains_digraph(string digraph, string word)
{
	for (int i = 0; i <= (int) word.length() - (int) digraph.length(); i++)
	{
		if (digraph[0] == word[i])
		{
			int found = 1;
			for (unsigned int digraph_i = 1; digraph_i < digraph.length();
					digraph_i++)
				if (digraph[digraph_i] != word[digraph_i + i])
				{
					found = 0;
					break;
				}
			if (found)
				return 1;
		}
	}
	return 0;
}

/*
 * Removes anything that is not a letter from word.
 */
string remove_punctuations(string word)
{
	string no_punc = "";
	for (unsigned int i = 0; i < word.length(); i++)
		if (isalpha(word[i]))
			no_punc += word[i];
	return no_punc;
}

/*
 * Prints and formats a vector that stores pair<string, vector<string>>.
 */
void print_vector(vector<pair<string, vector<string>>> counts)
{
	for (vector<pair<string, vector<string>>>::iterator it = counts.begin();
	it != counts.end(); ++it)
	{
		cout << it->first << ": [";
		int words_found = it->second.size();
		if (words_found == 0)
		cout << "]";
		else
		for (int i = 0; i < words_found; i++)
		{
			if (i != words_found - 1)
			cout << it->second[i] << ", ";
			else
			cout << it->second[i] << "]";
		}
		cout << endl;
	}
}

/*
 * Prints and formats a map that stores <string, vector<string>>.
 */
void print_map(map<string, vector<string>> counts)
{
	for (map<string, vector<string>>::iterator it = counts.begin();
			it != counts.end(); ++it)
	{
		cout << it->first << ": [";
		int words_found = it->second.size();
		if (words_found == 0)
			cout << "]";
		else
			for (int i = 0; i < words_found; i++)
			{
				if (i != words_found - 1)
					cout << it->second[i] << ", ";
				else
					cout << it->second[i] << "]";
			}
		cout << endl;
	}
}

/*
 * Returns the lowercase version of str. Nonletters are left alone.
 */
string to_lower(string str)
{
	string lowercased = "";
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (isalpha(str[i]) && isupper(str[i]))
			lowercased += tolower(str[i]);
		else
			lowercased += str[i];
	}
	return lowercased;
}

/*
 * Custom compare to compare according to ascii.
 */
bool cmp(const pair<string, vector<string>> p1,
		const pair<string, vector<string>> p2)
{
	return (p1.first < p2.first) > 0;
}

/*
 * Custom compare to compare according to reverse ascii.
 */
bool reverse_cmp(const pair<string, vector<string>> p1,
		const pair<string, vector<string>> p2)
{
	return (p2.first < p1.first) > 0;
}

/*
 * Custom compare to compare according to the number of strings in vector<string>.
 */
bool count_cmp(const pair<string, vector<string>> p1,
		const pair<string, vector<string>> p2)
{
	if(p1.second.size() == p2.second.size())
		return (p1.first < p2.first) > 0;
	return p1.second.size() > p2.second.size();
}

/*
 * Sorts the vector according to argument.
 */
vector<pair<string, vector<string>>> sort(const char how, vector<pair<string, vector<string>>> counts)
{
	if(how == 'a')
		sort(counts.begin(), counts.end(), cmp);
	else if(how == 'r')
		sort(counts.begin(), counts.end(), reverse_cmp);
	else
		sort(counts.begin(), counts.end(), count_cmp);
	return counts;
}

/*
 * Prints and formats vector<string>.
 */
void print_one_vector(vector<string> vec)
{
	for (vector<string> ::iterator it = vec.begin();it != vec.end(); ++it)
		cout << *it << endl;
}

/*
 * Prints all the digraphs with the number of counts specified by c. Prints None if none exists.
 */
void count_query(vector<pair<string, vector<string>>> counts, int c)
{
	int nums_of_c = 0;
	for (vector<pair<string, vector<string>>> ::iterator it = counts.begin();it != counts.end(); ++it)
		if((int)(it->second.size()) == c)
		{
			cout << it->first << endl;
			print_one_vector(it->second);
			nums_of_c++;
		}
	if(!nums_of_c)
		cout << "None" << endl;
}

/*
 * Prints all the strings that contains the digraph specified by the digraph argument.
 * Prints "No such digraph" if it does not exists within the input text.
 */
void digraph_query(map<string, vector<string>> counts, string digraph)
{
	if(counts.find(digraph) == counts.end())
		cout << "No such digraph" << endl;
	else if(counts[digraph].size() == 0)
		cout << "0" << endl;
	else
	{
		cout << counts[digraph].size() << endl;
		print_one_vector(counts[digraph]);
	}
}


int main(int argc, char * argv[])
{
	if (argc != 3 || (*argv[2] != 'a' && *argv[2] != 'r' && *argv[2] != 'c'))
	{
		cout << "Incorrect terminal inputs.\n";
		return 1;
	}
	ifstream file;
	string filename = argv[1];
	file.open(filename, ifstream::in);
	if (!file.is_open())
	{
		cout << "file could not be opened" << endl;
		return 1;
	}

	//reading in the first line of the txt
	string word;
	file >> word;
	pair<int, bool> temp = string_to_num(word);
	if (!temp.second)
	{
		cout << "Invalid argument for number of digraphs." << endl;
		return 1;
	}
	int num_digraphs = temp.first;
	//Not using a map because I can't sort it.
	vector<pair<string, vector<string>>> counts;
	for (int i = 0; i < num_digraphs; i++)
	{
		file >> word;
		vector<string> words;
		counts.push_back(make_pair(to_lower(word), words));
	}
	//reading the actual txt now
	while (file >> word)
	{
		word = to_lower(word);
		for (vector<pair<string, vector<string>>> ::iterator it = counts.begin();it != counts.end(); ++it)
			if (contains_digraph(it->first, word))
				it->second.push_back(remove_punctuations(word));
	}
	print_vector(sort(*argv[2], counts));

	//Accpeting queries
	counts = sort('a', counts);
	map<string, vector<string>> vec_to_map;
	for (vector<pair<string, vector<string>>>::iterator it = counts.begin();it != counts.end(); ++it)
		vec_to_map[it->first] = it->second;

	cout << "q?>";
	string q;
	while (cin >> q && q != "quit")
	{
		q = to_lower(q);
		pair<int, bool> temp = string_to_num(q);
		if(temp.second)
		{
			if(temp.first < 0)
			{
				cout << "Number cannot be negative." << endl;
				cout << "q?>";
				continue;
			}
			count_query(counts, temp.first);
		}
		else
			digraph_query(vec_to_map, q);
		cout << "q?>";
	}
}

