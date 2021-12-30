import pandas as pd
import math
import matplotlib.pyplot as plt

def read_data(filename, attr):
    with open(filename, "r") as file:
        data = list(file)
        result = [{val: float(rowdata.split(',')[indx])for indx, val in enumerate(attr)} for rowdata in data]
        return pd.DataFrame(result)


def priorprob(data):
    probresult = {"count_normal": 0, "count_altered": 0,
                  "prob_normal": 0.0, "prob_altered": 0.0}
    for item in data:
        if(item == 1):
            probresult["count_altered"] += 1
        else:
            probresult["count_normal"] += 1
    probresult["prob_normal"] = probresult["count_normal"] / (probresult["count_normal"] + probresult["count_altered"])
    probresult["prob_altered"] = probresult["count_altered"] / (probresult["count_normal"] + probresult["count_altered"])
    return probresult


def condprob(data, prior_data, attr, trgcount, alpha=1):
    result = {}
    normalcount = prior_data["count_normal"]
    alteredcount = prior_data["count_altered"]
    for index, item in data.iterrows():
        for index1, feature in enumerate(attr):
            if(index1 != 1 and index1 != 8 and index1 != 9):
                if(feature in result):
                    if(not item[feature] in result[feature]):
                        result[feature][item[feature]] = {
                            "count_normal": 0, "count_altered": 0, "prob_normal": 0, "prob_altered": 0}
                else:
                    result[feature] = {}
                    if(not item[feature] in result[feature]):
                        result[feature][item[feature]] = {
                            "count_normal": 0, "count_altered": 0, "prob_normal": 0, "prob_altered": 0}
            elif index1 != 9:
                if(feature in result):
                    if(not item[feature] in result[feature]):
                        result[feature] = {"mean_normal": 0, "mean_altered": 0, "variance_normal": 0,
                                           "variance_altered": 0, "prob_normal": 0, "prob_normal": 0, "prob_altered": 0}
                else:
                    result[feature] = {}
                    if(not item[feature] in result[feature]):
                        result[feature] = {"mean_normal": 0, "mean_altered": 0, "variance_normal": 0,
                                           "variance_altered": 0, "prob_normal": 0, "prob_altered": 0}

    for index, item in data[0:trgcount].iterrows():
        for index1, feature in enumerate(attr):
            if(index1 != 1 and index1 != 8 and index1 != 9):
                # For Data that is not Numhrs_Sit & Age
                if(feature in result):
                    # Check if data is in the dictionary
                    if(item[feature] in result[feature]):
                        if(item[attr[9]] == 0):
                            # If semen is Normal
                            result[feature][item[feature]]["count_normal"] += 1
                        else:
                            result[feature][item[feature]
                                            ]["count_altered"] += 1
            elif index1 != 9:
                # For Age & Numhrs_Sit which uses Gaussian
                if(feature in result):
                    if(len(result[feature]) != 0):
                        if(item[attr[9]] == 0):
                            # If semen is Normal
                            result[feature]["mean_normal"] += item[feature]
                        else:
                            result[feature]["mean_altered"] += item[feature]

    for index1, feature in enumerate(attr):
        if(feature != "Semen_Diagnosis"):
            if ("mean_normal" in result[feature]):
                result[feature]["mean_normal"] /= normalcount
                result[feature]["mean_altered"] /= alteredcount
            else:
                for item in result[feature]:
                    if "count_normal" in result[feature][item]:
                        #print("LENGTH : " + str(len(result[feature])))
                        result[feature][item]["prob_normal"] = (
                            result[feature][item]["count_normal"] + alpha)/normalcount + (len(result[feature]) * alpha)
                        result[feature][item]["prob_altered"] = (
                            result[feature][item]["count_altered"] + alpha) / alteredcount + (len(result[feature]) * alpha)

    # Loop to calculate the variance
    for index, item in data.iterrows():
        if(item[attr[9]] == 0):
            # For Age of Analysis
            result[attr[1]]["variance_normal"] += (
                (item[attr[1]] - result[attr[1]]["mean_normal"]) ** 2)
            # For Num of hours sitting per table
            result[attr[8]]["variance_normal"] += (
                (item[attr[8]] - result[attr[8]]["mean_normal"]) ** 2)
        else:
            # For Age of Analysis
            result[attr[1]]["variance_altered"] += (
                (item[attr[1]] - result[attr[1]]["mean_altered"]) ** 2)
            # For Num of hours sitting per table
            result[attr[8]]["variance_altered"] += (
                (item[attr[8]] - result[attr[8]]["mean_altered"]) ** 2)

    # For Age of Analysis
    result[attr[1]]["variance_normal"] /= (normalcount - 1)
    # For Num of hours sitting per table
    result[attr[8]]["variance_normal"] /= (normalcount - 1)
    # For Age of Analysis
    result[attr[1]]["variance_altered"] /= (alteredcount - 1)
    # For Num of hours sitting per table
    result[attr[8]]["variance_altered"] /= (alteredcount - 1)
    return result


def gaussiancalc(mean, variance, xval):
    zscore = xval - mean
    gauss = (1/math.sqrt(2 * math.pi)) * \
        math.exp(-1 * ((zscore ** 2)/(2 * variance)))
    return gauss


