#pragma once

#include "def.h"
#include "TopRecords.h"

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
		parse_file();

		TopList<20> topWords;
		for(const auto & wordCount: _counts) {
			//debug(wordCount.first << "\t" << wordCount.second);
			topWords.insert(wordCount.second, wordCount.first);
		}
		topWords.print();
	}

	bool good() const {
		return _reader.good();
	}

private:
	void parse_file() {
			while(good()) {
			const size_t readSize = read();
			parse_block(readSize);
		}
	}

	void parse_block(size_t readSize) {
		for(size_t i=0; i < readSize; ++i) {
			const CharType character = _readBlock[i];
			if( is_separator(character) ) {
				increment_word();
				//debug("Separator: " << character);
			} else {
				//debug("Character: " << character);
				_currentWord.push_back(character);
			}
		}
	}

	void increment_word() {
		if( _currentWord.size() > 0 ) {
			//debug("Word: " << _currentWord);

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
