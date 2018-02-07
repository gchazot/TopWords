#include "WordCounter.h"
#include "TopRecords.h"

int main (int argc, char *argv[])
{
	if( argc < 2 ) {
		cerr << "Usage: " << argv[0] << " <filename>." << endl;
		return 1;
	}

	WordCounter counter(argv[1]);
	if( !counter.good() ) {
		cerr << "Can not read file" << endl;
		return 2;
	}

	counter.count();
	return 0;
}
