// testplatformlib.cpp : Defines the entry point for the console application.
//

#include "libplatformdb.h"

#if defined(__WXGTK__) || defined(__WXMSW__)
#define printf wxPrintf
#endif

#ifndef	_WIN32
#ifdef _DEBUG
void debug(const char* sFmt, ...) {
	va_list vargs;
	va_start(vargs, sFmt);
	
	vfprintf(stderr, sFmt, vargs);
	
	va_end(vargs);
}
#endif // _DEBUG
#endif // _WIN32

/**
 *
 */

int main(int argc, const char* argv[]) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxInitialize();
#endif // __WXGTK__

	PlatformDatabase platDB;

	if (argc >= 2) {
		STRING sDBname = (char *)argv[1];
		printf("Loading XML file %s\n", sDBname.c_str());

		if (platDB.LoadDatabase(sDBname)) {
			printf("OK!\n");
//			platDB.Dump(stdout);

			if (argc == 3) {
				STRING sChipID = (char *)argv[2];
				PlatformChip chip;
				if (platDB.FindChip(chip, sChipID)) {
					printf("Dumping chip %s\n", sChipID.c_str());
					chip.Dump(stdout);
				} else {
					printf("Invalid chip %s specified!\n", sChipID.c_str());
				}
				//printf("%s has %ld blocks!\n", chip.get_chip_id().c_str(), chip.get_block_count()); 
			} else {
				STRING_VECTOR sVec;

				if (platDB.GetChipNames(sVec)) {
					for (size_t i = 0 ; i < sVec.size() ; i++) {
						printf("%s\n", sVec[i].c_str());
					}
				}
			}

		}
	} else {
		fprintf(stderr, "ERROR: must specify XML file on commandline!\n");
	}

	return 0;
}

