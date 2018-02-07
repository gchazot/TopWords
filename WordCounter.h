#pragma once

#include "def.h"
#include "TopRecords.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

constexpr bool isUpperCase(CharType character) {
	return (character >= 'A' && character <= 'Z');
}

constexpr bool isLowerCase(CharType character) {
	return (character >= 'a' && character <= 'z');
}

constexpr bool is_separator(CharType character) {
	return !isUpperCase(character) && !isLowerCase(character);
}


constexpr CharType translate(CharType character) {
	if(isUpperCase(character)) {
		return character - 'A' + 'a';
	}
	return character;
}



class WordCounter {
public:
	WordCounter(const char * filename):
		_reader(filename, ios::in|ios::binary) {
	}

	void count() {
		parse_file();
		printTopWords();
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
				const CharType lowerCaseCharacter = translate(character);
				_currentWord.push_back(lowerCaseCharacter);
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

	void printTopWords() {
		TopList<20> topWords;
		for(const auto & wordCount: _counts) {
			//debug(wordCount.first << "\t" << wordCount.second);
			topWords.insert(wordCount.second, wordCount.first);
		}
		topWords.print();
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
