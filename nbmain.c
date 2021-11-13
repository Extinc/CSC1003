// =============================================================================
// naivebayes.c
// Assignment main program 2 with structures
// 1003 grp????
// =============================================================================

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "nbstruct.h"
#include "nbdata.h"
#include "nbprob.h"

#define LEN(x) sizeof(x) / sizeof(x[0])

void plot_array(Confusion_Matrix *cmatrixdata, int flen, int n);
//Probability condprobinit;
int main(void);
int main(void)
{

    FILE *fp;
    unsigned int flen = 0;     // num of line in file
    unsigned int trgcount = 0; // Number of Training Data
    unsigned int tstcount = 0; // Number of Test Data
    unsigned short datasetcounter = 0;
    unsigned short cmatrixctr = 0;
    float timespent;                                                     // Store execution time
    Features *fddata;                                                    // Fertility Diangnosis Data
    Features *tempfdata;                                                 // Temp Storage for Fertility Diangnosis Data
    struct FeatureSet *priorprobres = malloc(sizeof(struct FeatureSet)); // Prior Probability
    if (priorprobres == NULL)
    {
        printf("Memory not allocated");
    }
    Probability *condprobres = calloc(1, sizeof(Probability)); //
    if (condprobres == NULL)
    {
        printf("Memory not allocated");
    }

    //Probability *condprobres = &condprobinit;
    // Conditional Probability
    Probability_Err *postprob;                              // Posterior Probability
    Confusion_Matrix cmatrixdata[10];                       // Confusion Matrix Array
    char *fpath = "fertility_Diagnosis_Data_Group9_11.txt"; // File Path
    // ------------------------------------------------------------------------------------------------
    clock_t tstart = clock();      // START TIMER
    flen = countlength(fp, fpath); // store the length count
    fddata = storeData(fp, fpath, flen);
    // ------------------------------------------------------------------------------------------------
    // First Set
    postprob = (Probability_Err *)malloc(flen * sizeof(Probability_Err));
    if (postprob == NULL)
    {
        printf("Memory not allocated");
        return 0;
    }
    while (datasetcounter < 10)
    {
        trgcount = flen * (1 - ((datasetcounter + 1) / 10.));

        if (trgcount >= (flen * 0.5f) && trgcount <= (flen * 0.9f))
        {
            tstcount = flen - trgcount;

            memset(condprobres, 0, sizeof(Probability));

            memset(postprob, 0, trgcount * sizeof(Probability_Err));
            //Prior Probability Calculate function call : (TRAINING DATA)
            priorprobcalc(fddata, priorprobres, trgcount);

            //Conditional Probability Calculate function call : (TRAINING DATA)
            cpcalc(fddata, priorprobres, condprobres, trgcount);

            //Posterior Probability Calculation Function call : (Training Data)
            postprobcalc(fddata, condprobres, postprob, trgcount);

            // Confusion Matrix
            cmatrix(postprob, cmatrixdata, trgcount, cmatrixctr);

            // Temp storage to get test data
            tempfdata = fddata + trgcount;

            // Calculation for test data :
            postprobcalc(tempfdata, condprobres, postprob, tstcount);

            cmatrix(postprob, cmatrixdata, tstcount, cmatrixctr + 1);
            if (trgcount == 50)
            {
                free(priorprobres);
                free(fddata);
                free(condprobres);
                free(postprob);

                break;
            }
        }
        cmatrixctr += 2;
        datasetcounter++;
    }
    // ------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------
    // PRINT OUT FOR CONFUSION MATRIX : // POSITIVE : NOT NORMAL    NEGATIVE : NORMAL
    // ------------------------------------------------------------------------------------------------

    // FILE *fp1;
    // fp1 = fopen("data.txt", "a");
    for (int i = 0; i < LEN(cmatrixdata); i++)
    {
        if (i < 11)
        {
            printf("\n=========================================================================");
            printf("\n                                  %d                                      ", cmatrixdata[i].data_count);
            printf("\n=========================================================================");
            printf("\n                     ||    PREDICTED ALTERED        PREDICTED NORMAL  ");
            printf("\n---------------------||--------------------------------------------------");
            printf("\n    ACTUAL ALTERED   ||           %d                         %d           ", cmatrixdata[i].true_pos, cmatrixdata[i].false_neg);
            printf("\n---------------------||--------------------------------------------------");
            printf("\n    ACTUAL NORMAL    ||           %d                         %d                 ", cmatrixdata[i].false_pos, cmatrixdata[i].true_neg);
            printf("\n=========================================================================");
            printf("\n Accuracy            : %lf   ||  Misclassification Rate  :   %lf", cmatrixdata[i].accuracy, cmatrixdata[i].misclass_rate);
            printf("\n True Positive Rate  : %lf   ||  False Positive Rate     :   %lf", cmatrixdata[i].true_posrate, cmatrixdata[i].false_posrate);
            printf("\n True Negative Rate  : %lf   ||  prob error              :   %lf", cmatrixdata[i].true_negrate, cmatrixdata[i].prob_error);
            printf("\n=========================================================================");
        }
        else
        {
            break;
        }
    }
    // fclose(fp1);
    plot_array(cmatrixdata, flen, 10);
    // ------------------------------------------------------------------------------------------------

    // Functions end before timer end

    clock_t tend = clock();                              // STOP TIMER
    timespent = (float)(tend - tstart) / CLOCKS_PER_SEC; // Duration of app run
    printf("\n Time taken for the appication to run is %f seconds", timespent);
    return 0;
}

void plot_array(Confusion_Matrix *cmatrixdata, int flen, int n)
{

    FILE *p = popen("gnuplot -persist", "w");
    fprintf(p, "set title 'Chart for Probability of Error' \n");
    fprintf(p, "set term qt font 'Arial,12' \n");
    fprintf(p, "set xlabel 'Test Cases' \n");
    fprintf(p, "set ylabel 'Probability of Error' \n");
    // lp : linepoints lc: linecolor
    fprintf(p, "plot '-' lc rgb '#199e27' with lp title 'Training Data' , '-' lc rgb 'blue' with lp title 'Test Data'\n");
    double xval = 0;
    double yval = 0;
    if (p != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            xval = cmatrixdata[i].data_count;
            yval = cmatrixdata[i].prob_error;
            if (xval >= (flen * 0.5))
            {
                if (i != 9)
                {
                    fprintf(p, "%lf %lf\n", xval, yval);
                    if (xval == (flen * 0.5))
                    {
                        break;
                    }
                }
            }
        }
        fprintf(p, "e\n");
        for (int k = 0; k < n; k++)
        {
            xval = cmatrixdata[k].data_count;
            yval = cmatrixdata[k].prob_error;
            if (xval <= (flen * 0.5))
            {
                if (k != 8)
                {
                    fprintf(p, "%lf %lf\n", xval, yval);
                    if (xval == (flen * 0.5))
                    {
                        break;
                    }
                }
            }
        }
        fprintf(p, "e\n");
    }

    fflush(p);
    pclose(p);
}