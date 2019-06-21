#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstring>
#include <utility>
#include <algorithm>
#include "range.hpp"

using namespace std;

class args_t
{
public:
	args_t(int argc, char *argv[])
	{
		for (size_t i = 0; i < argc; i++)
		{
			arg_list.emplace_back(argv[i], i);
		}
	}

	~args_t() = default;

	std::vector<std::tuple<std::string, std::size_t>> arg_list;

private:

};

std::vector<std::string> get(args_t &argument)
{
	using namespace std;
	vector<string> result;
	return std::move(result);
}

template<typename ...Args>
std::vector<std::string> get(args_t &argument, std::string arg, Args ...args)
{
	using namespace std;
	vector<string> result;
	auto &arg_list = argument.arg_list;

	auto itor = find_if(arg_list.begin(), arg_list.end(),
		[&arg](auto &i)
	{
		return arg == std::get<0>(i);
	});
	if (itor != arg_list.end())
	{
		auto &index = std::get<1>(*itor);

		auto v = skip_n(arg_list, index + 1);

		auto vec = take_if(v,
			[&index](auto &i)
		{
			auto &val = std::get<0>(i);
			auto &ind = std::get<1>(i);
			return ind > index &&
				val[0] != '-' &&
				val[0] != '/';
		});

		for (auto &v : vec)
		{
			result.push_back(std::get<0>(v));
		}

		if (result.empty())
		{
			result.push_back("");
		}

		return std::move(result);
	}
	else
	{
		return get(argument, forward<Args>(args)...);
	}
}

template<typename ...Args>
std::vector<std::string> get(args_t &argument, int arg, Args ...args)
{
	using namespace std;
	vector<string> result;
	auto &arg_list = argument.arg_list;

	if (arg >= arg_list.size())
	{
		return std::move(result);
	}

	if (any_of(arg_list.begin(), arg_list.end(),
		[&arg](auto &i)
	{
		auto &value = std::get<0>(i);
		auto &index = std::get<1>(i);
		return index <= arg && (value[0] == '-' || value[0] == '/');
	}))
	{
		return get(argument, forward<Args>(args)...);
	}

	result.push_back(std::get<0>(arg_list[arg]));
	return std::move(result);
}

template<typename ...Args>
std::vector<std::string> get(args_t &argument, const char* arg, Args ...args)
{
	using namespace std;
	return get(argument, string(arg), forward<Args>(args)...);
}
