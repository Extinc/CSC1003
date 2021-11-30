#include <stdio.h>
#include <stdlib.h>
#include "nbdata.h"

// ================================================================
// Store the Data in the File
// ================================================================
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

    data = (Features *)malloc(len * sizeof(Features));

    while (fscanf(ifp, "%f%*[,] %lf%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %f%*[,] %hd%*[,] %lf%*[,] %hd%*[,]", &tempdata.seasons, &tempdata.ageanalysis, &tempdata.childish_disease, &tempdata.trauma, &tempdata.surgical, &tempdata.high_fever, &tempdata.alc_consumpfreq, &tempdata.smoking_habit, &tempdata.sitting_duration, &tempdata.semen_diag) != EOF)
    {
        data[rcount] = tempdata; // to store the data from tempdata into the the rows
        rcount++; // row counter
    } 

    fclose(ifp); // CLOSE FILE
    return data;
}



// ================================================================
// Count the number of data in the files
// ================================================================

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
