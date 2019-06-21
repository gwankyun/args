// args.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstring>
#include <utility>
#include <algorithm>

#include "include/args.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	args_t args(argc, argv);

	auto filename = get(args, 1, "--filename", "-f");
	auto mode = get(args, 2, "--mode", "-m");

	if (!filename.empty())
	{
		cout << "filename:" << filename[0] << endl;
	}

	if (!mode.empty())
	{
		cout << "mode:" << mode[0] << endl;
	}

	return 0;
}
