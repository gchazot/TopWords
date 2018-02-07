#include "def.h"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool is_separator(CharType character) {
	return (character < 'a' || character > 'Z');
}


class WordCounter {
public:
	WordCounter(const char * filename):
		_reader(filename, ios::in|ios::binary)
	{
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
		for(size_t i=0; i < readSize; ++i){
			if( is_separator(_readBlock[i]) ){
				increment_word();
			}
			else
			{
				_counts.find(_currentWord);
			}
		}
	}

	void increment_word(){
		if( _currentWordIndex > 0 ){
			_currentWord[_currentWordIndex] = '\0';

			size_t newCount = 1;
			auto wordCount = _counts.find(_currentWord);
			if( wordCount != _counts.end() ){
				newCount += wordCount->second;
			}

			_counts[_currentWord] = newCount;
		}
	}


	size_t read() {
		_reader.read(_readBlock, ARCH_CHARS_PER_WORD);
		return _reader.gcount();
	}

	ifstream _reader;
	CharType _readBlock[ARCH_CHARS_PER_WORD];

	Word _currentWord;
	size_t _currentWordIndex;

	WordsCount _counts;
};
