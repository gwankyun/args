#pragma once
#include <algorithm>

template<typename Range, typename Pred>
Range take_if(const Range &source, Pred pred)
{
	using namespace std;
	Range result;
	auto bi = back_inserter(result);
	for (auto &i : source)
	{
		if (pred(i))
		{
			bi++;
			*bi = i;
		}
		else
		{
			return std::move(result);
		}
	}
	return std::move(result);
}

template<typename Range, typename Pred>
Range skip_if(const Range &source, Pred pred)
{
	using namespace std;
	Range result;
	auto itor = find_if_not(begin(source), end(source), pred);
	auto index = itor - begin(source);
	copy(begin(source) + index, end(source), back_inserter(result));
	return std::move(result);
}

template<typename Range>
Range skip_n(const Range &range, std::size_t size)
{
	using namespace std;
	Range result;
	copy(begin(range) + size, end(range), back_inserter(result));
	return std::move(result);
}
