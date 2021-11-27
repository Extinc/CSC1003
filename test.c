#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int dataCount = 0;
int trainingset, testingset;

float **readData(float **array)
{
    float season, age, alcohol_consumption, sitting_hours, disease, accident, surgical, fevers, smoking, diagnosis;
    int arrayRow = 0;
    FILE *file = fopen("fertility_Diagnosis_Data_Group9_11.txt", "r");
    while (!feof(file))
    {
        array = (float **)realloc(array, (arrayRow + 1) * sizeof(*array));
        array[arrayRow] = (float *)malloc(11 * sizeof(float));
        fscanf(file, "%g,%g,%g,%g,%g,%g,%g,%g,%g,%g\n", &season, &age, &disease, &accident, &surgical, &fevers, &alcohol_consumption, &smoking, &sitting_hours, &diagnosis);
        array[arrayRow][0] = season;
        array[arrayRow][1] = age;
        array[arrayRow][2] = disease;
        array[arrayRow][3] = accident;
        array[arrayRow][4] = surgical;
        array[arrayRow][5] = fevers;
        array[arrayRow][6] = alcohol_consumption;
        array[arrayRow][7] = smoking;
        array[arrayRow][8] = sitting_hours;
        array[arrayRow][9] = diagnosis;
        array[arrayRow][10] = -1;
        arrayRow++;
        dataCount++;
    }
    //Close file
    fclose(file);
    return array;
}

float variance(int start, int end, float **array, int outcome, float mean, int col)
{
    float diff = 0;
    float total = 0;
    int count = 0;
    for (int row = start; row < end; row++)
    {
        while (array[row][9] == outcome)
        {
            diff = (array[row][col] - mean);
            total += pow(diff, 2);
            count++;
            break;
        }
    }
    float variance = total / count;
    return variance;
}

float gaussian(int start, int end, float mean, float variance, float **array, int row, int col)
{
    float result;
    result = (1 / (sqrt(2 * variance * 3.14))) * exp(-1 * (pow((array[row][col] - mean), 2) / (2 * variance)));
    return result;
}

void printformat(int TN, int TP, int FN, int FP, int error)
{
    float probError = (float)error / (TP + TN + FP + FN);
    printf("===========================================================================================================\n");
    printf("|  TRUE POSITIVE  |  TRUE NEGATIVE  |  FALSE POSITIVE  |  FALSE NEGATIVE  |  ERROR COUNT  |  ERROR PROB   |\n");
    printf("|       %.2d        |       %.2d        |        %.2d        |        %.2d        |       %.2d      |     %.5g\t  |\n", TP, TN, FP, FN, error, probError);
    printf("===========================================================================================================\n");
}

