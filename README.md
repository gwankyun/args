# args
命令行參數解析

header-only，需C++11

用法：
``` c++
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
```
一行一個參數，支持位置項及命名項，命名項支持列表。
