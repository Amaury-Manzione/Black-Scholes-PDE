#include "reduite.h"

std::vector< std::vector<double> > reduite::sol_edp(std::string CT) const{
    int size = maillage_t.size();
    int size_S = maillage_S.size();
    std::vector< std::vector<double> > C(size);
    std::vector<double> new_maillage_S(size_S);
    

    /**
     * @brief Coefficients needed for the system AX=b
     * 
     */
    new_maillage_S[size_S-1]=log(maillage_S[size_S-1]/K_);
    new_maillage_S[0]=-new_maillage_S[size_S-1];
    double h = 2*new_maillage_S[size-1]/size_S;
    for(int i=1;i<size_S-1;i++){
        new_maillage_S[i]=new_maillage_S[i-1]+h;
    }
    double delta_t = (maillage_t[1]-maillage_t[0])*pow(sigma_,2)/2;
    double k1 = 1/(pow(h,2));
    double k3 = -1/delta_t;
    double k2 = -(2*k1 - k3);
    /**
     * @brief tridiagonal matrix A in the system : AX=b
     * 
     * @return algebra::Matrix 
     */
    algebra::Matrix A(k1,k2,k1,size_S-1);

    /**
     * @brief column vector b in the system : AX=b
     * 
     */
    std::vector<double> b(size_S-1);

    /**
     * @brief b changes whether it is a call or a put
     * 
     */
    std::string put("PUT");
    std::string call("CALL");
    int sign,i;
    if (put.compare(CT)==0){
        sign=1;
        i=0; 
    }
    else {
        if (call.compare(CT)==0){
            sign=-1;
            i = b.size()-1;
        }
        else {
            throw "bad argument : choose either PUT or CALL";
        }
    }
    /**
     * @brief Calculus of C at time ttilde = 0 for stilde in [-ln(L/K),ln(L/K)[
     * 
     */
    double k = 2*r_/pow(sigma_,2);
    for (int j=0; j<static_cast<int>(b.size());j++){
            b[j]=exp(new_maillage_S[j+1]*(k-1)/2)*std::max(0.,sign*(1-exp(new_maillage_S[j+1])));
    }

    /**
     * @brief Calculus of C at each time ttilde in ]0,T*sigma2 / 2] for s in [-ln(L/K),ln(L/K)[
     * 
     */
    std::vector<double> new_b(size_S-1);
    for (int j=1;j<=size;j++){
        /**
         * @brief We add the limit condition
         * 
         */
        algebra::add_Lambda(b,exp(new_maillage_S[i]*(k-1)/2 + pow(k+1,2)*pow(sigma_,2)*(T_-maillage_t[size-j])/4)*k1*exp(-r_*(maillage_t[size-j]-T_)),i);

        /**
         * @brief We then solve the system AX=b
         * 
         */
        new_b=A.resolution(b);

        /**
         * @brief We add the values of Ctilde at each iteration.
         * 
         */
        C[size-j]=b;

        /**
         * @brief We change b for the next iteration.
         * 
         */
        b=algebra::prod_Vect(k3,new_b);
    }
    return C;
}
