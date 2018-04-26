#ifndef InputManager_H

#define InputManager_H

#define K_UP 0
#define K_DN 1
#define K_RT 2
#define K_LT 3

class InputManager {
        int key_held[4];
        void Reset();
    public:
        InputManager();
        int HandleEvent();
    	
        int IsKeyUpPressed();
        int IsKeyDownPressed();
        int IsKeyLeftPressed();
        int IsKeyRightPressed();
		
        int IsDirectionPressed();
};

#endif