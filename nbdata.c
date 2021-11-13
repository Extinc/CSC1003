#include <stdio.h>
#include <stdlib.h>
#include "nbdata.h"

Features *storeData(FILE *ifp, char *fpath, int len)
{
    Features *data;
    ifp = fopen(fpath, "r"); // OPEN FILE
    Features tempdata = {};
    if (ifp == NULL)
    {
        exit(1);
    }
    unsigned int rcount = 0; // file num of row counter & index count

    data = (Features *)malloc(len & sizeof(Features));

    while (fscanf(ifp, "%f%*[,] %lf%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %f%*[,] %hd%*[,] %lf%*[,] %hd%*[,]", &tempdata.soadata, &tempdata.aoadata, &tempdata.cddata, &tempdata.atdata, &tempdata.sidata, &tempdata.hfdata, &tempdata.alcconsumptdata, &tempdata.shdata, &tempdata.numhrsitdata, &tempdata.semendiagdata) != EOF)
    {
        data[rcount] = tempdata; //
        rcount++;
    }

    fclose(ifp); // CLOSE FILE
    return data;
}

int countlength(FILE *ifp, char *fpath)
{
    int lencount = 0;
    ifp = fopen(fpath, "r");
    char temp[100];
    while (fscanf(ifp, "%s", temp) != EOF)
    {
        lencount++;
    }
    fclose(ifp); // CLOSE FILE
    return lencount;
}

// ===============================
// Function to Initialize Probability Structure to zero
// ==============================
Probability *inittozero()
{
    Probability results;
    Probability *resultset = &results;
    resultset->semen_diagnosis = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->winter = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->spring = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->summer = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->fall = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->cdiseaseyes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->cdiseaseno = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->accidenttrauma_yes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->accidenttrauma_no = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->surgical_yes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->surgical_no = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->highfever_lttm = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->highfever_mttm = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->highfever_none = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchstd = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchevery = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchstw = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchoaw = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchhardly = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->smokehabit_never = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->smokehabit_occ = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->smokehabit_daily = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->ageanalysis = (struct featuresettn){.normal_count = 0, .altered_count = 0, .sum_normal = 0, .sum_altered = 0, .var_normal = 0, .var_altered = 0, .mean_normal = 0, .mean_altered = 0};
    resultset->numhrsitptable = (struct featuresettn){.normal_count = 0, .altered_count = 0, .sum_normal = 0, .sum_altered = 0, .var_normal = 0, .var_altered = 0, .mean_normal = 0, .mean_altered = 0};
    return resultset;
}
