// testplatformlib.cpp : Defines the entry point for the console application.
//

#include "libplatformdb.h"

#define PLATFORM_DB_FILE "../../../xml/tango_platform_config.xml"


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

void displayChipInfo(PlatformDatabase& platDB, std::string sChipID) {
    PlatformChip chip;

    if (platDB.FindChip(chip, sChipID)) {
        printf("Dumping chip %s\n", sChipID.c_str());
        chip.Dump(stdout);
    } else {
        printf("Invalid chip %s specified!\n", sChipID.c_str());
    }

    return;
}

/**
 *
 */

void displayBlockInfo(PlatformDatabase& platDB, STRING sChipID, STRING sBlockID) {
    PlatformBlock   block;

    if (platDB.FindBlock(block, sChipID, sBlockID)) {
        printf("Chip %s has %zu blocks.\n", block.get_parent()->get_chip_id().c_str(),
               block.get_parent()->get_block_count());
        printf("Dump of block which was found!\n");
        block.Dump( stdout );
    } else {
        PlatformChip    chip;

        if (platDB.FindChip(chip, sChipID)) {
            STRING_VECTOR   sVec;

            printf("Unable to locate requested block '%s', please choose one:\n",
                   sBlockID.c_str());

            if (chip.GetBlockNames(sVec)) {
                for (size_t i = 0 ; i < sVec.size() ; i++) {
                    printf("   %s\n", sVec[i].c_str());
                }
            }
        } else {
            printf("Invalid chip ID '%s' specified!\n", sChipID.c_str());
        }
    }

    return;
}


/**
 *
 */

int main(int argc, const char* argv[]) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxInitialize();
#endif // __WXGTK__

	PlatformDatabase platDB;

	if (argc >= 1) {
		STRING sDBname = PLATFORM_DB_FILE; //(char *)argv[1];

		printf("Loading XML file %s\n", sDBname.c_str());

		if (platDB.LoadDatabase(sDBname)) {
			printf("OK!\n");

			if (argc == 2) {
                displayChipInfo(platDB, (char *)argv[1]);
			} else if (argc == 3) {
                displayBlockInfo(platDB, (char *)argv[1], (char *)argv[2]);
			} else {
//				platDB.Dump();

                STRING_PAIR_VECTOR sVec;

                if (platDB.GetChipPairs(sVec)) {
					for (size_t i = 0 ; i < sVec.size() ; i++) {
						printf("%-32s - %s\n",
                            sVec[i].first.c_str(),
                            sVec[i].second.c_str());
					}
                }

			}

		}
	} else {
		fprintf(stderr, "ERROR: must specify XML file on commandline!\n");
	}

	return 0;
}

