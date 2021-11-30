#ifndef ___nbstruct__
#define ___nbstruct__

#define PI 3.14159265
#define WINTER -1
#define SPRING -0.33
#define SUMMER 0.33
#define FALL 1
#define HIGH_FEVER_LESSTHAN -1
#define HIGH_FEVER_MORETHAN 0
#define HIGH_FEVER_NO 1
#define SERVERAL_A_DAY 0.2f
#define EVERY_DAY 0.4f
#define SERVERAL_A_WEEK 0.6f
#define ONCE_A_WEEK 0.8f
#define HARDLY_NEVER 1
#define SH_NEVER -1
#define SH_OCCASIONALLY 0
#define SH_DAILY 1
#define NORMAL_YES 0 // NORMAL / YES
#define ALTERED_NO 1 // ALTERED / NO
#define ALPHA 0.01
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
    double sitting_duration;            // Number of hours spent sitting per table
    unsigned short int semen_diag;       // Semen Diagnosis
} Features;

// Features struct except for Age and Number of Hours Spend sitting per day
struct FeatureSet
{
    unsigned int normal_count;  // Number of Normal
    unsigned int altered_count; // Number of altered
    double prob_normal;         // Probability of Normal
    double prob_altered;        // Probability of Normal
};

// Features for Age and Number of Hours Spend sitting per day
struct FeatureSetGauss
{
    unsigned int normal_count;  // Number of Normal
    unsigned int altered_count; // Number of altered
    double sum_normal;          // Number of Normal
    double sum_altered;         // Number of altered
    double var_normal;          // Value of Variance
    double var_altered;         // Value of Variance
    double mean_normal;         // Value of Mean
    double mean_altered;        // Value of Mean
};

typedef struct
{
    struct FeatureSet semen_diagnosis;      // Semen Diagnosis Features
    struct FeatureSet winter;               // Season : Winter
    struct FeatureSet spring;               // Season : Spring
    struct FeatureSet summer;               // Season : Summer
    struct FeatureSet fall;                 // Season : Fall
    struct FeatureSet cdisease_yes;         // Childish Disease Yes
    struct FeatureSet cdisease_no;          // Childish Disease No
    struct FeatureSet trauma_yes;   // Accident / Serious Trauma YES
    struct FeatureSet trauma_no;    // Accident / Serious Trauma NO
    struct FeatureSet surgical_yes;         // Surgical Intervention YES
    struct FeatureSet surgical_no;          // Surgical Intervention NO
    struct FeatureSet highfever_lttm;       // High Fever last Year : Less than 3 mths ago
    struct FeatureSet highfever_mttm;       // High Fever last Year : More than 3 mths ago
    struct FeatureSet highfever_none;       // High Fever last Year : NO
    struct FeatureSet freqalch_std;         // Frequency of alcohol : Several times a day
    struct FeatureSet freqalch_every;       // Frequency of alcohol : Every day
    struct FeatureSet freqalch_stw;         // Frequency of alcohol : Several times a week
    struct FeatureSet freqalch_oaw;         // Frequency of alcohol : Once a week
    struct FeatureSet freqalch_hardly;      // Frequency of alcohol : hardly or never
    struct FeatureSet smokehabit_never;     // Smoking Habit : Never
    struct FeatureSet smokehabit_occ;       // Smoking Habit : Occasionally
    struct FeatureSet smokehabit_daily;     // Smoking Habit : Daily
    struct FeatureSetGauss ageanalysis;     // Age of Analysis
    struct FeatureSetGauss sitting_hours; // Number of hours sitting per table
} Probability;

typedef struct
{
    short actual_nora;    // Actual Normal or Altered
    short predicted_nora; // predicted Normal Or Altered :  Y | 0 = Normal or Y | 1 = Altered
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