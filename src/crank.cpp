/**
 * @file crank.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <vector>
#include <string>
#include <iostream>
#include "Matrix.h"
#include "crank.h"

using namespace algebra;

std::vector< std::vector<double>> crank::sol_edp(std::string CT) const{
    int n = maillage_t.size();
    int p = maillage_S.size();
    double delta_t = maillage_t[1] - maillage_t[0];
    double delta_s = maillage_S[1] - maillage_S[0]; 

    /**
     * @brief Coefficients needed for the system AX=b
     * 
     */
    std::vector<double> k1(p-2);
    std::vector<double> k2(p-1);
    std::vector<double> k3(p-2);

    std::vector<double> k4(p-2);
    std::vector<double> k5(p-1);
    std::vector<double> k6(p-2);    

    double res;
    double res2;

    for(int i = 1; i < p-1; i++){
        res = (pow(sigma_,2) * maillage_S[i]*maillage_S[i]*delta_t) / (8*delta_s*delta_s);
        res2 = (maillage_S[i]*delta_t*r_) / (2*delta_s);
        k1[i-1] = res + res2;
        k2[i-1] = 1 - r_*delta_t - 2*res;
        k3[i-1] = res - res2; 
        k4[i-1] = -res;
        k5[i-1] = 1+2*res;
        k6[i-1] = -res;
    }
    res = (pow(sigma_,2) * maillage_S[p-1]*maillage_S[p-1]*delta_t) / (8*delta_s*delta_s);
    k2[p-2] = 1 - r_*delta_t - 2*res;
    k5[p-2] = 1+2*res;


    /**
     * @brief matrix needed for the equation 
     * 
     *  
     */
    Matrix mat1(k3,k2,k1);
    Matrix mat2(k4,k5,k6);

    /**
     * @brief Initialazing matrix 
     * 
     */
    std::vector< std::vector<double>> solution(n); 

    std::string put("PUT");
    std::string call("CALL");

    if (put.compare(CT)==0){
        res = (pow(sigma_,2) * maillage_S[1]*maillage_S[1]*delta_t) / (8*delta_s*delta_s);
        res2 = (maillage_S[1]*delta_t*r_) / (2*delta_s);
        for(int i = 0; i < p-1;i++){
            solution[n-1].push_back(std::max(0.,K_ - maillage_S[i+1]));
        }

        for(int i = n-1; i > 0 ; i--){
            std::vector<double> res3(p-1);
            res3 = mat1 * solution[i];
            double val = (-res2+res)*K_*exp(-r_*(-maillage_t[i+1]+T_)) + res*K_*exp(-r_*(-maillage_t[i]+T_));
            add_Lambda(res3,val,0);
            solution[i-1] = mat2.resolution(res3);   
        }
    }

    else{
        if (call.compare(CT) ==0){
            res = (pow(sigma_,2) * maillage_S[p-2]*maillage_S[p-2]*delta_t) / (8*delta_s*delta_s);
            res2 = (maillage_S[p-2]*delta_t*r_) / (2*delta_s);
            for(int i = 0; i < p-1;i++){
                solution[n-1].push_back(std::max(0.,maillage_S[i+1] -K_));
            }

            for(int i = n-1; i > 0 ; i--){
                std::vector<double> res3(p-1);
                res3 = mat1 *solution[i];
                double val = (res2+res)*K_*exp(-r_*(maillage_t[i]-T_)) + res*K_*exp(-r_*(maillage_t[i-1]-T_));
                add_Lambda(res3,val,p-2);
                solution[i-1] = mat2.resolution(res3);    
            }
        }
        else{
            throw "invalid string : expected either CALL or PUT";
        }
    }
    return solution;
}