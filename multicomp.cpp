/* Copyright (c) 2016 allendecid

Command line use: multicomp outputname *.fasta
Compile with: g++ -O3 multicomp.cpp -o multicomp
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
using std::string;

int main(int argc, char** argv) {
  if (argc<3)
    printf("To compress FASTA use: multicomp outputname *.fasta\n"), exit(1);
  FILE *out=fopen(argv[1], "wb");
  string label=string(argv[1])+".lb";
  string bw=string(argv[1])+".bw";
 // strcpy(filename, ".lb"); 
  FILE *outp=fopen(label.c_str(), "w");
  FILE *outb=fopen(bw.c_str(), "w");
  //FILE *outs=fopen("spaces", "wb");
  int b=1, c;
  int cnt=0,total=0;
  int ct=0,lim=0,fill=0;
  char end[5];
  for (int i=2; i<argc; ++i) {
    printf("%s\n", argv[i]);
    FILE *in=fopen(argv[i], "rb");
    if (!in) continue;
    bool dna=true,init=false;
    while ((c=getc(in))!=EOF) {
      if (c=='>') {dna=false;lim=0; if(ct!=0){putc(' ', outp),
                              fprintf(outp, "%d", ct),putc('\n', outp),ct=0;}
                              if(init){cnt++;if(fill==0){fprintf(outb, "0  0\n");}else{fprintf(outb, "%s %d\n", end,fill), b=1,fill=0,memset(&end[0], 0, sizeof(end));}}fprintf(outb, "%d\n", cnt);init=true;}
      else if (c==10) {if(!dna){dna=true,putc('\n', outp);}cnt--;}
      if (dna) {++cnt;
        if (c!='N'&&ct!=0&&c!=10){putc(' ', outp),fprintf(outp, "%d", ct),putc('\n', outp), ct=0;}
        if (c=='A') b=b*4,end[fill]='A',++fill;
        if (c=='C') b=b*4+1,end[fill]='C',++fill;
        if (c=='G') b=b*4+2,end[fill]='G',++fill;
        if (c=='T') b=b*4+3,end[fill]='T',++fill;
	if (c=='N'||c=='-') {if (ct==0){fprintf(outp, "%d", cnt),++ct;}else{ ++ct;}}
        if (b>=256) putc(b&255, out), b=1,fill=0,memset(&end[0], 0, sizeof(end));
        
      }
      else if (!dna&&lim<30) putc(c, outp),++lim;
    }if(ct!=0){putc(' ', outp),fprintf(outp, "%d", ct),putc('\n', outp);}
     if(b!=1){fprintf(outb, "%s %d", end,fill);}
    if (in) fclose(in);
  }
  fclose(out);
  fclose(outp);
  fclose(outb);
 // fclose(outs);
  return 0;
}


