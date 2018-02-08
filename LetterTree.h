#pragma once

#include "def.h"


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
	CharType _character;
	size_t _count;
	list<LetterTree> _next_letters;

};

class WordInserter {
public:
	explicit WordInserter(LetterTree * letterTree):
		_currentLetter(letterTree) {
	}

	void append(CharType character) {
		_currentLetter = _currentLetter->nextCharacter(character);
	}

	void incrementWord() {
		_currentLetter->increment();
	}

private:
	LetterTree * _currentLetter;
};
