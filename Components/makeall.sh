#!/bin/bash
###############################################################################
#	Build all components
###############################################################################

COMPONENTS="gbusfifolib platformDB platformDB2 remote_client structure_control symbolmgr fileresolver smpPlatformLib targetOptions"

for comp in $COMPONENTS; do
	pushd > /dev/null $comp
	echo "Building $comp"
	makeall.sh
	popd > /dev/null
done

