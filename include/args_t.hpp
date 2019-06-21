#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstring>
#include <utility>
#include <algorithm>

#include "range.hpp"
#include <utility>
#include <tuple>

using namespace std;

class args_t
{
public:
	args_t(int argc, char *argv[])
	{
		for (std::size_t i = 0; i < std::size_t(argc); i++)
		{
			arg_list.emplace_back(argv[i], i);
		}
	}

	~args_t() = default;

	std::vector<std::tuple<std::string, std::size_t>> arg_list;

private:

};
