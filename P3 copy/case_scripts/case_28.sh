#!/bin/bash

# Test undo operations.
infile=input_files/file04.txt
cat stdin/input_28.txt | ./editor $infile

# Print out the output file's contents.
outfile=here_we_go.txt
if [ -e $outfile ]; then
	echo === $outfile ===
	cat $outfile
	rm $outfile
else
	echo $outfile not generated
fi

# Print out the second output file's contents.
outfile=here_we_go2.txt
if [ -e $outfile ]; then
	echo === $outfile ===
	cat $outfile
	rm $outfile
else
	echo $outfile not generated
fi
