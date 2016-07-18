/* Copyright (c) 2016 allendecid

Command line use: singlecomp outputname *.fasta
Compile with: g++ -O3 singlecomp.cpp -o singlecomp
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
using std::string;

int main(int argc, char** argv) {
  if (argc<3)
    printf("To compress FASTA use: singlecomp outputname *.fasta\n"), exit(1);
  FILE *out=fopen(argv[1], "wb");
string label=string(argv[1])+".lb";
  FILE *outp=fopen(label.c_str(), "w");
  int b=1, c;
  int cnt=0,total=0;
  int ct=0;
  for (int i=2; i<argc; ++i) {
    printf("%s\n", argv[i]);
    FILE *in=fopen(argv[i], "rb");
    if (!in) continue;
    bool dna=true;
    while ((c=getc(in))!=EOF) {
      if (c=='>') dna=false; 
      else if (c==10) {if(!dna){dna=true,putc('\n', outp);}cnt--;}
      if (dna) {++cnt;
        if (c!='N'&&ct!=0&&c!=10){putc('#', outp);while(ct>254){putc(254, outp),ct=ct-254;}putc(ct, outp),putc('\n', outp), ct=0;}
        if (c=='A') b=b*4;
        if (c=='C') b=b*4+1;
        if (c=='G') b=b*4+2;
        if (c=='T') b=b*4+3;
	if (c=='N'||c=='-') {if (ct==0){total=cnt;
        while(total>254){putc(254, outp);total=total-254;}
        putc(total, outp);++ct;}else{ ++ct;}}
        if (b>=256) putc(b&255, out), b=1;
        
      }
      else if (!dna) putc(c, outp);
    }
    if (in) fclose(in);
  }
  fclose(out);
  fclose(outp);
 // fclose(outs);
  return 0;
}


