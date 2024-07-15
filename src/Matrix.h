/**
 * @file projet.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <vector>

#ifndef MATRIX_H
#define MATRIX_H

namespace algebra{
    class Matrix{
        private:
            std::vector<double> bot_;
            std::vector<double> mid_;
            std::vector<double> top_;
        public:
            /**
             * @brief Construct a new Matrix object
             * 
             */
            Matrix();

            /**
             * @brief Construct a new Matrix object
             * 
             * @param bot 
             * @param mid 
             * @param top 
             */
            Matrix(double bot,double mid,double top,int N);

            /**
             * @brief Construct a new Matric object
             * 
             * @param bot 
             * @param mid 
             * @param top 
             */
            Matrix(std::vector<double> bot,std::vector<double> mid,std::vector<double> top);

        public:
            /**
             * @brief Get the bot object
             * 
             * @return std::vector<double> 
             */
            std::vector<double> get_bot() const{return bot_;};

            /**
             * @brief Get the mid object
             * 
             * @return std::vector<double> 
             */
            std::vector<double> get_mid() const{return mid_;};

            /**
             * @brief Get the top object
             * 
             * @return std::vector<double> 
             */
            std::vector<double> get_top() const{return top_;};


            /**
             * @brief Get the size object
             * 
             * @return int 
             */
            int get_size() const{ return mid_.size();};

            /**
             * @brief Set the bot object
             * 
             * @param bot 
             */
            void set_bot(std::vector<double> bot) { bot_ = bot;};

            /**
             * @brief Set the mid object
             * 
             * @param mid 
             */
            void set_mid(std::vector<double> mid) { mid_ = mid ;};

            /**
             * @brief Set the top object
             * 
             * @param top 
             */
            void set_top(std::vector<double> top) { top_ = top ;};

        public:
            /**
             * @brief Resous AX=b avec A tridiagonal et b vecteur colonne
             * 
             * @param b 
             * @return std::vector<double> 
             */
            std::vector<double> resolution(const std::vector<double> & b) const;

            /**
             * @brief operator for dot product
             * 
             * @param vect 
             * @return std::vector<double>& 
             */
            friend std::vector<double> operator*(const Matrix & mat,const std::vector<double>  & vect);
        
    };

    /**
     * @brief Fais le produit d'un vecteur colonne par un scalaire : lambda * v
     * 
     * @param lambda 
     * @param v 
     * @return std::vector<double> 
     */
    std::vector<double> prod_Vect(double lambda, const std::vector<double> & v);

    /**
     * @brief Ajoute lambda a la i-ème composante de v (utile pour rajouter la condition initiale)
     * 
     * @param v 
     * @param lambda 
     * @param i 
     * @return std::vector<double> 
     */
    std::vector<double> add_Lambda(std::vector<double> & v,double lambda, int i);
}

#endif 