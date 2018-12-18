#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <functional>
#include <type_traits>

class args_t
{
public:
	args_t() = default;

	args_t(int argc, char *argv[])
	{
		std::size_t index = 0;
		for (size_t i = 1; i < argc; i++)
		{
			arg_list.emplace_back(index, argv[i]);
			index++;
		}
	}

	~args_t() = default;

	std::vector<std::tuple<std::size_t, std::string>> arg_list;
	std::vector<std::string> key_list;

private:

};

class scope_guard_t
{
public:
	explicit scope_guard_t(std::function<void()> on_exit_scope)
		: on_exit_scope_(on_exit_scope),
		dismissed_(false)
	{ }

	~scope_guard_t()
	{
		if (!dismissed_)
		{
			on_exit_scope_();
		}
	}

	void dismiss()
	{
		dismissed_ = true;
	}

private:
	bool dismissed_;
	std::function<void()> on_exit_scope_;
	scope_guard_t(scope_guard_t const&) = delete;
	scope_guard_t& operator=(scope_guard_t const&) = delete;
};

std::string get(args_t &argument, bool &is_success)
{
	using namespace std;
	auto &key_list = argument.key_list;
	auto &arg_list = argument.arg_list;
	is_success = false;

	scope_guard_t guard(
		[&key_list]()
	{
		key_list.clear();
	});

	for (auto &i : arg_list)
	{
		auto index = std::get<0>(i);
		auto value = std::get<1>(i);
		auto itor = std::find(key_list.begin(), key_list.end(), value);
		if (itor != key_list.end())
		{
			is_success = true;
			if (index == arg_list.size() - 1)
			{
				return "";
			}
			else
			{
				auto next_value = std::get<1>(arg_list[index + 1]);
				if (next_value[0] == '-' || next_value[0] == '/')
				{
					return "";
				}
				return std::move(next_value);
			}
		}
	}

	return "";
}

std::string get(args_t &argument)
{
	using namespace std;
	bool is_success = true;
	return get(argument, is_success);
}

template<typename Out, typename ...Args>
Out get(args_t &argument, std::string arg, Args ...args)
{
	argument.key_list.push_back(arg);
	bool is_success = true;
	return get(argument, is_success, std::forward<Args>(args)...);
}

template<typename ...Args>
std::string get(args_t &argument, bool &is_success, std::string arg, Args ...args)
{
	argument.key_list.push_back(arg);
	return get(argument, is_success, std::forward<Args>(args)...);
}