def posteriorprob(data, priorprobdata, condprobdata, attr):
    result = []
    tempprob_normal = 1
    tempprob_altered = 1
    gauss_age = 0
    gauss_sit = 0
    for index, item in data.iterrows():
        temp = {}
        tempprob_normal = condprobdata[attr[0]][item[attr[0]]]["prob_normal"] * condprobdata[attr[2]][item[attr[2]]]["prob_normal"] * condprobdata[attr[3]][item[attr[3]]]["prob_normal"] * condprobdata[attr[4]][item[attr[4]]]["prob_normal"] * condprobdata[attr[5]][item[attr[5]]]["prob_normal"] * condprobdata[attr[6]][item[attr[6]]]["prob_normal"] * condprobdata[attr[7]][item[attr[7]]]["prob_normal"] * priorprobdata["prob_normal"]
        tempprob_altered = condprobdata[attr[0]][item[attr[0]]]["prob_altered"] * condprobdata[attr[2]][item[attr[2]]]["prob_altered"] * condprobdata[attr[3]][item[attr[3]]]["prob_altered"] * condprobdata[attr[4]][item[attr[4]]]["prob_altered"] * condprobdata[attr[5]][item[attr[5]]]["prob_altered"] * condprobdata[attr[6]][item[attr[6]]]["prob_altered"] * condprobdata[attr[7]][item[attr[7]]]["prob_altered"] * priorprobdata["prob_altered"]
        gauss_age = gaussiancalc(
            condprobdata[attr[1]]["mean_normal"], condprobdata[attr[1]]["variance_normal"], item[attr[1]])
        gauss_sit = gaussiancalc(
            condprobdata[attr[8]]["mean_normal"], condprobdata[attr[8]]["variance_normal"], item[attr[8]])
        tempprob_normal = tempprob_normal * gauss_age * gauss_sit
        gauss_age = gaussiancalc(
            condprobdata[attr[1]]["mean_altered"], condprobdata[attr[1]]["variance_altered"], item[attr[1]])
        gauss_sit = gaussiancalc(
            condprobdata[attr[8]]["mean_altered"], condprobdata[attr[8]]["variance_altered"], item[attr[8]])
        tempprob_altered = tempprob_altered * gauss_age * gauss_sit
        temp["prob_normal"] = tempprob_normal / (tempprob_normal + tempprob_altered)
        temp["prob_altered"] = tempprob_altered / (tempprob_normal + tempprob_altered)
        temp["actual"] = int(item[attr[9]])
        if(temp["prob_normal"] >= temp["prob_altered"]):
            temp["prediction"] = 0
        else:
            temp["prediction"] = 1
        result.append(temp)
    return pd.DataFrame(result)


def cmatrix(posteriordata, type, size = 0):
    cmatrix_result = {"true_pos": 0, "true_neg": 0,
                      "false_pos": 0, "false_neg": 0, "error": 0}
    for index, prob in posteriordata.iterrows():
        if(prob["prediction"] == prob["actual"]):
            if(prob["prediction"] == 1 and prob["actual"] == 1):
                cmatrix_result["true_pos"] += 1
            else:
                cmatrix_result["true_pos"] += 1
        else:
            if(prob["prediction"] == 1 and prob["actual"] == 0):
                cmatrix_result["false_pos"] += 1
            else:
                cmatrix_result["false_neg"] += 1
            cmatrix_result["error"] += 1
    cmatrix_result["error"] /= len(posteriordata)
    cmatrix_result["size"] = size
    cmatrix_result["type"] = type
    return cmatrix_result

def graph(cmatrixdata):
    plt.plot(cmatrixdata[cmatrixdata["type"]== "train"]["size"], (cmatrixdata[cmatrixdata["type"]== "train"]["error"] * 100), label="Training Data")
    plt.plot(cmatrixdata[cmatrixdata["type"]== "test"]["size"], (cmatrixdata[cmatrixdata["type"]== "test"]["error"] * 100), label="Test Data")
    # Set the x axis label of the current axis.
    plt.xlabel('Data Size')
    # Set the y axis label of the current axis.
    plt.ylabel('Probability of Error (%)')
    plt.legend()
    plt.show()

attributes = ["Season", "Age", "Childish_Disease", "Accident_SeriousTrauma", "Surgical_Intervention",
              "High_fever_lastyear", "Freq_alcconsumption", "Smoking_Habit", "Numhrs_Sit", "Semen_Diagnosis"]
data = read_data("fertility_Diagnosis_Data_Group9_11.txt", attributes)
matrix = []
datalen = int(len(data))
for i in range(5,10):
    
    trgcount = int(datalen * (i/10.0))
    print(trgcount)
    trgprior = priorprob(data[0:trgcount]["Semen_Diagnosis"])
    trgcond = condprob(data, trgprior, attributes, trgcount, alpha=0.1)
    trgpost = posteriorprob(data[0:trgcount], trgprior, trgcond, attributes)
    matrix.append(cmatrix(trgpost, "train", size = trgcount))
    testpost = posteriorprob(data[trgcount:datalen], trgprior, trgcond, attributes)
    matrix.append(cmatrix(testpost, "test", size = trgcount))
print(pd.DataFrame(matrix))
graph(pd.DataFrame(matrix))