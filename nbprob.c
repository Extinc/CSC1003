#include <stdio.h>
#include "nbprob.h"

// =============================================================================
// Prior Probability
// =============================================================================
void *priorprobcalc(Features *dataset, struct FeatureSet *probresult, unsigned int rowcount)
{
    //struct FeatureSet *probresult;
    unsigned int normcount = 0; // normal count
    unsigned int altcount = 0;  // altered count
    // Calculate  & Store the probability back to the result
    for (int i = 0; i < rowcount; i++)
    {
        normcount = dataset[i].semen_diag == NORMAL_YES ? normcount + 1 : normcount;
        altcount = dataset[i].semen_diag == ALTERED_NO ? altcount + 1 : altcount;
    }

    probresult->prob_normal = (double)normcount / rowcount;
    probresult->prob_altered = (double)altcount / rowcount;
    probresult->normal_count = normcount;
    probresult->altered_count = altcount;
    return 0;
}

// =============================================================================
// Conditional Probability
// =============================================================================

void *cpcalc(Features *dataset, struct FeatureSet *priorprob, Probability *resultset, unsigned int rowcount)
{
    struct FeatureSet temp = *priorprob;
    //resultset = inittozero(); // Initialize resultset
    int normcount = 0;
    int altcount = 0;
    // ==============================
    // Normal & Altered counter
    // ============================== 
    normcount = temp.normal_count;
    altcount = temp.altered_count;
    resultset->semen_diagnosis = temp;
    for (int i = 0; i < rowcount; i++)
    {
        if (dataset[i].semen_diag == NORMAL_YES)
        {
            if (dataset[i].seasons == WINTER)
            {
                resultset->winter.normal_count += 1;
            }
            else if (dataset[i].seasons == (float)SPRING)
            {
                resultset->spring.normal_count += 1;
            }
            else if (dataset[i].seasons == (float)SUMMER)
            {
                resultset->summer.normal_count += 1;
            }
            else if (dataset[i].seasons == (float)FALL)
            {
                resultset->fall.normal_count += 1;
            }
            // ==============================
            if (dataset[i].childish_disease == NORMAL_YES)
            {
                resultset->cdisease_yes.normal_count += 1;
            }
            else
            {
                resultset->cdisease_no.normal_count += 1;
            }
            // ==============================
            if (dataset[i].trauma == NORMAL_YES)
            {
                resultset->accidenttrauma_yes.normal_count += 1;
            }
            else
            {
                resultset->accidenttrauma_no.normal_count += 1;
            }
            // ==============================
            if (dataset[i].surgical == NORMAL_YES)
            {
                resultset->surgical_yes.normal_count += 1;
            }
            else
            {
                resultset->surgical_no.normal_count += 1;
            }
            // ==============================
            if (dataset[i].high_fever == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.normal_count += 1;
            }
            else if (dataset[i].high_fever == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.normal_count += 1;
            }
            else if (dataset[i].high_fever == HIGH_FEVER_NO)
            {
                resultset->highfever_none.normal_count += 1;
            }
            // ==============================
            if (dataset[i].alc_consumpfreq == SERVERAL_A_DAY)
            {
                resultset->freqalch_std.normal_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == EVERY_DAY)
            {
                resultset->freqalch_every.normal_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == SERVERAL_A_WEEK)
            {
                resultset->freqalch_stw.normal_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == ONCE_A_WEEK)
            {
                resultset->freqalch_oaw.normal_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == HARDLY_NEVER)
            {
                resultset->freqalch_hardly.normal_count += 1;
            }

            // ==============================

            if (dataset[i].smoking_habit == SH_NEVER)
            {
                resultset->smokehabit_never.normal_count += 1;
            }
            else if (dataset[i].smoking_habit == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.normal_count += 1;
            }
            else if (dataset[i].smoking_habit == SH_DAILY)
            {
                resultset->smokehabit_daily.normal_count += 1;
            }

            // ==============================
            resultset->ageanalysis.sum_normal += dataset[i].ageanalysis;
            resultset->ageanalysis.normal_count += 1;
            resultset->numhrsit_ptable.sum_normal += dataset[i].numhrsit_pertable;
            resultset->numhrsit_ptable.normal_count += 1;
        }
        else
        {
            if (dataset[i].seasons == WINTER)
            {
                resultset->winter.altered_count += 1;
            }
            else if (dataset[i].seasons == (float)SPRING)
            {
                resultset->spring.altered_count += 1;
            }
            else if (dataset[i].seasons == (float)SUMMER)
            {
                resultset->summer.altered_count += 1;
            }
            else if (dataset[i].seasons == (float)FALL)
            {
                resultset->fall.altered_count += 1;
            }
            // ==============================
            if (dataset[i].childish_disease == NORMAL_YES)
            {
                resultset->cdisease_yes.altered_count += 1;
            }
            else
            {
                resultset->cdisease_no.altered_count += 1;
            }
            // ==============================
            if (dataset[i].trauma == NORMAL_YES)
            {
                resultset->accidenttrauma_yes.altered_count += 1;
            }
            else
            {
                resultset->accidenttrauma_no.altered_count += 1;
            }
            // ==============================
            if (dataset[i].surgical == NORMAL_YES)
            {
                resultset->surgical_yes.altered_count += 1;
            }
            else
            {
                resultset->surgical_no.altered_count += 1;
            }
            // ==============================
            if (dataset[i].high_fever == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.altered_count += 1;
            }
            else if (dataset[i].high_fever == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.altered_count += 1;
            }
            else if (dataset[i].high_fever == HIGH_FEVER_NO)
            {

                resultset->highfever_none.altered_count += 1;
            }
            // ==============================
            if (dataset[i].alc_consumpfreq == SERVERAL_A_DAY)
            {
                resultset->freqalch_std.altered_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == (float)EVERY_DAY)
            {
                resultset->freqalch_every.altered_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == (float)SERVERAL_A_WEEK)
            {
                resultset->freqalch_stw.altered_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == (float)ONCE_A_WEEK)
            {
                resultset->freqalch_oaw.altered_count += 1;
            }
            else if (dataset[i].alc_consumpfreq == HARDLY_NEVER)
            {
                resultset->freqalch_hardly.altered_count += 1;
            }

            // ==============================

            if (dataset[i].smoking_habit == SH_NEVER)
            {

                resultset->smokehabit_never.altered_count += 1;
            }
            else if (dataset[i].smoking_habit == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.altered_count += 1;
            }
            else if (dataset[i].smoking_habit == SH_DAILY)
            {
                resultset->smokehabit_daily.altered_count += 1;
            }
            // ==============================
            resultset->ageanalysis.sum_altered += dataset[i].ageanalysis;
            resultset->ageanalysis.altered_count += 1;

            resultset->numhrsit_ptable.sum_altered += dataset[i].numhrsit_pertable;
            resultset->numhrsit_ptable.altered_count += 1;
        }
    }

    // ==============================
    // Probability - Normal
    // ==============================
    //
    resultset->winter.prob_normal = (double)(resultset->winter.normal_count + ALPHA) / ((normcount + (4 * ALPHA)));
    resultset->spring.prob_normal = (double)(resultset->spring.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->summer.prob_normal = (double)(resultset->summer.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->fall.prob_normal = (double)(resultset->fall.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->cdisease_yes.prob_normal = (double)(resultset->cdisease_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->cdisease_no.prob_normal = (double)(resultset->cdisease_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->accidenttrauma_yes.prob_normal = (double)(resultset->accidenttrauma_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->accidenttrauma_no.prob_normal = (double)(resultset->accidenttrauma_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_yes.prob_normal = (double)(resultset->surgical_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_no.prob_normal = (double)(resultset->surgical_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    //
    resultset->highfever_lttm.prob_normal = (double)(resultset->highfever_lttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_mttm.prob_normal = (double)(resultset->highfever_mttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_none.prob_normal = (double)(resultset->highfever_none.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    //
    resultset->freqalch_std.prob_normal = (double)(resultset->freqalch_std.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_every.prob_normal = (double)(resultset->freqalch_every.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_stw.prob_normal = (double)(resultset->freqalch_stw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_oaw.prob_normal = (double)(resultset->freqalch_oaw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalch_hardly.prob_normal = (double)(resultset->freqalch_hardly.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    //
    resultset->smokehabit_never.prob_normal = (double)(resultset->smokehabit_never.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_normal = (double)(resultset->smokehabit_occ.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_normal = (double)(resultset->smokehabit_daily.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->ageanalysis.mean_normal = (double)(resultset->ageanalysis.sum_normal) / (normcount);
    resultset->numhrsit_ptable.mean_normal = (double)(resultset->numhrsit_ptable.sum_normal) / (normcount);


    // ==============================
    // Probability - Altered
    // // ==============================

    resultset->winter.prob_altered = (double)(resultset->winter.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->spring.prob_altered = (double)(resultset->spring.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->summer.prob_altered = (double)(resultset->summer.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->fall.prob_altered = (double)(resultset->fall.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->cdisease_yes.prob_altered = (double)(resultset->cdisease_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->cdisease_no.prob_altered = (double)(resultset->cdisease_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->accidenttrauma_yes.prob_altered = (double)(resultset->accidenttrauma_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->accidenttrauma_no.prob_altered = (double)(resultset->accidenttrauma_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_yes.prob_altered = (double)(resultset->surgical_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_no.prob_altered = (double)(resultset->surgical_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->highfever_lttm.prob_altered = (double)(resultset->highfever_lttm.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->highfever_mttm.prob_altered = (double)(resultset->highfever_mttm.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->highfever_none.prob_altered = (double)(resultset->highfever_none.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->freqalch_std.prob_altered = (double)(resultset->freqalch_std.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_every.prob_altered = (double)(resultset->freqalch_every.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_stw.prob_altered = (double)(resultset->freqalch_stw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_oaw.prob_altered = (double)(resultset->freqalch_oaw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalch_hardly.prob_altered = (double)(resultset->freqalch_hardly.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->smokehabit_never.prob_altered = (double)(resultset->smokehabit_never.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_altered = (double)(resultset->smokehabit_occ.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_altered = (double)(resultset->smokehabit_daily.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->ageanalysis.mean_altered = (double)(resultset->ageanalysis.sum_altered) / (altcount);
    resultset->numhrsit_ptable.mean_altered = (double)(resultset->numhrsit_ptable.sum_altered ) / (altcount);


    for (int j = 0; j < rowcount; j++)
    {
        if (dataset[j].semen_diag == NORMAL_YES)
        {
            resultset->ageanalysis.var_normal += pow((dataset[j].ageanalysis - (resultset->ageanalysis.mean_normal)), 2);
            resultset->numhrsit_ptable.var_normal += pow((dataset[j].numhrsit_pertable - (resultset->numhrsit_ptable.mean_normal)), 2);
        }
        else if (dataset[j].semen_diag == ALTERED_NO)
        {
            resultset->ageanalysis.var_altered += pow((dataset[j].ageanalysis - (resultset->ageanalysis.mean_altered)), 2);
            resultset->numhrsit_ptable.var_altered += pow((dataset[j].numhrsit_pertable - (resultset->numhrsit_ptable.mean_altered)), 2);
        }
    }
    resultset->ageanalysis.var_normal /= (double)(normcount );
    resultset->numhrsit_ptable.var_normal /= (double)(normcount );
    resultset->ageanalysis.var_altered /= (double)(altcount );
    resultset->numhrsit_ptable.var_altered /= (double)(altcount );
    return 0;
}

// =============================================================================
// Posterior Probability
// =============================================================================
void *postprobcalc(Features *dataset, struct FeatureSet *fsetdatas, Probability *probdataset, Probability_Err *resultset, unsigned int rowcount)
{
    Probability probdatas = *probdataset;
    //Probability_Err *resultset = (Probability_Err *)malloc(rowcount * sizeof(Probability_Err));
    double tempprob_normal = 0, tempprob_altered = 0;
    double tempgauss_age = 0, tempgauss_hrs = 0;
    //int err_count = 0;
    int i = 0;
    for (i = 0; i < rowcount; i++)
    {
        tempprob_normal = 1;
        tempprob_altered = 1;

        if (dataset[i].seasons == WINTER)
        {
            tempprob_normal = tempprob_normal * probdatas.winter.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.winter.prob_altered;
        }
        else if (dataset[i].seasons == (float)SPRING)
        {
            tempprob_normal = tempprob_normal * probdatas.spring.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.spring.prob_altered;
        }
        else if (dataset[i].seasons == (float)SUMMER)
        {
            tempprob_normal = tempprob_normal * probdatas.summer.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.summer.prob_altered;
        }
        else if (dataset[i].seasons == (float)FALL)
        {
            tempprob_normal *= probdatas.fall.prob_normal;
            tempprob_altered *= probdatas.fall.prob_altered;
        }
        // ==============================
        if (dataset[i].childish_disease == NORMAL_YES)
        {
            tempprob_normal *= probdatas.cdisease_yes.prob_normal;
            tempprob_altered *= probdatas.cdisease_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.cdisease_no.prob_normal;
            tempprob_altered *= probdatas.cdisease_no.prob_altered;
        }
        // ==============================
        if (dataset[i].trauma == NORMAL_YES)
        {
            tempprob_normal *= probdatas.accidenttrauma_yes.prob_normal;
            tempprob_altered *= probdatas.accidenttrauma_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.accidenttrauma_no.prob_normal;
            tempprob_altered *= probdatas.accidenttrauma_no.prob_altered;
        }
        // ==============================

        if (dataset[i].surgical == NORMAL_YES)
        {
            tempprob_normal *= probdatas.surgical_yes.prob_normal;
            tempprob_altered *= probdatas.surgical_yes.prob_altered;
        }
        else
        {
            tempprob_normal *= probdatas.surgical_no.prob_normal;
            tempprob_altered *= probdatas.surgical_no.prob_altered;
        }

        // ==============================

        if (dataset[i].high_fever == HIGH_FEVER_LESSTHAN)
        {
            tempprob_normal *= probdatas.highfever_lttm.prob_normal;
            tempprob_altered *= probdatas.highfever_lttm.prob_altered;
        }
        else if (dataset[i].high_fever == HIGH_FEVER_MORETHAN)
        {
            tempprob_normal *= probdatas.highfever_mttm.prob_normal;
            tempprob_altered *= probdatas.highfever_mttm.prob_altered;
        }
        else if (dataset[i].high_fever == HIGH_FEVER_NO)
        {
            tempprob_normal *= probdatas.highfever_none.prob_normal;
            tempprob_altered *= probdatas.highfever_none.prob_altered;
        }

        // ==============================
        if (dataset[i].alc_consumpfreq == (float)SERVERAL_A_DAY)
        {
            tempprob_normal *= probdatas.freqalch_std.prob_normal;
            tempprob_altered *= probdatas.freqalch_std.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == (float)EVERY_DAY)
        {
            tempprob_normal *= probdatas.freqalch_every.prob_normal;
            tempprob_altered *= probdatas.freqalch_every.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == (float)SERVERAL_A_WEEK)
        {
            tempprob_normal *= probdatas.freqalch_stw.prob_normal;
            tempprob_altered *= probdatas.freqalch_stw.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == ONCE_A_WEEK)
        {
            tempprob_normal *= probdatas.freqalch_oaw.prob_normal;
            tempprob_altered *= probdatas.freqalch_oaw.prob_altered;
        }
        else if (dataset[i].alc_consumpfreq == HARDLY_NEVER)
        {
            tempprob_normal *= probdatas.freqalch_hardly.prob_normal;
            tempprob_altered *= probdatas.freqalch_hardly.prob_altered;
            // printf("\n TEST a5 : %lf ", probdatas.freqalch_hardly.prob_normal);
        }

        // ==============================

        if (dataset[i].smoking_habit == SH_NEVER)
        {
            tempprob_normal *= probdatas.smokehabit_never.prob_normal;
            tempprob_altered *= probdatas.smokehabit_never.prob_altered;
            // printf("\n TEST sh1 : %lf ", probdatas.smokehabit_never.prob_normal);
        }
        else if (dataset[i].smoking_habit == SH_OCCASIONALLY)
        {
            tempprob_normal *= probdatas.smokehabit_occ.prob_normal;
            tempprob_altered *= probdatas.smokehabit_occ.prob_altered;
            // printf("\n TEST sh2 : %lf ", probdatas.smokehabit_occ.prob_normal);
        }
        else if (dataset[i].smoking_habit == SH_DAILY)
        {
            tempprob_normal *= probdatas.smokehabit_daily.prob_normal;
            tempprob_altered *= probdatas.smokehabit_daily.prob_altered;
        }

        // ==============================

        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_normal, probdatas.ageanalysis.var_normal, dataset[i].ageanalysis);
        tempprob_normal *= tempgauss_age;
        tempgauss_hrs = gaussiancalc(probdatas.numhrsit_ptable.mean_normal, probdatas.numhrsit_ptable.var_normal, dataset[i].numhrsit_pertable);
        tempprob_normal *= tempgauss_hrs;
        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_altered, probdatas.ageanalysis.var_altered, dataset[i].ageanalysis);
        tempprob_altered *= tempgauss_age;
        tempgauss_hrs = gaussiancalc(probdatas.numhrsit_ptable.mean_altered, probdatas.numhrsit_ptable.var_altered, dataset[i].numhrsit_pertable);
        tempprob_altered *= tempgauss_hrs;
        resultset[i].actual_nora = dataset[i].semen_diag;
        tempprob_normal =(tempprob_normal * fsetdatas->prob_normal) / (tempprob_altered + tempprob_normal);
        tempprob_altered = (tempprob_altered * fsetdatas->prob_altered)/ (tempprob_altered + tempprob_normal);
        // printf("\nROW : %d\tINDEX: %d\t tempnormal : %.9lf\t tempaltered : %.9lf", rowcount, i, tempprob_normal, tempprob_altered);
        // printf("\nROW : %d\tINDEX: %d\tactual_nora : %d", rowcount, i, resultset[i].actual_nora);
        if (tempprob_normal >= tempprob_altered)
        {
            resultset[i].predicted_nora = 0;
        }
        else
        {
            resultset[i].predicted_nora = 1;
        }

        resultset[i].prob_normal = tempprob_normal;
        resultset[i].prob_altered = tempprob_altered;
    }
    return 0;
}

// =============================================================================
// Error Probability :
// =============================================================================
void *cmatrix(Probability_Err *postprobdata, struct Confusion_Matrix *resultset, unsigned int rowcount, unsigned int index)
{
    int i;
    resultset[index].data_count = rowcount;
    resultset[index].true_pos = 0;
    resultset[index].true_neg = 0;
    resultset[index].false_pos = 0;
    resultset[index].false_neg = 0;
    resultset[index].prob_error = 0;

    for (i = 0; i < rowcount; i++)
    {
        if (postprobdata[i].actual_nora == postprobdata[i].predicted_nora)
        {
            if (postprobdata[i].actual_nora == 1 && postprobdata[i].predicted_nora == 1)
            {
                resultset[index].true_pos += 1;
            }
            else if (postprobdata[i].actual_nora == 0 && postprobdata[i].predicted_nora == 0)
            {
                resultset[index].true_neg += 1;
            }
        }
        else
        {
            if (postprobdata[i].actual_nora == 0 && postprobdata[i].predicted_nora == 1)
            {
                resultset[index].false_pos += 1;
            }

            if (postprobdata[i].actual_nora == 1 && postprobdata[i].predicted_nora == 0)
            {
                resultset[index].false_neg += 1;
            }
            resultset[index].prob_error += 1;
        }
    }
    resultset[index].prob_error /= (float)rowcount;
    return 0;
}
// =============================================================================
// Gaussian Formula
// =============================================================================
double gaussiancalc(double mean, double variance, double xval)
{
    double result = 0;
    double zscore = (xval - mean);
    result = (1 / sqrt(2 * PI)) * exp(-1 * (pow(zscore, 2) / (2 * variance)));
    return result;
}