void errorCount(float **array, int start, int end, int start2, int end2)
{
    //Y
    int countNormal = 0, countAltered = 0;
    //X1
    int countWinterNormal = 0, countSpringNormal = 0, countSummerNormal = 0, countFallNormal = 0;
    int countWinterAltered = 0, countSpringAltered = 0, countSummerAltered = 0, countFallAltered = 0;
    //X2
    float totalAgeNormal = 0, meanAgeNormal = 0, varianceAgeNormal = 0, totalAgeAltered = 0, meanAgeAltered = 0, varianceAgeAltered = 0;
    //X3
    int countYesDiseaseNormal = 0, countNoDiseaseNormal = 0, countYesDiseaseAltered = 0, countNoDiseaseAltered = 0;
    //X4
    int countYesAccidentNormal = 0, countNoAccidentNormal = 0, countYesAccidentAltered = 0, countNoAccidentAltered = 0;
    //X5
    int countYesSurgicalNormal = 0, countNoSurgicalNormal = 0, countYesSurgicalAltered = 0, countNoSurgicalAltered = 0;
    //X6
    int countLessFeverNormal = 0, countMoreFeverNormal = 0, countNoFeverNormal = 0;
    int countLessFeverAltered = 0, countMoreFeverAltered = 0, countNoFeverAltered = 0;
    //X7
    int countSeveralDayNormal = 0, countDayNormal = 0, countSeveralWeekNormal = 0, countWeekNormal = 0, countNeverNormal = 0;
    int countSeveralDayAltered = 0, countDayAltered = 0, countSeveralWeekAltered = 0, countWeekAltered = 0, countNeverAltered = 0;
    //X8
    int countNeverSmokingNormal = 0, countOccasionalSmokingNormal = 0, countDailySmokingNormal = 0;
    int countNeverSmokingAltered = 0, countOccasionalSmokingAltered = 0, countDailySmokingAltered = 0;
    //X9
    float totalSittingNormal = 0, meanSittingNormal = 0, varianceSittingNormal = 0, totalSittingAltered = 0, meanSittingAltered = 0, varianceSittingAltered = 0;

    for (int row = start; row < end; row++)
    {
        //count
        while (array[row][9] == 0)
        {
            countNormal++;

            //SEASON OF ANALYSIS
            if (array[row][0] == -1)
            {
                countWinterNormal++;
            }
            else if (array[row][0] == (float)-0.33)
            {
                countSpringNormal++;
            }
            else if (array[row][0] == (float)0.33)
            {
                countSummerNormal++;
            }
            else if (array[row][0] == 1)
            {
                countFallNormal++;
            }

            //AGE OF ANALYSIS
            totalAgeNormal += array[row][1];

            //CHILDISH DISEASE
            if (array[row][2] == 0)
            {
                countYesDiseaseNormal++;
            }
            else if (array[row][2] == 1)
            {
                countNoDiseaseNormal++;
            }

            //ACCIDENT OR SERIOUS TRAUMA
            if (array[row][3] == 0)
            {
                countYesAccidentNormal++;
            }
            else if (array[row][3] == 1)
            {
                countNoAccidentNormal++;
            }

            //SURGICAL INTERVENTION
            if (array[row][4] == 0)
            {
                countYesSurgicalNormal++;
            }
            else if (array[row][4] == 1)
            {
                countNoSurgicalNormal++;
            }

            //HIGH FEVERS IN LAST YEAR
            if (array[row][5] == -1)
            {
                countLessFeverNormal++;
            }
            else if (array[row][5] == 0)
            {
                countMoreFeverNormal++;
            }
            else if (array[row][5] == 1)
            {
                countNoFeverNormal++;
            }

            //FREQUENCY OF ALCOHOL CONSUMPTION
            if (array[row][6] == (float)0.2)
            {
                countSeveralDayNormal++;
            }
            else if (array[row][6] == (float)0.4)
            {
                countDayNormal++;
            }
            else if (array[row][6] == (float)0.6)
            {
                countSeveralWeekNormal++;
            }
            else if (array[row][6] == (float)0.8)
            {
                countWeekNormal++;
            }
            else if (array[row][6] == 1)
            {
                countNeverNormal++;
            }

            //SMOKING HABIT
            if (array[row][7] == -1)
            {
                countNeverSmokingNormal++;
            }
            else if (array[row][7] == 0)
            {
                countOccasionalSmokingNormal++;
            }
            else if (array[row][7] == 1)
            {
                countDailySmokingNormal++;
            }

            //NUMBER OF HOURS SPENT SITTING PER DAY
            totalSittingNormal += array[row][8];

            break;
        }

        while (array[row][9] == 1)
        {
            countAltered++;

            if (array[row][0] == -1)
            {
                countWinterAltered++;
            }
            else if (array[row][0] == (float)-0.33)
            {
                countSpringAltered++;
            }
            else if (array[row][0] == (float)0.33)
            {
                countSummerAltered++;
            }
            else if (array[row][0] == 1)
            {
                countFallAltered++;
            }

            totalAgeAltered += array[row][1];

            if (array[row][2] == 0)
            {
                countYesDiseaseAltered++;
            }
            else if (array[row][2] == 1)
            {
                countNoDiseaseAltered++;
            }

            if (array[row][3] == 0)
            {
                countYesAccidentAltered++;
            }
            else if (array[row][3] == 1)
            {
                countNoAccidentAltered++;
            }

            if (array[row][4] == 0)
            {
                countYesSurgicalAltered++;
            }
            else if (array[row][4] == 1)
            {
                countNoSurgicalAltered++;
            }

            if (array[row][5] == -1)
            {
                countLessFeverAltered++;
            }
            else if (array[row][5] == 0)
            {
                countMoreFeverAltered++;
            }
            else if (array[row][5] == 1)
            {
                countNoFeverAltered++;
            }

            if (array[row][6] == (float)0.2)
            {
                countSeveralDayAltered++;
            }
            else if (array[row][6] == (float)0.4)
            {
                countDayAltered++;
            }
            else if (array[row][6] == (float)0.6)
            {
                countSeveralWeekAltered++;
            }
            else if (array[row][6] == (float)0.8)
            {
                countWeekAltered++;
            }
            else if (array[row][6] == 1)
            {
                countNeverAltered++;
            }

            if (array[row][7] == -1)
            {
                countNeverSmokingAltered++;
            }
            else if (array[row][7] == 0)
            {
                countOccasionalSmokingAltered++;
            }
            else if (array[row][7] == 1)
            {
                countDailySmokingAltered++;
            }

            totalSittingAltered += array[row][8];

            break;
        }
    }

    //Prior probability of normal & altered
    float ppNormal = (float)countNormal / (countNormal + countAltered);
    float ppAltered = (float)countAltered / (countNormal + countAltered);

    //Calculate mean and variance of Age and Sitting hours
    meanAgeNormal = totalAgeNormal / countNormal;
    varianceAgeNormal = variance(start, end, array, 0, meanAgeNormal, 1);
    meanAgeAltered = totalAgeAltered / countAltered;
    varianceAgeAltered = variance(start, end, array, 1, meanAgeAltered, 1);
    meanSittingNormal = totalSittingNormal / countNormal;
    varianceSittingNormal = variance(start, end, array, 0, meanSittingNormal, 8);
    meanSittingAltered = totalSittingAltered / countAltered;
    varianceSittingAltered = variance(start, end, array, 1, meanSittingAltered, 8);

    //Calculate conditional probability of data
    //SEASONS
    float cpWinterNormal = (float)countWinterNormal / countNormal;
    float cpSpringNormal = (float)countSpringNormal / countNormal;
    float cpSummerNormal = (float)countSummerNormal / countNormal;
    float cpFallNormal = (float)countFallNormal / countNormal;
    float cpWinterAltered = (float)countWinterAltered / countAltered;
    float cpSpringAltered = (float)countSpringAltered / countAltered;
    float cpSummerAltered = (float)countSummerAltered / countAltered;
    float cpFallAltered = (float)countFallAltered / countAltered;
    //DISEASE
    float cpYesDiseaseNormal = (float)countYesDiseaseNormal / countNormal;
    float cpNoDiseaseNormal = (float)countNoDiseaseNormal / countNormal;
    float cpYesDiseaseAltered = (float)countYesDiseaseAltered / countAltered;
    float cpNoDiseaseAltered = (float)countNoDiseaseAltered / countAltered;
    //ACCIDENT
    float cpYesAccidentNormal = (float)countYesAccidentNormal / countNormal;
    float cpNoAccidentNormal = (float)countNoAccidentNormal / countNormal;
    float cpYesAccidentAltered = (float)countYesAccidentAltered / countAltered;
    float cpNoAccidentAltered = (float)countNoAccidentAltered / countAltered;
    //SURGICAL
    float cpYesSurgicalNormal = (float)countYesSurgicalNormal / countNormal;
    float cpNoSurgicalNormal = (float)countNoSurgicalNormal / countNormal;
    float cpYesSurgicalAltered = (float)countYesSurgicalAltered / countAltered;
    float cpNoSurgicalAltered = (float)countNoSurgicalAltered / countAltered;
    //FEVER
    float cpLessFeverNormal = (float)countLessFeverNormal / countNormal;
    float cpMoreFeverNormal = (float)countMoreFeverNormal / countNormal;
    float cpNoFeverNormal = (float)countNoFeverNormal / countNormal;
    float cpLessFeverAltered = (float)countLessFeverAltered / countAltered;
    float cpMoreFeverAltered = (float)countMoreFeverAltered / countAltered;
    float cpNoFeverAltered = (float)countNoFeverAltered / countAltered;
    //ALCOHOL
    float cpSeveralDayNormal = (float)countSeveralDayNormal / countNormal;
    float cpEveryNormal = (float)countDayNormal / countNormal;
    float cpSeveralWeekNormal = (float)countSeveralWeekNormal / countNormal;
    float cpOnceWeekNormal = (float)countWeekNormal / countNormal;
    float cpNeverNormal = (float)countNeverNormal / countNormal;
    float cpSeveralDayAltered = (float)countSeveralDayAltered / countAltered;
    float cpEveryAltered = (float)countDayAltered / countAltered;
    float cpSeveralWeekAltered = (float)countSeveralWeekAltered / countAltered;
    float cpOnceWeekAltered = (float)countWeekAltered / countAltered;
    float cpNeverAltered = (float)countNeverAltered / countAltered;
    //SMOKING
    float cpNeverSmokingNormal = (float)countNeverSmokingNormal / countNormal;
    float cpOccasionalSmokingNormal = (float)countOccasionalSmokingNormal / countNormal;
    float cpDailySmokingNormal = (float)countDailySmokingNormal / countNormal;
    float cpNeverSmokingAltered = (float)countNeverSmokingAltered / countAltered;
    float cpOccasionalSmokingAltered = (float)countOccasionalSmokingAltered / countAltered;
    float cpDailySmokingAltered = (float)countDailySmokingAltered / countAltered;

    start = start2;
    end = end2;

    int TP = 0, TN = 0, FP = 0, FN = 0, errorCount = 0;

    for (int row = start; row < end; row++)
    {
        //transform gaussian distributed to standard gaussian distribution with zero mean and unit variance
        float gaussianAgeNormal = gaussian(start, end, meanAgeNormal, varianceAgeNormal, array, row, 1);
        float gaussianAgeAltered = gaussian(start, end, meanAgeAltered, varianceAgeAltered, array, row, 1);
        float gaussianSittingNormal = gaussian(start, end, meanSittingNormal, varianceSittingNormal, array, row, 8);
        float gaussianSittingAltered = gaussian(start, end, meanSittingAltered, varianceSittingAltered, array, row, 8);

        float seasonNormal, seasonAltered, ageNormal, ageAltered, diseaseNormal, diseaseAltered, accidentNormal, accidentAltered, surgicalNormal, surgicalAltered, feverNormal, feverAltered, alcoholNormal, alcoholAltered, smokingNormal, smokingAltered, sittingNormal, sittingAltered;
        //X1
        if (array[row][0] == -1)
        {
            seasonNormal = cpWinterNormal;
            seasonAltered = cpWinterAltered;
        }
        else if (array[row][0] == (float)-0.33)
        {
            seasonNormal = cpSpringNormal;
            seasonAltered = cpSpringAltered;
        }
        else if (array[row][0] == (float)0.33)
        {
            seasonNormal = cpSummerNormal;
            seasonAltered = cpSummerAltered;
        }
        else if (array[row][0] == 1)
        {
            seasonNormal = cpFallNormal;
            seasonAltered = cpFallAltered;
        }

        //X2
        ageNormal = gaussianAgeNormal;
        ageAltered = gaussianAgeAltered;

        //X3
        if (array[row][2] == 0)
        {
            diseaseNormal = cpYesDiseaseNormal;
            diseaseAltered = cpYesDiseaseAltered;
        }
        else if (array[row][2] == 1)
        {
            diseaseNormal = cpNoDiseaseNormal;
            diseaseAltered = cpNoDiseaseAltered;
        }

        //X4
        if (array[row][3] == 0)
        {
            accidentNormal = cpYesAccidentNormal;
            accidentAltered = cpYesAccidentAltered;
        }
        else if (array[row][3] == 1)
        {
            accidentNormal = cpNoAccidentNormal;
            accidentAltered = cpNoAccidentAltered;
        }

        //X5
        if (array[row][4] == 0)
        {
            surgicalNormal = cpYesSurgicalNormal;
            surgicalAltered = cpYesSurgicalAltered;
        }
        else if (array[row][4] == 1)
        {
            surgicalNormal = cpNoSurgicalNormal;
            surgicalAltered = cpNoSurgicalAltered;
        }

        //X6
        if (array[row][5] == -1)
        {
            feverNormal = cpLessFeverNormal;
            feverAltered = cpLessFeverAltered;
        }
        else if (array[row][5] == 0)
        {
            feverNormal = cpMoreFeverNormal;
            feverAltered = cpMoreFeverAltered;
        }
        else if (array[row][5] == 1)
        {
            feverNormal = cpNoFeverNormal;
            feverAltered = cpNoFeverAltered;
        }

        //X7
        if (array[row][6] == (float)0.2)
        {
            alcoholNormal = cpSeveralDayNormal;
            alcoholAltered = cpSeveralDayAltered;
        }
        else if (array[row][6] == (float)0.4)
        {
            alcoholNormal = cpEveryNormal;
            alcoholAltered = cpEveryAltered;
        }
        else if (array[row][6] == (float)0.6)
        {
            alcoholNormal = cpSeveralWeekNormal;
            alcoholAltered = cpSeveralWeekAltered;
        }
        else if (array[row][6] == (float)0.8)
        {
            alcoholNormal = cpOnceWeekNormal;
            alcoholAltered = cpOnceWeekAltered;
        }
        else if (array[row][6] == 1)
        {
            alcoholNormal = cpNeverNormal;
            alcoholAltered = cpNeverAltered;
        }

        //X8
        if (array[row][7] == -1)
        {
            smokingNormal = cpNeverSmokingNormal;
            smokingAltered = cpNeverSmokingAltered;
        }
        else if (array[row][7] == 0)
        {
            smokingNormal = cpOccasionalSmokingNormal;
            smokingAltered = cpOccasionalSmokingAltered;
        }
        else if (array[row][7] == 1)
        {
            smokingNormal = cpDailySmokingNormal;
            smokingAltered = cpDailySmokingAltered;
        }

        //X9
        sittingNormal = gaussianSittingNormal;
        sittingAltered = gaussianSittingAltered;

        float posteriorNormal = seasonNormal * ageNormal * diseaseNormal * accidentNormal * surgicalNormal * feverNormal * alcoholNormal * smokingNormal * sittingNormal * ppNormal;
        float posteriorAltered = seasonAltered * ageAltered * diseaseAltered * accidentAltered * surgicalAltered * feverAltered * alcoholAltered * smokingAltered * sittingAltered * ppAltered;
        float posteriorTotal = posteriorNormal + posteriorAltered;
        float posteriorProbNormal;
        float posteriorProbAltered;
        if (posteriorTotal != 0)
        {
            posteriorProbNormal = posteriorNormal / posteriorTotal;
            posteriorProbAltered = posteriorAltered / posteriorTotal;
        }
        else
        {
            posteriorProbNormal = 1;
            posteriorProbAltered = 0;
        }

        float prediction = -1;

        if (posteriorProbNormal >= posteriorProbAltered)
        {
            prediction = 0;
        }
        else if (posteriorProbNormal < posteriorProbAltered)
        {
            prediction = 1;
        }

        if (prediction == 0 && array[row][9] == 0)
        {
            array[row][10] = 0;
            TN++;
        }
        else if (prediction == 1 && array[row][9] == 1)
        {
            array[row][10] = 0;
            TP++;
        }
        else if (prediction == 0 && array[row][9] == 1)
        {
            array[row][10] = 1;
            FN++;
            errorCount++;
        }
        else if (prediction == 1 && array[row][9] == 0)
        {
            array[row][10] = 1;
            FP++;
            errorCount++;
        }
    }
    printformat(TN, TP, FN, FP, errorCount);
}

