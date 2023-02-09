#include <iostream>
#include <string>
#include "simulator.h"
#include "predictor.h"
using namespace std;

int main(int argc, char* argv[]){
    try{
        if (argc-1 <= 4){
            string predictor = argv[1];
            unsigned long int m_bits = atoi(argv[2]);
            unsigned long int n_bits;
            string trace_file;
            if(predictor == "gshare"){
                n_bits = atoi(argv[3]);
                trace_file = argv[4];
            }
            else{
                n_bits = 0;
                trace_file = argv[3];
            }
            cout << "------------ Simulator Configurations ------------" << endl;
            cout << "Predictor          : " << predictor << endl;
	        cout << "m_bits             : " << m_bits << endl;
            if(predictor == "gshare"){
                cout << "n_bits             : "  << n_bits << endl;
            }            
            cout << "Trace file          : " << trace_file << endl;
            if(predictor == "smith"){
                PredictorModal* m = new SmithModal(m_bits);
            }
            else if(predictor == "bimodal"){
                PredictorModal* m = new BiModal(m_bits);
            }
            else if(predictor == "gshare"){
                PredictorModal* m = new GshareModal(m_bits, n_bits);
            }
            PredictorModal* m = new GshareModal(m_bits, n_bits);
            // PredictorModal* m = new PredictorModal(predictor, m_bits, n_bits);
            Simulator* s = new Simulator(*m, predictor);
            s->beginSimulator(trace_file);
            s->printResults();
        }else{
            throw(argc-1);
        }
    }catch (int args_count) {
        cout << "Should contain 3 or 4 arguments!!" << " But " << args_count << " are entered." <<endl;
    }
    return 0;
}