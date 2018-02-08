#pragma once

#include "def.h"

#include <list>


class LetterTree {
public:
	LetterTree(): _character('A' - 1), _count(0) {}

	explicit LetterTree(CharType letter):
		_character(letter),
		_count(0) {
	}

	LetterTree * nextCharacter(CharType character){
		auto letterIt = _next_letters.begin();
		while(letterIt != _next_letters.end()) {
			if(letterIt->_character == character) {
				return &*letterIt;
			}
			++letterIt;
		}

		return &_next_letters.emplace_back(character);
	}

	void increment() {
		++_count;
	}

private:
	friend class WordCursor;

	CharType _character;
	size_t _count;
	list<LetterTree> _next_letters;

};

class WordInserter {
public:
	explicit WordInserter(LetterTree * letterTree):
		_rootLetter(letterTree),
		_currentLetter(letterTree) {
	}

	void append(CharType character) {
		_currentLetter = _currentLetter->nextCharacter(character);
	}

	void increment() {
		if( _currentLetter != _rootLetter) {
			_currentLetter->increment();
			reset();
		}
	}

private:
	LetterTree * const _rootLetter;
	LetterTree * _currentLetter;

	void reset() {
		_currentLetter = _rootLetter;
	}
};

class WordCursor {
	typedef list<LetterTree>::const_iterator LetterIterator;
public:
	explicit WordCursor(const LetterTree & letterTree):
		_top(letterTree) {
	}

	bool next() {
		if(_letters.empty()) {
			_letters.push_back(_top._next_letters.begin());
			if(!currentIsValid()) {
				return false;
			} else if(current()->_count > 0) {
				return true;
			}
		}

		while(nextValidWord()) {
			if(current()->_count > 0) {
				return true;
			}
		}
		return false;
	}

	size_t count() const {
		return current()->_count;
	}

	Word word() const {
		Word result;
		for(const auto letter: _letters){
			result.push_back(letter->_character);
		}
		return result;
	}


private:
	const LetterTree & _top;
	list<LetterIterator> _letters;

	LetterIterator & current() {
		return _letters.back();
	}
	const LetterIterator & current() const {
		return _letters.back();
	}

	const LetterTree & currentParent() const {
		if(_letters.size() == 1) {
			return _top;
		}
		return * * prev(prev(_letters.end()));
	}

	bool nextValidWord() {
		if(enterLetter()) {
			return true;
		}
		if(advanceLetter()) {
			return true;
		}
		while(exitLetter()) {
			if(advanceLetter()) {
				return true;
			}
		}
		return false;
	}

	bool currentIsValid() const {
		return (!_letters.empty()) && (current() != currentParent()._next_letters.end());
	}

	bool enterLetter() {
		if(!currentIsValid()) {
			return false;
		} else if(current()->_next_letters.empty()) {
			return false;
		} else {
			_letters.push_back(current()->_next_letters.begin());
			return true;
		}
	}

	bool exitLetter() {
		if(!_letters.empty()) {
			_letters.pop_back();
			return true;
		}
		return false;
	}

	bool advanceLetter() {
		if(!currentIsValid()) {
			return false;
		} else {
			++current();
			return currentIsValid();
		}
	}
};
