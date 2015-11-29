#!/usr/bin/env bash

# command input parameters
SKETCH_PATH=`pwd`/main
echo The code is at: ${SKETCH_PATH}
OUT_BYTECODE_PATH=`pwd`/out-bytecode
echo The bytecode output will be at: ${OUT_BYTECODE_PATH}
mkdir -p ${OUT_BYTECODE_PATH}

# preparing the command string
BUILD_COMMAND="processing-java --sketch=${SKETCH_PATH} --output=${OUT_BYTECODE_PATH} --force --run"
echo -e "Running this build command: \n ${BUILD_COMMAND}"

# run the command TODO as detached from the current shell: &
${BUILD_COMMAND}

