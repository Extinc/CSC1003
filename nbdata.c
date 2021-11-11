#include <stdio.h>
#include <stdlib.h>
#include "nbdata.h"

features *storeData(FILE *ifp, char *fpath, int len)
{
    features *data;
    ifp = fopen(fpath, "r"); // OPEN FILE
    features tempdata = {};
    if (ifp == NULL)
    {
        exit(1);
    }
    unsigned int rcount = 0; // file num of row counter & index count

    data = (features *)malloc(len & sizeof(features));

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
    resultset->semendiagftures = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->winter = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->spring = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->summer = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->fall = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->cdiseaseyes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->cdiseaseno = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->astyes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->astno = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->siyes = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->sino = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->hflttm = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->hfmttm = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->hfnone = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchstd = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchevery = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchstw = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchoaw = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->freqalchhardly = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->shabitnever = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->shabitocc = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->shabitdaily = (struct FeatureSet){.normal_count = 0, .altered_count = 0, .prob_normal = 0, .prob_altered = 0};
    resultset->ageanalysis = (struct featuresettn){.normal_count = 0, .altered_count = 0, .sum_normal = 0, .sum_altered = 0, .var_normal = 0, .var_altered = 0, .mean_normal = 0, .mean_altered = 0};
    resultset->numhrsitptable = (struct featuresettn){.normal_count = 0, .altered_count = 0, .sum_normal = 0, .sum_altered = 0, .var_normal = 0, .var_altered = 0, .mean_normal = 0, .mean_altered = 0};
    return resultset;
}
