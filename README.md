# DNAcomp
Lossless compression of FASTA files in C++ 

DNAcomp is a small program writen in c++ to produce compressed DNA sequences from FASTA files. It packs 4 bases per byte and writes the sequence label and the unknown bases (N or n) in a separate file, allowing lossless compression of the sequence file. 

The bases A,C,G,T are compressed into bytes with the following translation A=00,C=01,G=10,T=11. If the end of the sequence is a partial byte (less than 4 bases) it writes it in the separate file.

##Single sequence compression

To compress and decompress a single sequence fasta file use the sources for singlecomp.cpp and singledecomp.cpp.

To compile use:

```
g++ -O3 singlecomp.cpp -o singlecomp
g++ -O3 singledecomp.cpp -o singledecomp
```

To run use:

```
singlecomp outputname *.fasta
singledecomp *.newfasta compressedfilename
```

##Multiple sequence compression

To compress and decompress a multiple sequence fasta file use the sources for multicomp.cpp and multidecomp.cpp.

To compile use:

```
g++ -O3 multicomp.cpp -o multicomp
g++ -O3 multidecomp.cpp -o multidecomp
```

To run use:

```
multicomp outputname *.fasta
multidecomp *.newfasta compressedfile
```

##Example use

First donwload the sample files from the sample folder and put them in the current directory of the program.

Then use:

```
// for single sequences
singlecomp samplec sample.fa
singledecomp newsample.fa samplec

// for multiple sequences
multicomp smallc small.fa
multidecomp newsmall.fa smallc
```

