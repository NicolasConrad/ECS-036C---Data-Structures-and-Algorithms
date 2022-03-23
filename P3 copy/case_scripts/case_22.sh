#!/bin/bash

# Test basic insertion.
infile=input_files/lines.txt
cat stdin/input_22.txt | ./editor $infile

# Verify the input file's contents were not modified.
echo === $infile ===
cat $infile

# Print out the output file's contents.
outfile=the_output.txt
if [ -e $outfile ]; then
	echo === $outfile ===
	cat $outfile
	rm $outfile
else
	echo $outfile not generated
fi
