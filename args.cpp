// args.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
#include "include/args.hpp"

int main(int argc, char *argv[])
{
	args_t arg(argc, argv);
	auto ip = get(arg, 1, "--ip");
	auto port = get(arg, 2, "--port");
	if (!ip.empty())
	{
		cout << ip[0] << endl;
	}
	//if (!port.empty())
	//{
	//	cout << port[0] << endl;
	//}
	if (std::is_same<const char*, std::string>::value)
	{
		cout << "yes" << endl;
	}
	else
	{
		cout << "no" << endl;
	}
	return 0;
}
