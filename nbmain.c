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

void plot_array(Confusion_Matrix_Type *cmatrixdata, int n);
//Probability condprobinit;
int main(void);
int main(void)
{

    printf(" SIZE : %lu", sizeof(Features));
    FILE *fp;
    unsigned int flen = 0;     // num of line in file
    unsigned int trgcount = 0; // Number of Training Data
    unsigned int tstcount = 0; // Number of Test Data
    unsigned short datasetcounter = 0;
    float timespent;                                                     // Store execution time
    Features *fddata;                                                    // Fertility Diangnosis Data
    Features *tempfdata;                                                 // Temp Storage for Fertility Diangnosis Data
    struct FeatureSet *priorprobres = malloc(sizeof(struct FeatureSet)); // Prior Probability
    if (priorprobres == NULL)
    {
        printf("Memory not allocated");
    }
    Probability *condprobres = calloc(1, sizeof(Probability)); // Conditional Probability
    if (condprobres == NULL)
    {
        printf("Memory not allocated");
    }

    Probability_Err *postprob;                                                     // Posterior Probability
    Confusion_Matrix_Type *cmatrixdata = calloc(1, sizeof(Confusion_Matrix_Type)); // Confusion Matrix Allocate memory and Initialize all to zero within struct
    if (cmatrixdata == NULL)
    {
        printf("Memory not allocated");
    }

    char *fpath = "fertility_Diagnosis_Data_Group9_11.txt"; // File Path
    // ------------------------------------------------------------------------------------------------
    clock_t tstart = clock();      // START TIMER
    flen = countlength(fp, fpath); // store the length count
    fddata = storeData(fp, fpath, flen);
    // ------------------------------------------------------------------------------------------------
    postprob = (Probability_Err *)malloc(flen * sizeof(Probability_Err)); // Allocate memory for posterior probabiliy
    if (postprob == NULL)
    {
        printf("Memory not allocated");
    }
    while (datasetcounter < 5)
    {
        // To calculate the Training Ratio based on file length
        trgcount = flen * (1 - ((datasetcounter + 1) / 10.));

        if (trgcount >= (flen * 0.5) && trgcount <= (flen * 0.9))
        {
            tstcount = flen - trgcount;

            memset(condprobres, 0, sizeof(Probability));

            memset(postprob, 0, flen * sizeof(Probability_Err));
            //Prior Probability Calculate function call : (TRAINING DATA)
            priorprobcalc(fddata, priorprobres, trgcount);

            //Conditional Probability Calculate function call : (TRAINING DATA)
            cpcalc(fddata, priorprobres, condprobres, trgcount);

            //Posterior Probability Calculation Function call : (Training Data)
            postprobcalc(fddata, priorprobres, condprobres, postprob, trgcount);

            // Confusion Matrix
            cmatrix(postprob, cmatrixdata->trg_cmatrix, trgcount, datasetcounter);

            // Temp storage to get test data
            tempfdata = fddata + trgcount;

            // Calculation for test data :
            postprobcalc(tempfdata, priorprobres, condprobres, postprob, tstcount);

            cmatrix(postprob, cmatrixdata->tst_cmatrix, tstcount, datasetcounter);
        }
        datasetcounter++;
    }


    free(priorprobres);
    free(fddata);
    free(condprobres);
    free(postprob);
    // ------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------------------------
    // PRINT OUT FOR CONFUSION MATRIX : // POSITIVE : NOT NORMAL    NEGATIVE : NORMAL
    // ------------------------------------------------------------------------------------------------

    for (int i = 0; i < 5; i++)
    {
        printf("\n=========================================================================");
        printf("\n||                          TRAINING DATA                              ||");
        printf("\n||                                %d                                   ||", cmatrixdata->trg_cmatrix[i].data_count);
        printf("\n=========================================================================");
        printf("\n                     ||    PREDICTED ALTERED        PREDICTED NORMAL  ");
        printf("\n---------------------||--------------------------------------------------");
        printf("\n    ACTUAL ALTERED   ||           TP : %d                FN : %d           ", cmatrixdata->trg_cmatrix[i].true_pos, cmatrixdata->trg_cmatrix[i].false_neg);
        printf("\n---------------------||--------------------------------------------------");
        printf("\n    ACTUAL NORMAL    ||           FP : %d                TN : %d          ", cmatrixdata->trg_cmatrix[i].false_pos, cmatrixdata->trg_cmatrix[i].true_neg);
        printf("\n=========================================================================");
        printf("\n  Prob error  :   %lf", cmatrixdata->trg_cmatrix[i].prob_error);
        printf("\n=========================================================================");
        printf("\n");
        printf("\n=========================================================================");
        printf("\n||                            TEST DATA                                ||");
        printf("\n||                                %d                                   ||", cmatrixdata->tst_cmatrix[i].data_count);
        printf("\n=========================================================================");
        printf("\n                     ||    PREDICTED ALTERED        PREDICTED NORMAL  ");
        printf("\n---------------------||--------------------------------------------------");
        printf("\n    ACTUAL ALTERED   ||           TP : %d                FN : %d           ", cmatrixdata->tst_cmatrix[i].true_pos, cmatrixdata->tst_cmatrix[i].false_neg);
        printf("\n---------------------||--------------------------------------------------");
        printf("\n    ACTUAL NORMAL    ||           FP : %d                TN : %d          ", cmatrixdata->tst_cmatrix[i].false_pos, cmatrixdata->tst_cmatrix[i].true_neg);
        printf("\n=========================================================================");
        printf("\n Prob error :   %lf", cmatrixdata->tst_cmatrix[i].prob_error);
        printf("\n=========================================================================");
    }
    plot_array(cmatrixdata, 5);

    free(cmatrixdata);
    // ------------------------------------------------------------------------------------------------

    // Functions end before timer end

    clock_t tend = clock();                              // STOP TIMER
    timespent = (float)(tend - tstart) / CLOCKS_PER_SEC; // Duration of app run
    printf("\n Time taken for the appication to run is %f seconds", timespent);
    return 0;
}

