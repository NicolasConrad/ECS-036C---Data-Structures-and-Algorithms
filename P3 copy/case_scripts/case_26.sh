#!/bin/bash

# Test insertion that generates new lines.
infile=input_files/file04.txt
cat stdin/input_26.txt | ./editor $infile

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
