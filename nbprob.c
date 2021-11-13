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
        normcount = dataset[i].semendiagdata == NORMAL_YES ? normcount + 1 : normcount;
        altcount = dataset[i].semendiagdata == ALTERED_NO ? altcount + 1 : altcount;
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
        if (dataset[i].semendiagdata == NORMAL_YES)
        {
            if (dataset[i].soadata == WINTER)
            {
                resultset->winter.normal_count += 1;
            }
            else if (dataset[i].soadata == (float)SPRING)
            {
                resultset->spring.normal_count += 1;
            }
            else if (dataset[i].soadata == (float)SUMMER)
            {
                resultset->summer.normal_count += 1;
            }
            else if (dataset[i].soadata == (float)FALL)
            {
                resultset->fall.normal_count += 1;
            }
            // ==============================
            if (dataset[i].cddata == NORMAL_YES)
            {
                resultset->cdiseaseyes.normal_count += 1;
            }
            else
            {
                resultset->cdiseaseno.normal_count += 1;
            }
            // ==============================
            if (dataset[i].atdata == NORMAL_YES)
            {
                resultset->accidenttrauma_yes.normal_count += 1;
            }
            else
            {
                resultset->accidenttrauma_no.normal_count += 1;
            }
            // ==============================
            if (dataset[i].sidata == NORMAL_YES)
            {
                resultset->surgical_yes.normal_count += 1;
            }
            else
            {
                resultset->surgical_no.normal_count += 1;
            }
            // ==============================
            if (dataset[i].hfdata == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.normal_count += 1;
            }
            else if (dataset[i].hfdata == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.normal_count += 1;
            }
            else if (dataset[i].hfdata == HIGH_FEVER_NO)
            {
                resultset->highfever_none.normal_count += 1;
            }
            // ==============================
            if (dataset[i].alcconsumptdata == SERVERAL_A_DAY)
            {
                resultset->freqalchstd.normal_count += 1;
            }
            else if (dataset[i].alcconsumptdata == EVERY_DAY)
            {
                resultset->freqalchevery.normal_count += 1;
            }
            else if (dataset[i].alcconsumptdata == SERVERAL_A_WEEK)
            {
                resultset->freqalchstw.normal_count += 1;
            }
            else if (dataset[i].alcconsumptdata == ONCE_A_WEEK)
            {
                resultset->freqalchoaw.normal_count += 1;
            }
            else if (dataset[i].alcconsumptdata == HARDLY_NEVER)
            {
                resultset->freqalchhardly.normal_count += 1;
            }

            // ==============================

            if (dataset[i].shdata == SH_NEVER)
            {
                resultset->smokehabit_never.normal_count += 1;
            }
            else if (dataset[i].shdata == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.normal_count += 1;
            }
            else if (dataset[i].shdata == SH_DAILY)
            {
                resultset->smokehabit_daily.normal_count += 1;
            }

            // ==============================
            if (dataset[i].aoadata != 0)
            {
                resultset->ageanalysis.sum_normal += dataset[i].aoadata;
                resultset->ageanalysis.normal_count += 1;
            }
            if (dataset[i].numhrsitdata != 0)
            {
                resultset->numhrsitptable.sum_normal += dataset[i].numhrsitdata;
                resultset->numhrsitptable.normal_count += 1;
            }
        }
        else
        {
            if (dataset[i].soadata == WINTER)
            {
                resultset->winter.altered_count += 1;
            }
            else if (dataset[i].soadata == (float)SPRING)
            {
                resultset->spring.altered_count += 1;
            }
            else if (dataset[i].soadata == (float)SUMMER)
            {
                resultset->summer.altered_count += 1;
            }
            else if (dataset[i].soadata == (float)FALL)
            {
                resultset->fall.altered_count += 1;
            }
            // ==============================
            if (dataset[i].cddata == NORMAL_YES)
            {
                resultset->cdiseaseyes.altered_count += 1;
            }
            else
            {
                resultset->cdiseaseno.altered_count += 1;
            }
            // ==============================
            if (dataset[i].atdata == NORMAL_YES)
            {
                resultset->accidenttrauma_yes.altered_count += 1;
            }
            else
            {
                resultset->accidenttrauma_no.altered_count += 1;
            }
            // ==============================
            if (dataset[i].sidata == NORMAL_YES)
            {
                resultset->surgical_yes.altered_count += 1;
            }
            else
            {
                resultset->surgical_no.altered_count += 1;
            }
            // ==============================
            if (dataset[i].hfdata == HIGH_FEVER_LESSTHAN)
            {
                resultset->highfever_lttm.altered_count += 1;
            }
            else if (dataset[i].hfdata == HIGH_FEVER_MORETHAN)
            {
                resultset->highfever_mttm.altered_count += 1;
            }
            else if (dataset[i].hfdata == HIGH_FEVER_NO)
            {

                resultset->highfever_none.altered_count += 1;
            }
            // ==============================
            if (dataset[i].alcconsumptdata == SERVERAL_A_DAY)
            {
                resultset->freqalchstd.altered_count += 1;
            }
            else if (dataset[i].alcconsumptdata == (float)EVERY_DAY)
            {
                resultset->freqalchevery.altered_count += 1;
            }
            else if (dataset[i].alcconsumptdata == (float)SERVERAL_A_WEEK)
            {
                resultset->freqalchstw.altered_count += 1;
            }
            else if (dataset[i].alcconsumptdata == (float)ONCE_A_WEEK)
            {
                resultset->freqalchoaw.altered_count += 1;
            }
            else if (dataset[i].alcconsumptdata == HARDLY_NEVER)
            {
                resultset->freqalchhardly.altered_count += 1;
            }

            // ==============================

            if (dataset[i].shdata == SH_NEVER)
            {

                resultset->smokehabit_never.altered_count += 1;
            }
            else if (dataset[i].shdata == SH_OCCASIONALLY)
            {
                resultset->smokehabit_occ.altered_count += 1;
            }
            else if (dataset[i].shdata == SH_DAILY)
            {
                resultset->smokehabit_daily.altered_count += 1;
            }
            // ==============================
            resultset->ageanalysis.sum_altered += dataset[i].aoadata;
            resultset->ageanalysis.altered_count += 1;

            resultset->numhrsitptable.sum_altered += dataset[i].numhrsitdata;
            resultset->numhrsitptable.altered_count += 1;
        }
    }

    //normcount = normcount == 0 ? 0 : normcount;

    // ==============================
    // Probability - Normal
    // ==============================
    //normcount = temp.normal_count + (4 * ALPHA);
    resultset->winter.prob_normal = (double)(resultset->winter.normal_count + ALPHA) / ((normcount + (4 * ALPHA)));
    resultset->spring.prob_normal = (double)(resultset->spring.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->summer.prob_normal = (double)(resultset->summer.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->fall.prob_normal = (double)(resultset->fall.normal_count + ALPHA) / (normcount + (4 * ALPHA));
    resultset->cdiseaseyes.prob_normal = (double)(resultset->cdiseaseyes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->cdiseaseno.prob_normal = (double)(resultset->cdiseaseno.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->accidenttrauma_yes.prob_normal = (double)(resultset->accidenttrauma_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->accidenttrauma_no.prob_normal = (double)(resultset->accidenttrauma_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_yes.prob_normal = (double)(resultset->surgical_yes.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->surgical_no.prob_normal = (double)(resultset->surgical_no.normal_count + ALPHA) / (normcount + (2 * ALPHA));
    resultset->highfever_lttm.prob_normal = (double)(resultset->highfever_lttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_mttm.prob_normal = (double)(resultset->highfever_mttm.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->highfever_none.prob_normal = (double)(resultset->highfever_none.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->freqalchstd.prob_normal = (double)(resultset->freqalchstd.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalchevery.prob_normal = (double)(resultset->freqalchevery.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalchstw.prob_normal = (double)(resultset->freqalchstw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalchoaw.prob_normal = (double)(resultset->freqalchoaw.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->freqalchhardly.prob_normal = (double)(resultset->freqalchhardly.normal_count + ALPHA) / (normcount + (5 * ALPHA));
    resultset->smokehabit_never.prob_normal = (double)(resultset->smokehabit_never.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_normal = (double)(resultset->smokehabit_occ.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_normal = (double)(resultset->smokehabit_daily.normal_count + ALPHA) / (normcount + (3 * ALPHA));
    // resultset->ageanalysis.mean_normal = (double)(resultset->ageanalysis.sum_normal) / (resultset->ageanalysis.normal_count); // check if mean normal divide by total row or count of normal
    // resultset->numhrsitptable.mean_normal = (double)(resultset->numhrsitptable.sum_normal) / (resultset->numhrsitptable.normal_count);
    resultset->ageanalysis.mean_normal = (double)(resultset->ageanalysis.sum_normal + ALPHA) / (normcount + (1 * ALPHA)); // check if mean normal divide by total row or count of normal
    resultset->numhrsitptable.mean_normal = (double)(resultset->numhrsitptable.sum_normal + ALPHA) / (normcount + (1 * ALPHA));
    // ==============================
    // Probability - Altered
    // ==============================
    resultset->winter.prob_altered = (double)(resultset->winter.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->spring.prob_altered = (double)(resultset->spring.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->summer.prob_altered = (double)(resultset->summer.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->fall.prob_altered = (double)(resultset->fall.altered_count + ALPHA) / (altcount + (4 * ALPHA));
    resultset->cdiseaseyes.prob_altered = (double)(resultset->cdiseaseyes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->cdiseaseno.prob_altered = (double)(resultset->cdiseaseno.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->accidenttrauma_yes.prob_altered = (double)(resultset->accidenttrauma_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->accidenttrauma_no.prob_altered = (double)(resultset->accidenttrauma_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_yes.prob_altered = (double)(resultset->surgical_yes.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->surgical_no.prob_altered = (double)(resultset->surgical_no.altered_count + ALPHA) / (altcount + (2 * ALPHA));
    resultset->highfever_lttm.prob_altered = (double)(resultset->highfever_lttm.altered_count + ALPHA) / (altcount + (4 * ALPHA)) + (3. * ALPHA);
    resultset->highfever_mttm.prob_altered = (double)(resultset->highfever_mttm.altered_count + ALPHA) / (altcount + (4 * ALPHA)) + (3. * ALPHA);
    resultset->highfever_none.prob_altered = (double)(resultset->highfever_none.altered_count + ALPHA) / (altcount + (4 * ALPHA)) + (3. * ALPHA);
    resultset->freqalchstd.prob_altered = (double)(resultset->freqalchstd.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalchevery.prob_altered = (double)(resultset->freqalchevery.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalchstw.prob_altered = (double)(resultset->freqalchstw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalchoaw.prob_altered = (double)(resultset->freqalchoaw.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->freqalchhardly.prob_altered = (double)(resultset->freqalchhardly.altered_count + ALPHA) / (altcount + (5 * ALPHA));
    resultset->smokehabit_never.prob_altered = (double)(resultset->smokehabit_never.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_occ.prob_altered = (double)(resultset->smokehabit_occ.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    resultset->smokehabit_daily.prob_altered = (double)(resultset->smokehabit_daily.altered_count + ALPHA) / (altcount + (3 * ALPHA));
    // resultset->ageanalysis.mean_altered = (double)(resultset->ageanalysis.sum_altered) / resultset->ageanalysis.altered_count; // check if mean normal divide by total row or count of normal
    // resultset->numhrsitptable.mean_altered = (double)(resultset->numhrsitptable.sum_altered) / resultset->numhrsitptable.altered_count;
    resultset->ageanalysis.mean_altered = (double)(resultset->ageanalysis.sum_altered + ALPHA) / (altcount + (1 * ALPHA)); // check if mean normal divide by total row or count of normal
    resultset->numhrsitptable.mean_altered = (double)(resultset->numhrsitptable.sum_altered + ALPHA) / (altcount + (1 * ALPHA));
    for (int j = 0; j < rowcount; j++)
    {
        if (dataset[j].semendiagdata == NORMAL_YES)
        {
            resultset->ageanalysis.var_normal += pow((dataset[j].aoadata - resultset->ageanalysis.mean_normal), 2);
            resultset->numhrsitptable.var_normal += pow((dataset[j].numhrsitdata - resultset->numhrsitptable.mean_normal), 2);
        }
        else if (dataset[j].semendiagdata == ALTERED_NO)
        {
            resultset->ageanalysis.var_altered += pow((dataset[j].aoadata - resultset->ageanalysis.mean_altered), 2);
            resultset->numhrsitptable.var_altered += pow((dataset[j].numhrsitdata - resultset->numhrsitptable.mean_altered), 2);
        }
    }
    // resultset->ageanalysis.var_normal /= (double)(normcount - 1);
    // resultset->numhrsitptable.var_normal /= (double)(normcount - 1);

    // resultset->ageanalysis.var_altered = (double)resultset->ageanalysis.var_altered / (altcount - 1);
    // resultset->numhrsitptable.var_altered = (double)resultset->numhrsitptable.var_altered / (altcount - 1);

    resultset->ageanalysis.var_normal /= (double)(resultset->ageanalysis.normal_count - 1);
    resultset->numhrsitptable.var_normal /= (double)(resultset->numhrsitptable.normal_count - 1);
    resultset->ageanalysis.var_altered = (double)resultset->ageanalysis.var_altered / (resultset->ageanalysis.altered_count - 1);
    resultset->numhrsitptable.var_altered = (double)resultset->numhrsitptable.var_altered / (resultset->numhrsitptable.altered_count - 1);
    return 0;
}

// =============================================================================
// Posterior Probability
// =============================================================================
void *postprobcalc(Features *dataset, Probability *probdataset, Probability_Err *resultset, unsigned int rowcount)
{
    Probability probdatas = *probdataset;
    //Probability_Err *resultset = (Probability_Err *)malloc(rowcount * sizeof(Probability_Err));
    double tempprob_normal = 1, tempprob_altered = 1;
    double tempgauss_age = 0, tempgauss_hrs = 0;
    //int err_count = 0;
    int i = 0;
    for (i = 0; i < rowcount; i++)
    {
        tempprob_normal = 1;
        tempprob_altered = 1;

        if (dataset[i].soadata == WINTER)
        {
            tempprob_normal = tempprob_normal * probdatas.winter.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.winter.prob_altered;
            // printf("\n TEST S111 : %lf ", probdatas.winter.prob_normal);
        }
        else if (dataset[i].soadata == (float)SPRING)
        {
            tempprob_normal = tempprob_normal * probdatas.spring.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.spring.prob_altered;
            // printf("\n TEST S2 : %lf ", probdatas.spring.prob_normal);
        }
        else if (dataset[i].soadata == (float)SUMMER)
        {
            tempprob_normal = tempprob_normal * probdatas.summer.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.summer.prob_altered;
            // printf("\n TESTS3 : %lf ", probdatas.summer.prob_normal);
        }
        else if (dataset[i].soadata == (float)FALL)
        {
            tempprob_normal = tempprob_normal * probdatas.fall.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.fall.prob_altered;
            // printf("\n TEST S48 : %lf ", probdatas.fall.prob_normal);
        }
        // ==============================
        if (dataset[i].cddata == NORMAL_YES)
        {
            tempprob_normal = tempprob_normal * probdatas.cdiseaseyes.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.cdiseaseyes.prob_altered;
            // printf("\n TEST S4 : %lf ", probdatas.cdiseaseyes.prob_normal);
        }
        else
        {
            tempprob_normal = tempprob_normal * probdatas.cdiseaseno.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.cdiseaseno.prob_altered;
            // printf("\n TEST S5 : %lf ", probdatas.cdiseaseno.prob_normal);
        }
        // ==============================
        if (dataset[i].atdata == NORMAL_YES)
        {
            tempprob_normal = tempprob_normal * probdatas.accidenttrauma_yes.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.accidenttrauma_yes.prob_altered;
            //printf("\n TEST S6 : %lf ", probdatas.accidenttrauma_yes.prob_normal);
        }
        else
        {
            tempprob_normal = tempprob_normal * probdatas.accidenttrauma_no.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.accidenttrauma_no.prob_altered;
            // printf("\n TEST S7 : %lf ", probdatas.accidenttrauma_no.prob_normal);
        }
        // ==============================

        if (dataset[i].sidata == NORMAL_YES)
        {
            tempprob_normal = tempprob_normal * probdatas.surgical_yes.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.surgical_yes.prob_altered;
            // printf("\n TEST S8 : %lf ", probdatas.surgical_yes.prob_normal);
        }
        else
        {
            tempprob_normal = tempprob_normal * probdatas.surgical_no.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.surgical_no.prob_altered;
            // printf("\n TEST S9 : %lf ", probdatas.surgical_no.prob_normal);
        }

        // ==============================

        if (dataset[i].hfdata == HIGH_FEVER_LESSTHAN)
        {
            tempprob_normal = tempprob_normal * probdatas.highfever_lttm.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.highfever_lttm.prob_altered;
            // printf("\n TEST 1: %lf ", probdatas.highfever_lttm.prob_normal);
        }
        else if (dataset[i].hfdata == HIGH_FEVER_MORETHAN)
        {
            tempprob_normal = tempprob_normal * probdatas.highfever_mttm.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.highfever_mttm.prob_altered;
            // printf("\n TEST  2: %lf ", probdatas.highfever_mttm.prob_normal);
        }
        else if (dataset[i].hfdata == HIGH_FEVER_NO)
        {
            tempprob_normal = tempprob_normal * probdatas.highfever_none.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.highfever_none.prob_altered;
            // printf("\n TEST 3: %lf ", probdatas.highfever_none.prob_normal);
        }

        // ==============================
        if (dataset[i].alcconsumptdata == (float)SERVERAL_A_DAY)
        {
            tempprob_normal = tempprob_normal * probdatas.freqalchstd.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.freqalchstd.prob_altered;
            // printf("\n TESTa1 : %lf ", probdatas.freqalchstd.prob_normal);
        }
        else if (dataset[i].alcconsumptdata == (float)EVERY_DAY)
        {
            tempprob_normal = tempprob_normal * probdatas.freqalchevery.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.freqalchevery.prob_altered;
            // printf("\n TEST a2 : %lf ", probdatas.freqalchevery.prob_normal);
        }
        else if (dataset[i].alcconsumptdata == (float)SERVERAL_A_WEEK)
        {
            tempprob_normal = tempprob_normal * probdatas.freqalchstw.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.freqalchstw.prob_altered;
            // printf("\n TEST a3 : %lf ", probdatas.freqalchstw.prob_normal);
        }
        else if (dataset[i].alcconsumptdata == ONCE_A_WEEK)
        {
            tempprob_normal = tempprob_normal * probdatas.freqalchoaw.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.freqalchoaw.prob_altered;
            // printf("\n TEST a4: %lf ", probdatas.freqalchoaw.prob_normal);
        }
        else if (dataset[i].alcconsumptdata == HARDLY_NEVER)
        {
            tempprob_normal = tempprob_normal * probdatas.freqalchhardly.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.freqalchhardly.prob_altered;
            // printf("\n TEST a5 : %lf ", probdatas.freqalchhardly.prob_normal);
        }

        // ==============================

        if (dataset[i].shdata == SH_NEVER)
        {
            tempprob_normal = tempprob_normal * probdatas.smokehabit_never.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.smokehabit_never.prob_altered;
            // printf("\n TEST sh1 : %lf ", probdatas.smokehabit_never.prob_normal);
        }
        else if (dataset[i].shdata == SH_OCCASIONALLY)
        {
            tempprob_normal = tempprob_normal * probdatas.smokehabit_occ.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.smokehabit_occ.prob_altered;
            // printf("\n TEST sh2 : %lf ", probdatas.smokehabit_occ.prob_normal);
        }
        else if (dataset[i].shdata == SH_DAILY)
        {
            tempprob_normal = tempprob_normal * probdatas.smokehabit_daily.prob_normal;
            tempprob_altered = tempprob_altered * probdatas.smokehabit_daily.prob_altered;
            // printf("\n TEST sh3 : %lf ", probdatas.smokehabit_daily.prob_normal);
        }

        // ==============================
        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_normal, probdatas.ageanalysis.var_normal, dataset[i].aoadata);
        tempgauss_hrs = gaussiancalc(probdatas.numhrsitptable.mean_normal, probdatas.numhrsitptable.var_normal, dataset[i].numhrsitdata);
        tempprob_normal = tempprob_normal * tempgauss_age * tempgauss_hrs;

        tempgauss_age = gaussiancalc(probdatas.ageanalysis.mean_altered, probdatas.ageanalysis.var_altered, dataset[i].aoadata);
        tempgauss_hrs = gaussiancalc(probdatas.numhrsitptable.mean_altered, probdatas.numhrsitptable.var_altered, dataset[i].numhrsitdata);
        tempprob_altered = tempprob_altered * tempgauss_age * tempgauss_hrs;

        resultset[i].actual_nora = dataset[i].semendiagdata;
        resultset[i].predicted_nora = tempprob_normal >= tempprob_altered ? 0 : 1;
        resultset[i].prob_normal = tempprob_normal;
        resultset[i].prob_altered = tempprob_altered;
    }
    return 0;
}

// =============================================================================
// Error Probability :
// =============================================================================
void *cmatrix(Probability_Err *postprobdata, Confusion_Matrix *resultset, unsigned int rowcount, unsigned int index)
{
    int i;
    resultset[index].data_count = rowcount;
    resultset[index].true_pos = 0;
    resultset[index].true_neg = 0;
    resultset[index].false_pos = 0;
    resultset[index].false_neg = 0;
    resultset[index].accuracy = 0;
    resultset[index].misclass_rate = 0;
    resultset[index].true_posrate = 0;
    resultset[index].false_posrate = 0;
    resultset[index].true_negrate = 0;
    resultset[index].precision = 0;
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
                resultset[index].prob_error += 1;
            }

            if (postprobdata[i].actual_nora == 1 && postprobdata[i].predicted_nora == 0)
            {
                resultset[index].false_neg += 1;
                resultset[index].prob_error += 1;
            }
        }
    }

    resultset[index].accuracy = (resultset[index].true_pos + resultset[index].true_neg) == 0 ? 0 : (double)(resultset[index].true_pos + resultset[index].true_neg) / rowcount;
    resultset[index].misclass_rate = 1. - resultset[index].accuracy;
    resultset[index].true_posrate = resultset[index].true_pos == 0 ? 0 : (double)resultset[index].true_pos / (resultset[index].true_pos + resultset[index].false_neg);
    resultset[index].false_posrate = (double)resultset[index].false_pos / (resultset[index].false_pos + resultset[index].true_neg);
    resultset[index].true_negrate = 1. - resultset[index].false_posrate;
    resultset[index].precision = (double)resultset[index].true_pos / (resultset[index].false_pos + resultset[index].true_pos);
    resultset[index].prob_error = (double)resultset[index].prob_error /rowcount;
    return 0;
}
// =============================================================================
// Gaussian Formula
// =============================================================================
double gaussiancalc(double mean, double variance, double xval)
{
    double result;
    result = (1 / (sqrt(2 * variance * PI))) * exp(-1 * (pow(xval - mean, 2) / 2 * variance));
    return result;
}


