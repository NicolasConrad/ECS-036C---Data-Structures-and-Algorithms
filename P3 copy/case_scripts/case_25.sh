#!/bin/bash

# Test insertion that wraps around to next line.
infile=input_files/tiny.txt
cat stdin/input_25.txt | ./editor $infile

# Verify the input file's contents were not modified.
echo === $infile ===
cat $infile

# Print out the output file's contents.
outfile=output.txt
if [ -e $outfile ]; then
	echo === $outfile ===
	cat $outfile
	rm $outfile
else
	echo $outfile not generated
fi
