#ifndef NBDATA_H
#define NBDATA_H
#define MAX 100
#include <stdio.h>
#include "nbstruct.h"
#include <math.h>
features *storeData(FILE *ifp, char *fpath, int len);
//void splitData(features data[], features trg[], features test[], unsigned int trgdatarows);
void setfeatureindex(Probability resultset[]);
Probability *inittozero();
int countlength(FILE *ifp, char *fpath);
#endif