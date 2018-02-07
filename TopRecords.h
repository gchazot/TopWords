#pragma once

#include "def.h"
#include <list>

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
		while(insertIt->count < count) {
			++insertIt;
		}
		if(_top.size() < TOP_SIZE || insertIt != _top.begin()) {
			_top.emplace(insertIt, element, count);

			if(_top.size() > TOP_SIZE) {
				_top.pop_front();
			}
		}
	}

	void print() {
		for(const auto & item: _top){
			debug(item.count << "\t" << item.word);
		}
	}

private:
	list<TopItem> _top;
};
