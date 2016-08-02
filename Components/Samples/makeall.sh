#!/bin/bash
###############################################################################
#	Build all components
###############################################################################

COMPONENTS="testgbus testPlatformDB testrc testStruct testsymbols testAlloc"

for comp in $COMPONENTS; do
	pushd > /dev/null $comp
	echo "Building $comp"
	./makeall.sh
	popd > /dev/null
done

