#pragma once
#include <iostream>
#include <vector>
const int MAX_INT = 256;


int toInt(char a)
{

	if (a == 'A')
		return 0;
	else if (a == 'C')
		return 1;
	else if (a == 'T')
		return 2;
	else if (a == 'G')
		return 3;
	else
		return 4;
}

std::vector<int> makeBad_table(std::string pattern_str)
{
	int pattern_size = pattern_str.size();
	std::vector<int> bad(5, pattern_size);

	for (int i = 0; i < pattern_size; i++)
	{
		bad[toInt(pattern_str[i])] = i;
	}

	return bad;
}



std::vector<int> makeGoddsuffix_table(std::string pattern_str)
{
	int pattern_size = pattern_str.size();

	int pattern_pt = pattern_size; // pattern point
	int suffix_pt = pattern_pt + 1; // suffix point
	
	std::vector<int> suffix_table(pattern_size + 1, 0);
	suffix_table[pattern_pt] = suffix_pt;
	std::vector<int> skip_table(pattern_size + 1, 0);

	while (pattern_pt > 0)
	{
		while (suffix_pt <= pattern_size && 
			pattern_str[pattern_pt - 1] != pattern_str[suffix_pt - 1])
		{
			if (skip_table[suffix_pt] == 0)
			{
				skip_table[suffix_pt] == suffix_pt - pattern_pt;
			}
			suffix_pt = suffix_table[suffix_pt];
		}
		suffix_table[--pattern_pt] = --suffix_pt;
	}

	suffix_pt = suffix_table[0];

	while (pattern_pt < pattern_size)
	{
		if (skip_table[pattern_pt] == 0)
			skip_table[pattern_pt] = suffix_pt;
		if (pattern_pt++ == suffix_pt)
			suffix_pt = suffix_table[suffix_pt];
	}
	return skip_table;
}

int search(std::vector<int> bad_table, std::vector<int> good_suffix_table, std::string plain_text, std::string pattern_str)
{
	int plain_size = plain_text.size();
	int pattern_size = pattern_str.size();

	int begin = 0;

	if (plain_size < pattern_size)
		return -1;

	while (begin <= plain_size - pattern_size)
	{
		int match = pattern_size;
		int first = pattern_size;
		int miss_match = 0;
		
		while(match >0 && miss_match <5)
		{
			if (pattern_str[match - 1] != plain_text[begin + (match - 1)])
				miss_match++;
			/*if (miss_match == 1)
				first = match;*/
			match--;
			

		}
			if (match == 0)
				return begin;
			if (bad_table[toInt(plain_text[begin + first])] != pattern_size)
			{
				begin += std::max(first - bad_table[toInt(plain_text[begin + first])], good_suffix_table[first]);
			}
			else
			{
				begin += std::max(good_suffix_table[first], first);
			}
	}
	return -1;
}