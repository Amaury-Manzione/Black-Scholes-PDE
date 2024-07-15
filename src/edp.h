#include <vector>
#include <string>
#include <tgmath.h>
#include "Matrix.h"

#ifndef EDP_H
#define EDP_H
/**
 * @brief Abstract class associated with the black and scholes equation. 
 * 
 */
class edp
{
    /**
     * @brief attributes of the class
     * 
     */
    protected : 
        double T_;
        double r_;
        double sigma_;
        double K_;
        double L_;
        std::vector<double> maillage_S;
        std::vector<double> maillage_t;

    public : 

        std::vector<double> get_T(){return maillage_t;}

        /**
         * @brief Construct a new edp object
         * 
         */
        edp();

        /**
         * @brief Construct a new edp object
         * 
         * @param T 
         * @param r 
         * @param sigma 
         * @param K 
         * @param L 
         * @param M 
         * @param N 
         */
        edp(int T, double r, double sigma, int K, int L, int M, int N);
        
        
        std::vector<double> get_maillage_S()const{ return maillage_S ;};
        
        
        std::vector<double> get_maillage_t()const{ return maillage_t ;};

        /**
         * @brief return the matrix with the approach solution for all (t,s)
         * 
         * @param CT : either "CALL" or "PUT"
         * @return Matrix 
         */
        virtual std::vector< std::vector<double> > sol_edp(std::string CT) const =0;
};

#endif 
