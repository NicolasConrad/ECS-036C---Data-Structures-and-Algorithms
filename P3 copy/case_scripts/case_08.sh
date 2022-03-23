#!/bin/bash

infile=input_files/file01.txt
cat stdin/input_08.txt | ./editor $infile

# Verify the input file's contents were not modified.
echo === $infile ===
cat $infile

# Print out the output file's contents.
outfile=output_08.txt
if [ -e $outfile ]; then
	echo === $outfile ===
	cat $outfile
	rm $outfile
else
	echo $outfile not generated
fi
