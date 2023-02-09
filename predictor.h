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
        unsigned long int bits_m; 
        unsigned long int bits_n = 0;
        unsigned long int low = 0;
        unsigned long int mid;
        unsigned long int high;
        Block* counter_blocks;
        PredictorModal(unsigned long int m_bits);
        virtual unsigned long int getIndex(string& branch_pc);
        string xoring(string& a, string& b, unsigned long int& n);
        string getPrediction(unsigned long int& index);
        void updateCounter(string& true_outcome, unsigned long int& index);
        void updateGHR(string& actual_outcome, unsigned long int& idx);
};

class SmithModal:public PredictorModal{
    public:
        SmithModal(unsigned long int m_bits);
        unsigned long int getIndex(string& branch_pc);
        void updateGHR(string& true_outcome, unsigned long int& idx);
};

class BiModal:public PredictorModal{
    public:
        Block* counter_blocks;
        BiModal(unsigned long int m_bits);
        unsigned long int getIndex(string& branch_pc);
        void updateGHR(string& true_outcome, unsigned long int& idx);
};

class GshareModal:public PredictorModal{
    public:
        string global_history_reg = "";
        GshareModal(unsigned long int m_bits, unsigned long int n_bits);
        unsigned long int getIndex(string& branch_pc);
        void updateGHR(string& true_outcome, unsigned long int& idx);
};

#endif