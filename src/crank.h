#include "edp.h"
#ifndef CRANK_H
#define CRANK_H

class crank : public edp {
    public : 
        /**
         * @brief 
         * 
         * @param CT : either "PUT" or "CALL"
         * @return std::vector< std::vector<double> > 
         */
        std::vector< std::vector<double> > sol_edp(std::string CT) const;
};

#endif