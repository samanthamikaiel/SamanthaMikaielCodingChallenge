#!/bin/sh

GRADER_ROOT=$(dirname ${BASH_SOURCE})

PROJECT_PATH=${GRADER_ROOT}/..

INPUT_PATH=${GRADER_ROOT}/src

OUTPUT_PATH=${GRADER_ROOT}/output

g++ --std=c++11 ${INPUT_PATH}/sessionization.cpp -o ${GRADER_ROOT}/sessionization && cd ${GRADER_ROOT} && ${GRADER_ROOT}/sessionization > ${OUTPUT_PATH}/sessionization.txt
