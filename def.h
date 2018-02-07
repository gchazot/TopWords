#pragma once

#include <map>
#include <string>

typedef std::string Word;
typedef Word::value_type CharType;
typedef std::map<Word, size_t> WordsCount;

static const unsigned int ARCH_WORD_WIDTH_BITS = 64;
static const unsigned int CHAR_WIDTH_BITS = 8 * sizeof(CharType);
static const unsigned int ARCH_CHARS_PER_WORD = ARCH_WORD_WIDTH_BITS/CHAR_WIDTH_BITS;

#define log(args) cout << args << endl
#define debug(args) cerr << args << endl
