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

    data = (Features *)malloc(len * sizeof(Features));

    while (fscanf(ifp, "%f%*[,] %lf%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %hd%*[,] %f%*[,] %hd%*[,] %lf%*[,] %hd%*[,]", &tempdata.seasons, &tempdata.ageanalysis, &tempdata.childish_disease, &tempdata.trauma, &tempdata.surgical, &tempdata.high_fever, &tempdata.alc_consumpfreq, &tempdata.smoking_habit, &tempdata.numhrsit_pertable, &tempdata.semen_diag) != EOF)
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

// int countlength(FILE *ifp, char *fpath)
// {
//     char *line_buf = NULL;
//     size_t line_buf_size = 0;
//     int line_count = 0;
//     ssize_t line_size;
//     ifp = fopen(fpath, "r");

//     if (!ifp)
//     {
//         fprintf(stderr, "Error opening file '%s'\n", fpath);
//         return EXIT_FAILURE;
//     }

//     /* Get the first line of the file. */
//     //line_size = getline(&line_buf, &line_buf_size, ifp);

//     /* Loop through until we are done with the file. */
//     while ((line_size = getline(&line_buf, &line_buf_size, ifp)) != -1)
//     {
//         /* Increment our line count */
//         ++line_count;
//         //;
//     }

//     /* Free the allocated line buffer */
//     free(line_buf);
//     line_buf = NULL;
//     fclose(ifp); // CLOSE FILE
//     return line_count;
// }