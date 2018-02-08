#pragma once

#include "def.h"
#include "LetterTree.h"
#include "TopRecords.h"

#include <fstream>

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
		_reader(filename, ios::in|ios::binary),
		_wordsCounts(),
		_currentWord(&_wordsCounts) {
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
				_currentWord.increment();
			} else {
				const CharType lowerCaseCharacter = translate(character);
				_currentWord.append(lowerCaseCharacter);
			}
		}
	}

	void printTopWords() {
		TopList<20> topWords;
		WordCursor cursor(_wordsCounts);
		while(cursor.next()) {
			topWords.insert(cursor.count(), cursor.word());
		}
		topWords.print();
	}


	size_t read() {
		_reader.read(_readBlock, ARCH_CHARS_PER_WORD);
		return _reader.gcount();
	}

	ifstream _reader;
	CharType _readBlock[ARCH_CHARS_PER_WORD];

	LetterTree _wordsCounts;
	WordInserter _currentWord;
};
