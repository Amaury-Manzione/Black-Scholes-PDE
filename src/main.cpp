#include "crank.h"
#include "reduite.h"
#include<vector>
#include <iostream>
#include<string>

int main(){
    try{
        crank test = crank();
        std::string put("PUT");
        std::string call("CALL");
        reduite test2 = reduite();

        std::vector< std::vector<double> > res = test.sol_edp(put);
        std::vector< std::vector<double> > res2 = test2.sol_edp(put);

        /**
         * @brief ploting put prices C(0,s) for s in [0,L] 
         * with crank-nichelson method
         * 
         */
        std::cout << "put option prices with crank-nichelson method" << std::endl; 
        for (int i=0;i<50;i++){std::cout<<i<<" : "<<res[0][i]<<std::endl;}
        std::cout << "" << std::endl;
        /**
         * @brief ploting put prices C(0,s) for s in [0,L] 
         * with heat equation method
         * 
         */
        std::cout << "put option prices with heat equation method" << std::endl; 
        for (int i=0;i<50;i++){std::cout<<i<<" : "<<res2[0][i]<<std::endl;}

        std::vector<double> v1(999);
        std::vector<double> v2(999);
        
        /**
         * @brief initialazing vectors for the plot
         * 
         */
        for (int i=0;i<999;i++){
            v1[i] = res[0][i];
            v2[i] = res2[0][i];
        }

        /**
         * @brief creating new window
         * 
         */
        //sdl fw(500,500);
       
        /**
         * @brief ploting v1 and v2
         * 
         */
        //fw.draw_function(v1);
        //fw.draw_function(v2);
        
        //SDL_Event event;
        /*
        while( !(event.type == SDL_QUIT )){
        	SDL_Delay(10);
        	SDL_PollEvent(&event);
        }
        */
    }

    catch(const char * s){
        std::cout << s;
	}
    return 0;
}
