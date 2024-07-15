#include "edp.h"

edp::edp(){
    T_=1;
    r_=0.1;
    sigma_=0.1;
    K_=100.;
    L_=300.;
    maillage_S=std::vector<double>(1000);
    maillage_t=std::vector<double>(1000);
    for (int i=0;i<1000;i++){
        maillage_t[i]=T_*i/1000;
        maillage_S[i]= L_*i/1000;
    }
}

edp::edp(int T, double r, double sigma, int K, int L, int M, int N){
    T_=T;
    r_=r;
    sigma_=sigma;
    K_=K;
    L_=L;
    maillage_S=std::vector<double>(N);
    maillage_t=std::vector<double>(M);
    for (int i=0;i<N;i++){
        maillage_S[i]= L_*i/1000;
    }
    for (int j=0;j<N;j++){
        maillage_t[j]= T_*j/1000;
    }
}

