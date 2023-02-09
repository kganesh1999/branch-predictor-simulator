#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <sstream>
#include "predictor.h"
using namespace std;
class Simulator{
    public:
        PredictorModal model;
        string type;
        unsigned long int traces_read = 0;
        unsigned long int mispreds = 0;
        Simulator(PredictorModal m, string predictor_type);
        vector<string> split(string& s, string& delimeter);
        void beginSimulator(string& trace_file);
        void printResults();
        void printModelContents();
};
#endif