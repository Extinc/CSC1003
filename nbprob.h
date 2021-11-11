#ifndef ___nbprob__
#define ___nbprob__
#include "nbstruct.h"
#include "nbdata.h"

void *priorprobcalc(features *dataset, struct FeatureSet *probresult, unsigned int rowcount);
void *cpcalc(features *dataset, struct FeatureSet *priorprob, Probability *resultset, unsigned int rowcount);
void *postprobcalc(features *dataset, Probability *probdataset, Probability_Err *resultset, unsigned int rowcount);
void *cmatrix(Probability_Err *postprobdata, Confusion_Matrix *resultset, unsigned int rowcount, unsigned int index);
double gaussiancalc(double mean, double variance, double xval);
#endif