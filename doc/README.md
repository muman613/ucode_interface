#README

Source `scripts/env.sh` to add scripts to the path.

Interface implementations can be found in `interface1`, `interface2`, and `interface3`, and `interface4`.

The master make system is located in the 'Build' sub-directory.

Components used by the project are located in the 'Components' sub-directory.

Documentation can be found in the 'doc' sub-directory.

Microcode used by the interface must be installed in the 'ucode' sub-directory.

XML files such as the platform databaes are stored in the 'xml' sub-directory.

Each sub-project has it's own 'Makefile' in it's directory. The build system is sensitive to a few ENVIRONMENT variables such as:

	ARCH      	Specify whether to build for x86 (32bit) or x86_64 (64bit)
	DEBUG		If DEBUG is defined then the target is a debug object.

Each sub-project has a Bash script named 'makeall.sh' which will do a clean build for each supported target {Release x86_64, Debug x86_64, Release x86, Debug x86}.

Helper scripts such as 'build.sh' which are in the path if the 'env.sh' script is sourced provide the Text UI for building.

####HELPER SCRIPTS

	makeall.sh			-	Build all configurations.
	CLEAN=1 makeall.sh 	-	Clean the project and rebuild it.
	build.sh			-	Build all configurations in a text GUI.
	CLEAN=1 build.sh	-	Clean the project and rebuild in a text GUI.

####TO BUILD ALL CONFIGURATIONS:

	CLEAN=1 build.sh	# Clean the project before building.


*Last update : Wednesday, 02. November 2016 05:41PM*

