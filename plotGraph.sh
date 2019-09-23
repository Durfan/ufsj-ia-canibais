#!/bin/bash

exe() { echo "${@/eval/}";"$@"; }

OUTDIR="./resources/"

for filename in ${OUTDIR}*.dot; do
    exe eval "dot -Tsvg ${filename} > ${filename%.*}.svg"
done