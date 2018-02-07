#include "def.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool is_separator(CharType character) {
	const bool upperCase =  (character >= 'A' && character <= 'Z');
	const bool lowerCase =  (character >= 'a' && character <= 'z');
	return !upperCase && !lowerCase;
}


class WordCounter {
public:
	WordCounter(const char * filename):
		_reader(filename, ios::in|ios::binary) {
	}

	void count() {
		while(good()) {
			const size_t readSize = read();
			parse_block(readSize);
		}
	}

	bool good() const {
		return _reader.good();
	}

private:
	void parse_block(size_t readSize) {
		for(size_t i=0; i < readSize; ++i) {
			const CharType character = _readBlock[i];
			if( is_separator(character) ) {
				increment_word();
			} else {
				_currentWord.push_back(character);
			}
		}
	}

	void increment_word() {
		if( _currentWord.size() > 0 ) {
			size_t newCount = 1;
			auto wordCount = _counts.find(_currentWord);
			if( wordCount != _counts.end() ) {
				newCount += wordCount->second;
			}

			_counts[_currentWord] = newCount;
			_currentWord.clear();
		}
	}


	size_t read() {
		_reader.read(_readBlock, ARCH_CHARS_PER_WORD);
		return _reader.gcount();
	}

	ifstream _reader;
	CharType _readBlock[ARCH_CHARS_PER_WORD];

	Word _currentWord;

	WordsCount _counts;
};
