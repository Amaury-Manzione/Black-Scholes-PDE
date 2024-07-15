/**
 * @file Matrix.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Matrix.h"
#include <vector>

namespace algebra{
    Matrix::Matrix() : bot_(std::vector<double>({0})) , mid_(std::vector<double>({0})) , top_(std::vector<double>({0})) {}

    Matrix::Matrix(std::vector<double> bot,std::vector<double> mid,std::vector<double> top) : bot_(bot) , mid_(mid) , top_(top) {}

    Matrix::Matrix(double bot,double mid,double top,int N) : Matrix(){    
        bot_.resize(N-1);
        mid_.resize(N);
        top_.resize(N-1);

        for(int i = 0; i< N-1; i++){
            bot_[i] = bot;
            mid_[i] = mid;
            top_[i] = top;
        }

        mid_[N-1] = mid;
    }

    std::vector<double> operator*(const Matrix & mat,const std::vector<double>  & vect){
        int len = vect.size();
        std::vector<double> new_vect(len);

        if ( mat.get_size() != len ){
            throw "erreur d'index";
        }

        if (len < 2){
            throw "erreur d'index";
        }

        // treating initial and final case apart 
        new_vect[0] = mat.get_mid()[0]*vect[0] + mat.get_top()[0]*vect[1];
        new_vect[len-1] = mat.get_bot()[len-2]*vect[len-2] + mat.get_mid()[len-1]*vect[len-1];

        for(int i = 1; i < len-1 ; i++){
            new_vect[i] = mat.get_bot()[i-1]*vect[i-1] + mat.get_mid()[i]*vect[i] + mat.get_top()[i]*vect[i+1];
        }

        return new_vect;
    }

    std::vector<double> Matrix::resolution(const std::vector<double> & b) const{
        int size=b.size();
        if ( get_size() != size){
            throw "error : bad index";
        }

        if ( size < 2){
            throw "error : bad index";
        }

        std::vector<double> z(size);
        std::vector<double> y(size);
        std::vector<double> top = get_top();
        std::vector<double> mid = get_mid();
        std::vector<double> bot = get_bot();
        z[0]=top[0]/mid[0];
        y[0]=b[0]/mid[0];
        for (int i=1; i<size;i++){
            z[i]=top[i]/(mid[i]-bot[i]*z[i-1]);
            y[i]=(b[i]-bot[i]*y[i-1])/(mid[i]-bot[i]*z[i-1]);
        }
        std::vector<double> x(size);
        x[size-1]=y[size-1];
        for(int i=1;i<=size;i++){
            x[size-i]=y[size-i]-z[size-i]*x[size-i+1];
        }
        return x;
    }

    std::vector<double> prod_Vect(double lambda, const std::vector<double> & v){
        int size = v.size();
        std::vector<double> res(size);
        for (int i=0;i<size;i++){
            res[i]=lambda*v[i];
        }
        return res;
    }

    std::vector<double> add_Lambda(std::vector<double> & v,double lambda, int i){
        if(i<0 || i>static_cast<int>(v.size())){
            throw "error : bad index";
        }
        v[i]=lambda + v[i];
        return v;
    }
}    