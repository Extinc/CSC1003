#ifndef ___nbstruct__
#define ___nbstruct__

#define PI 3.14159265          // Value of PI
#define WINTER -1              // Season
#define SPRING -0.33           // Season
#define SUMMER 0.33            // Season
#define FALL 1                 // Season
#define HIGH_FEVER_LESSTHAN -1 // For High Fever Less than 3 month ago
#define HIGH_FEVER_MORETHAN 0  // For High Fever More than 3 month ago
#define HIGH_FEVER_NO 1        // High Fever No
#define SERVERAL_A_DAY 0.2f    // For Frequency of Alcohol Consumption Serveral a day
#define EVERY_DAY 0.4f         // For Frequency of Alcohol Consumption Everyday
#define SERVERAL_A_WEEK 0.6f   // For Frequency of Alcohol Consumption Several a week
#define ONCE_A_WEEK 0.8f       // For Frequency of Alcohol Consumption Once a week
#define HARDLY_NEVER 1         // For Frequency of Alcohol Consumption Hardly or Never
#define SH_NEVER -1            // Smoking Habit Never
#define SH_OCCASIONALLY 0      // Smoking Habit Occasionally
#define SH_DAILY 1             // Smoking Habit Daily
#define NORMAL_YES 0           // NORMAL / YES
#define ALTERED_NO 1           // ALTERED / NO
#define ALPHA 0.01             // alpha value for laplace smoothing
typedef struct
{
    float seasons;                       // SEASON OF Analysis
    double ageanalysis;                  // Age of Analysis
    unsigned short int childish_disease; // Childish Disease
    unsigned short int trauma;           // Accident / Serious Trauma
    unsigned short int surgical;         // Surgical Intervention
    short int high_fever;                // High Fever Last Year
    float alc_consumpfreq;               // Freuqnce of alcohol consumption
    short int smoking_habit;             // smoking habit
    double sitting_duration;             // Number of hours spent sitting per table
    unsigned short int semen_diag;       // Semen Diagnosis
} Features;

// Features struct except for Age and Number of Hours Spend sitting per day
struct FeatureSet
{
    unsigned int normal_count;  // Number of Normal
    unsigned int altered_count; // Number of altered
    double prob_normal;         // Probability of Normal
    double prob_altered;        // Probability of Altered
};

// Features for Age and Number of Hours Spend sitting per day
struct FeatureSetGauss
{
    unsigned int normal_count;  // Number of Normal
    unsigned int altered_count; // Number of altered
    double sum_normal;          // Value of Sum Normal
    double sum_altered;         // Value of SUm altered
    double var_normal;          // Value of Variance Normal
    double var_altered;         // Value of Variance Altered
    double mean_normal;         // Value of Mean Normal
    double mean_altered;        // Value of Mean Altered
};

typedef struct
{
    struct FeatureSet semen_diagnosis;    // Semen Diagnosis Features
    struct FeatureSet winter;             // Season : Winter
    struct FeatureSet spring;             // Season : Spring
    struct FeatureSet summer;             // Season : Summer
    struct FeatureSet fall;               // Season : Fall
    struct FeatureSet cdisease_yes;       // Childish Disease Yes
    struct FeatureSet cdisease_no;        // Childish Disease No
    struct FeatureSet trauma_yes;         // Accident / Serious Trauma YES
    struct FeatureSet trauma_no;          // Accident / Serious Trauma NO
    struct FeatureSet surgical_yes;       // Surgical Intervention YES
    struct FeatureSet surgical_no;        // Surgical Intervention NO
    struct FeatureSet highfever_lttm;     // High Fever last Year : Less than 3 mths ago
    struct FeatureSet highfever_mttm;     // High Fever last Year : More than 3 mths ago
    struct FeatureSet highfever_none;     // High Fever last Year : NO
    struct FeatureSet freqalch_std;       // Frequency of alcohol : Several times a day
    struct FeatureSet freqalch_every;     // Frequency of alcohol : Every day
    struct FeatureSet freqalch_stw;       // Frequency of alcohol : Several times a week
    struct FeatureSet freqalch_oaw;       // Frequency of alcohol : Once a week
    struct FeatureSet freqalch_hardly;    // Frequency of alcohol : hardly or never
    struct FeatureSet smokehabit_never;   // Smoking Habit : Never
    struct FeatureSet smokehabit_occ;     // Smoking Habit : Occasionally
    struct FeatureSet smokehabit_daily;   // Smoking Habit : Daily
    struct FeatureSetGauss ageanalysis;   // Age of Analysis
    struct FeatureSetGauss sitting_hours; // Number of hours sitting per table
} Probability;

typedef struct
{
    short actual_nora;    // Actual Normal or Altered:  0 = Normal or 1 = Altered
    short predicted_nora; // predicted Normal Or Altered :  0 = Normal or 1 = Altered
    double prob_normal;   // Probability of Normal
    double prob_altered;  // Probability of Altered
} Probability_Err;

struct Confusion_Matrix
{
    unsigned int data_count; // Number of Data for the data set
    unsigned int true_pos;   // True Positive : No of times predict correctly that patient is not normal
    unsigned int true_neg;   // True Negative : No of times predict wrongly that patient is normal
    unsigned int false_pos;  // True Positive : No of times predict correctly that patient is not normal
    unsigned int false_neg;  // True Negative : No of times predict wrongly that patient is normal
    float prob_error;        // the probability of error, occurance of how many time the error occurred
};

typedef struct
{
    struct Confusion_Matrix trg_cmatrix[5]; // COnfusion Matrix for Training Data
    struct Confusion_Matrix tst_cmatrix[5]; // Confusion Matrix for Test Data
} Confusion_Matrix_Type;
#endif