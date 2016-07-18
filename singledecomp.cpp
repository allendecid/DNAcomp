/* Copyright (c) 2016 allendecid

Command line use: singledecomp fastafile compressedfile
Compile with: g++ -O3 singledecomp.cpp -o singledecomp
*/

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include <vector>
using namespace std;
int decimal_binary(int n);
int main(int argc, char** argv) { 


  if (argc<3) // if the input or output file are missing
    printf("To decompress FASTA: singledecomp fastafile compressedfile\n"), exit(1); // exit
  FILE *out=fopen(argv[1], "w"); 

  int b=1, c, n, d;
  int base=0;
  int lop=0;
  int j;
  int ct=0;
  int size=0;
  vector <int> example;

  for (int i=2; i<argc; ++i) {
    printf("%s\n", argv[i]);// input file
    FILE *in=fopen(argv[i], "rb");
    string input=string(argv[i])+".lb";
    FILE *ind=fopen(input.c_str(), "r");
    if (!in) continue;
    bool dna,switc=true;
    while ((d=getc(ind))!=EOF) {
    if (d=='>'){
    dna=true;}
    else if (d=='\n'){if (size==0){
    dna=false;}else{example.push_back(size),size=0;}}
    else if (d=='#'){
    example.push_back(size),size=0;}
    if (dna) {
    putc(d, out);}
    else if (!dna&&d!='\n'&&d!='#') {size=size+d;}
    
    
    
    }
   
    putc('\n', out);	
    while ((c=getc(in))!=EOF) { // each value c represents 4 nn
        ++ct;
      
	for (i=0; i<4; ++i) {++base;
            if(example[lop]==base){base=base+example[lop+1];
            for (j=0; j<example[lop+1]; ++j){putc('N', out);}lop=lop+2;}
            int t=(c>>(6-2*i))&3;
            putc("ACGT"[t], out);
            
	}
        if (ct==20){ putc('\n', out);ct=0;} // add column
    }
    if (in) fclose(in);
    if (ind) fclose(ind);
  }
  fclose(out);
 // printf("%c", base);
  return 0;

}

int decimal_binary(int n)  /* Function to convert decimal to binary.*/
{
    int rem, i=1, binary=0;
    while (n!=0)
    {
        rem=n%2;
        n/=2;
        binary+=rem*i;
        i*=10;
	//printf("%d s", rem);
    }
    return binary;
}