void plot_array(Confusion_Matrix_Type *cmatrixdata, int n)
{

    FILE *p = popen("gnuplot -persist", "w");
    fprintf(p, "set title 'Chart for Probability of Error' \n");
    fprintf(p, "set term qt font 'Arial,12' \n");
    fprintf(p, "set xlabel 'Sample Size' \n");             // Set X-axis Label
    fprintf(p, "set ylabel 'Probability of Error %%' \n"); // Set Y-axis Label
    fprintf(p, "set xrange [40:100] \n");                  // Set Y-axis Label
    fprintf(p, "set yrange [0:30] \n");                    // Set Y-axis Label
    // lp : linepoints lc: linecolor
    fprintf(p, "set format y '%%.2f' \n"); // Set Y-axis Label
    fprintf(p, "set style line 1 lc rgb 'blue' lt 1 lw 2 pt 6 \n"); // Set Y-axis Label
    fprintf(p, "set style line 2 lc rgb 'red' lt 1 lw 2 pt 6 \n");  // Set Y-axis Label

    double xval = 0;
    double yval = 0;
    if (p != NULL)
    {
        fprintf(p, "$TRGDATA << EOD\n");
        for (int i = 0; i < n; i++)
        {
            xval = cmatrixdata->trg_cmatrix[i].data_count;
            yval = cmatrixdata->trg_cmatrix[i].prob_error * 100;
            fprintf(p, "%g %g\n", xval, yval);
        }
        fprintf(p, "EOD\n");
        fprintf(p, "$TSTDATA << EOD\n");
        for (int k = n - 1; k > 0; k--)
        {
            xval = cmatrixdata->trg_cmatrix[k].data_count;
            yval = cmatrixdata->tst_cmatrix[k].prob_error * 100;
            // If Test Data
            fprintf(p, "%g %g\n", xval, yval);
        }
        fprintf(p, "EOD\n");
    }
    fprintf(p, "plot '$TRGDATA' with lp title 'Training Data' ls 1, '$TSTDATA' with lp title 'Test Data' ls 2\n");
    fflush(p);
    pclose(p);
}