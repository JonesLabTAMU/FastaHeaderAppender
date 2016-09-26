# FastaHeaderAppender
FastaHeaderAppender
Adam Jones (ajones@bio.tamu.edu)

FILES INCLUDED:
<p>FastaHeaderAppender: 64-bit Ubuntu executable (no extension)</p>
FastaHeaderAppender.exe: Windows executable (.exe extension),
FastaHeaderAppender.cpp: C++ source code

This program simply adds some text to the end of each header in
a fasta file.  The program can also replace spaces in the header
with underscores.


Installation and Usage:


Windows: 

Put the executable (FastaHeaderAppender.exe) in the folder with 
your fasta file.  Double click on FastaHeaderAppender.exe to run
in interactive mode.  Answer the queries to specify the parameters
for the program.


Ubuntu (and maybe other forms of Linux):

Put the executable in the folder with your fasta file.  For help:

./FastaHeaderAppender -h

To run in interactive mode:

./FastaHeaderAppender

To run with arguments:

./FastaHeaderAppender -i fasta_file.fa -o output_fasta_file.fa -s string_to_append -u y

You may need to alter file permissions for it to run:

chmod u+x FastaHeaderAppender



Other operating systems:

Compile the source code using the g++ compiler.

Here's one way to do it:

g++ FastaHeaderAppender.cpp -o FastaHeaderAppender


Arguments:

-i:	name of the input file (fasta_file.fa for example)
-o:	name of the output file (will be overwritten if it exists)
-s:	string to append
-u:	replace spaces with underscores (y or n)