int main()
{
    float timespent;
    clock_t tstart = clock();
    float **array = 0;
    int arrayRow;
    array = readData(array);

    printf("TRAINING 90\n");
    errorCount(array, 0, 90, 0, 90);
    printf("TESTING 10\n");
    errorCount(array, 0, 90, 90, 100);

    //test 1    (80:20)
    printf("TRAINING 80\n");
    errorCount(array, 0, 80, 0, 80);
    printf("TESTING 20\n");
    errorCount(array, 0, 80, 80, 100);

    printf("TRAINING 50\n");
    errorCount(array, 0, 50, 0, 50);
    printf("TESTING 50\n");
    errorCount(array, 0, 50, 50, 100);

    printf("TRAINING 60\n");
    errorCount(array, 0, 60, 0, 60);
    printf("TESTING 40\n");
    errorCount(array, 0, 60, 60, 100);

    printf("TRAINING 70\n");
    errorCount(array, 0, 70, 0, 70);
    printf("TESTING 30\n");
    errorCount(array, 0, 70, 70, 100);

    for (int i = 0; i < dataCount; i++)
        free(array[i]);
    free(array);
    clock_t tend = clock();                              // STOP TIMER
    timespent = (float)(tend - tstart) / CLOCKS_PER_SEC; // Duration of app run
    printf("\n Time taken for the appication to run is %f seconds", timespent);
    return 0;
}