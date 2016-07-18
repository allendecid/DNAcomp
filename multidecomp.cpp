/* Copyright (c) 2016 allendecid

Command line use: multidecomp fastafile compressedfile
Compile with: g++ -O3 multidecomp.cpp -o multidecomp
*/

#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include <vector>
using namespace std;
using std::string;
int decimal_binary(int n);
int main(int argc, char** argv) { 


  if (argc<3) // if the input or output file are missing
    printf("To decompress FASTA: multidecomp fastafile compressedfile\n"), exit(1); // exit
  FILE *out=fopen(argv[1], "w"); //* pointer to some location argv1 is outputfile

  int b=1, c, n, d;
  int base=0;
  int lop=0;
  int j;
  int ct=0;
  char buffer[50], buff[10];
  char *token,*loc;
  char const *search = " ";
  int ret;
  char *output = NULL;
  vector <int> example; // pos N and ammount
  vector <int> newseq; // pos seq id >
  vector <int> resta; // last nn for seq
  std::vector<std::string> v; // seq id >
  std::vector<std::string> vbw; // lasr nn

  for (int i=2; i<argc; ++i) {
    printf("%s\n", argv[i]);// input file
    FILE *in=fopen(argv[i], "rb");
    string input=string(argv[i])+".lb";
    string bw=string(argv[i])+".bw";
    FILE *ind=fopen(input.c_str(), "r");
    FILE *inb=fopen(bw.c_str(), "r");
    char *strbw;
    int addbw=0,noflw=0;
    char m[]=">";
    char s[]=" ";
    int cuenta=1;
    int indx=-1;
    if (!in) continue;
    while (EOF != fscanf(inb, "%10[^\n]\n", buff))
    {     output = strstr (buff,s);if(output) {
          strtok_r (buff, " ", &loc);
           vbw.push_back(buff);
           resta.push_back(atoi(loc)),++indx;}
           else{
                newseq.push_back(atoi(buff));
               }   
    }
    bool dna,switc=true;
    while (EOF != fscanf(ind, "%50[^\n]\n", buffer))
    {   output = strstr (buffer,m);if(output) {
    v.push_back(buffer);
}else{

           strtok_r (buffer, " ", &loc);
        
           example.push_back(atoi(buffer));
           example.push_back(atoi(loc));++noflw;}
      
    }
   fprintf(out, "%s\n", v[0].c_str());
   bool insseq=false; // ask to insert seq
   bool over=false;
   
    while ((c=getc(in))!=EOF) {  
       
        ++ct;
       
	for (i=0; i<4; ++i) { ++base;

if((newseq[cuenta]-resta[cuenta-1])==base){
             if(resta[cuenta-1]>0){fprintf(out, "%s", vbw[cuenta-1].c_str());base=base+resta[cuenta-1];}}  
           if(example[lop]+resta[cuenta-1]+1==base){
            if(newseq[cuenta]-resta[cuenta-1]-example[lop+1]==base){
             if(resta[cuenta-1]>0){fprintf(out, "%s", vbw[cuenta-1].c_str());base=base+resta[cuenta-1];}}}  
            
            if(newseq[cuenta]==base){fprintf(out, "\n%s\n", v[cuenta].c_str()),++cuenta;++base;}

        
            if(example[lop]==base){base=base+example[lop+1];if(newseq[cuenta]==base){insseq=true;}
            for (j=0; j<example[lop+1]; ++j){if((j+1)%80==0){putc('\n', out);}putc('N', out);}lop=lop+2;}
            if(insseq){fprintf(out, "\n%s\n", v[cuenta].c_str());++base;++cuenta;if (example[lop]==base){base=base+example[lop+1];for (j=0; j<example[lop+1]; ++j){if((j+1)%80==0){putc('\n', out);}putc('N', out);}lop=lop+2;} insseq=false;}
            int t=(c>>(6-2*i))&3;
            putc("ACGT"[t], out);
	}
        if (ct==20){ putc('\n', out);ct=0;} // add column
    }       if(resta[indx]>0){ // last seq
            fprintf(out, "%s",vbw[indx].c_str());}

            if(noflw>(lop/2)){ // last seq
            for (j=0; j<example[lop+1]; ++j){if((j+1)%80==0){putc('\n', out);}putc('N', out);}}  
   // free(buffer);
    if (in) fclose(in);
    if (ind) fclose(ind);
    if (inb) fclose(inb);
  }
  fclose(out);
 // printf("%c", base);
  return 0;

}

