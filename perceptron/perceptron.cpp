/*
Grace Dolphy
Assignment 5
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void assignRandomInitalWeights(double* weights, int size);
void printWeightsResult(double* weights, int size);

int main(int argc, char *argv[]) {
    //accept first training data file name
    string trainFileName = argv[1];
    ifstream trainFile (trainFileName);
    
    double weights[5];

    //training phase.
    if (trainFile.is_open()) {
        int rows;
        trainFile >> rows; //get number of rows.

        //assign arbitrary w's
        assignRandomInitalWeights(weights, 5);

        double trainingMatrix[rows][5];
        int labels[rows];

        //gather rest of input from test data file, input into trainingMatrix. add the labels to separate array.
        for (int j = 0; j < rows; j++) {
            //enhance input column
            trainingMatrix[j][0] = 1;

            for (int i = 1; i < 5; i++) {
                int xij;
                trainFile >> xij;
                trainingMatrix[j][i] = xij;
            }

            int label;
            trainFile >> label;
            labels[j] = label;           
        }

        //For a number of predetermined “epochs” k :
        for (int k = 1; k <= 50; k++) {
            //For each data point xj :
            for (int j = 0; j < rows; j++) {
                double result = weights[0]*trainingMatrix[j][0] + weights[1]*trainingMatrix[j][1] + weights[2]*trainingMatrix[j][2] + weights[3]*trainingMatrix[j][3] + weights[4]*trainingMatrix[j][4];
                if (result > 0) {
                    result = 1;
                } else {
                    result = 0;
                }

                for (int w = 0; w < 5; w++) {
                    weights[w] = weights[w] + .5*(labels[j] - result)*trainingMatrix[j][w];
                }
            }   
        }

        trainFile.close();
    }

    //accept second training data file name
    string testFileName = argv[2];
    ifstream testFile (testFileName);

    if (testFile.is_open()) {
        int rows;
        testFile >> rows; //get number of rows.

        double testingMatrix[rows][5];

        //gather rest of input from test data file, input into testingMatrix.
        for (int j = 0; j < rows; j++) {
            //enhance input column
            testingMatrix[j][0] = 1;

            for (int i = 1; i < 5; i++) {
                int xij;
                testFile >> xij;
                testingMatrix[j][i] = xij;
            }        
        }

        //use the weights obtained and multiple by each xji to get final result.
        for (int j = 0; j < rows; j++) {
            if (weights[0]*testingMatrix[j][0] + weights[1]*testingMatrix[j][1] + weights[2]*testingMatrix[j][2] + weights[3]*testingMatrix[j][3] + weights[4]*testingMatrix[j][4] > 0){
                cout << "1 "; 
            } else {
                cout << "0 ";
            }
        }
    }

    return 0;
}

//called to assign random weights to the weights array.
void assignRandomInitalWeights(double* weights, int size) {
    for (int i = 0; i < size; i++) {
        weights[i] = ((double) rand() / (RAND_MAX));
    }
}

//prints out the weights assigned.
void printWeightsResult(double* weights, int size) {
    for (int i = 0; i < size; i++) {
        cout << weights[i] << " ";
    }
    cout << endl;
}
