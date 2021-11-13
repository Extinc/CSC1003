#ifndef ___NBDATA__
#define ___NBDATA__
#define MAX 100
#include <stdio.h>
#include "nbstruct.h"
#include <math.h>
Features *storeData(FILE *ifp, char *fpath, int len);
//void splitData(Features data[], Features trg[], Features test[], unsigned int trgdatarows);
void setfeatureindex(Probability resultset[]);
Probability *inittozero();
int countlength(FILE *ifp, char *fpath);
#endif