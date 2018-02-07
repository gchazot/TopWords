#pragma once

#include "def.h"
#include <list>

using namespace std;

struct TopItem {
	Word word;
	size_t count;

	TopItem(Word word, size_t count): word(word), count(count) {}
};

template<size_t TOP_SIZE>
class TopList {
public:
	void insert(size_t count, Word element) {
		list<TopItem>::const_iterator insertIt = _top.begin();
		while(insertIt->count > count) {
			++insertIt;
		}
		_top.emplace(insertIt, element, count);

		if(_top.size() > TOP_SIZE) {
			_top.pop_front();
		}
	}

private:
	list<TopItem> _top;
};
