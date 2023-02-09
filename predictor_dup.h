#ifndef PREDICTOR_H
#define PREDICTOR_H
#include <iostream>
#include <math.h>
#include <string>
using namespace std;   

class Block{
    public:
        unsigned long int index;
        unsigned long int counter;
        Block(){
            index = 0;
            counter = 0;
        }
        Block(unsigned long int i, unsigned long int c){
            index = i;
            counter = c; 
        }
};

class PredictorModal{
    public:
        string type;
        string global_history_reg = "";
        unsigned long int bits_m;
        unsigned long int bits_n;
        unsigned long int mid;
        unsigned long int low = 0;
        unsigned long int high;
        Block* counter_blocks;
        PredictorModal(string predictor_type, unsigned long int m_bits, unsigned long int n_bits);
        string xoring(string& a, string& b, unsigned long int& n);
        string getPrediction(unsigned long int& index);
        void updateCounter(string& true_outcome, unsigned long int& index);
        unsigned long int bimodalIndex(string& branch_pc);
        unsigned long int gshareIndex(string& branch_pc);
        void updateGHR(string& true_outcome, unsigned long int& idx);
};
#endif