#include "predictor.h"

PredictorModal::PredictorModal(unsigned long int m_bits){
        bits_m = m_bits;
}

string PredictorModal::xoring(string& a, string& b, unsigned long int& n){
    string ans = "";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b[i])
            ans += "0";
        else
            ans += "1";
    }
    return ans;
}

void PredictorModal::updateCounter(string& true_outcome, unsigned long int& index){
    if (true_outcome=="n"){
        if (counter_blocks[index].counter > low){
            counter_blocks[index].counter -=1;
        }
    } 
    else{
        if (counter_blocks[index].counter < high){
            counter_blocks[index].counter += 1;
        }
    }
}

string PredictorModal::getPrediction(unsigned long int& index){
    string pred;
    if(counter_blocks[index].counter < mid){
        pred = "n";
    }else{
        pred = "t";
    }
    return pred; 
}

void PredictorModal::updateGHR(string& true_outcome, unsigned long int& idx){
    ;
}

SmithModal::SmithModal(unsigned long int m_bits):PredictorModal(m_bits){
        counter_blocks = new Block(0, mid);
        high = pow(2,m_bits)-1;
        mid = (high+1) / 2;
}

unsigned long int SmithModal::getIndex(string& branch_pc){
    return 0;
}

BiModal::BiModal(unsigned long int m_bits):PredictorModal(m_bits){
        high = 7;
        mid = 4;
        unsigned long int size = (pow(2,m_bits));
        counter_blocks = new Block[size];
        for(unsigned long int i=0; i<pow(2,m_bits); i++){
            counter_blocks[i] = Block(i, mid);
        }
}

unsigned long int BiModal::getIndex(string& branch_pc){
    unsigned long int a_int = stoi(branch_pc, 0, 16);
    string binarystring = bitset<24>(a_int).to_string().substr(0,22);
    string idx_bin = binarystring.substr(binarystring.size() - (bits_m));
    unsigned long int idx = stoi(idx_bin,0,2);
    return idx;
}

void BiModal::updateGHR(string& true_outcome, unsigned long int& idx){
    ;
}

GshareModal::GshareModal(unsigned long int m_bits, unsigned long int n_bits):PredictorModal(m_bits){
        bits_n = n_bits;
        high = 7;
        mid = 4;
        unsigned long int size = (pow(2,m_bits));
        counter_blocks = new Block[size];
        for(unsigned long int i=0; i<pow(2,m_bits); i++){
            counter_blocks[i] = Block(i, mid);
        }
        for(unsigned long int i=0; i<n_bits; i++){
            global_history_reg += "0";
        }
}

unsigned long int GshareModal::getIndex(string& branch_pc){
    unsigned long int a_int = stoi(branch_pc, 0, 16);
    string binarystring = bitset<24>(a_int).to_string();
    string tag = binarystring.substr(binarystring.size() - 2 - bits_m, bits_m);
    string updated_tag = tag.substr(0, bits_m-bits_n);
    string lsb_pc = tag.substr(tag.size()-bits_n, bits_n);
    string xored_bits = xoring(lsb_pc, global_history_reg, bits_n);
    string xor_res = xored_bits.substr(xored_bits.size()-bits_n, bits_n);
    string m_index = updated_tag.append(xor_res);
    unsigned long int idx = stoi(m_index,0,2);
    return idx;
}

void GshareModal::updateGHR(string& true_outcome, unsigned long int& idx){
    string entry;
    if(true_outcome == "t"){
        entry = "1";
    }else{
        entry = "0";
    }
    global_history_reg = entry.append(global_history_reg.substr(0,bits_n-1));
}