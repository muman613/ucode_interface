#!/bin/bash
###############################################################################
#	Clean all object and depend files
###############################################################################

CLEAN_TARGETS="buildlog *~ *.o *.d core* nohup.out"

for target in $CLEAN_TARGETS; do
	echo "Removing $target files..."
	find . -iname "$target" -exec rm -rf {} \;
done

