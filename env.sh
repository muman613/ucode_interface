#!/bin/bash

CWD=`pwd`

export PATH="$CWD/scripts:$PATH"

alias makeall="CLEAN=1 makeall.sh"
alias remakeall="makeall.sh"
alias build="CLEAN=1 build.sh"
alias rebuild="build.sh"

ulimit -c unlimited

