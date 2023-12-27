#ifndef __ENCDEC_H
#define __ENCDEC_H


int appEncode(char *input, char *output);
int appDecode(char *input, char *output);
int dataEncode(char *input, char *output);
int dataDecode(char *input, char *output);
int phyEncode(char *input, char *output);
int phyDecode(char *input, char *output);

void toUpperString(char *input, char *output);

int appService(char *input, char *output,int encode);
int dataService(char *input, char *output,int encode);
int phyService(char *input, char *output, int encode);

#endif
