#include <SDL2/SDL.h>
#include<vector>

class sdl{
public:
    private:
    /**
     * @brief Height and width of the window
     * 
     */
    int height;    
    int width;      

    public:
    SDL_Renderer *renderer = NULL;  
    
    /**
     * @brief Construct a new sdl object
     * 
     * @param height_ 
     * @param width_ 
     */
    sdl(int height_, int width_): height(height_), width(width_){
        SDL_Init(SDL_INIT_VIDEO);     
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        /**
         * @brief set draw color 
         * 
         */
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);     
        /**
         * @brief / Reflects the changes done in the
        window
         * 
         */
        SDL_RenderPresent(renderer);    
    }

    /**
     * @brief Destroy the sdl object
     * 
     */
    ~sdl(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    
    /**
     * @brief draw a std::vector on the window
     * 
     * @param v1 
     */
    void draw_function(std::vector<double> &v1) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
 
    
    int n = v1.size();
    double v1_min = 0.0;
   
 	double v1_max = v1[0];
    /**
     * @brief loop that find maximum element of v1
     * 
     */
    for (int i =1; i < n;i++){
        if (v1[i] > v1_max)
            v1_max = v1[i];
 	}
    
    /**
     * @brief Scale the values in the input vectors to fit within the window bounds
     * 
     */
    for (int i = 0; i < n; i++) {
        v1[i] = height-  (((v1[i] - v1_min) / (v1_max - v1_min))* height);
    }
    
    /**
     * @brief plot the scaled points
     * 
     */
    for (int i = 0; i < n; i++) {
        SDL_RenderDrawPoint(renderer,i,static_cast<int>(v1[i]));
    }
    SDL_RenderPresent(renderer);
}


};
