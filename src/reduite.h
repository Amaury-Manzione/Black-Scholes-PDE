#include "edp.h"
#ifndef REDUIT_H
#define REDUIT_H

class reduite : public edp {
    public : 
        /**
         * @brief 
         * 
         * @param CT : either "PUT" or "CALL"
         * @return std::vector< std::vector<double> > 
         */
        std::vector< std::vector<double> > sol_edp(std::string CT) const;
        std::vector<double> get(){return maillage_S;};
        
};

#endif