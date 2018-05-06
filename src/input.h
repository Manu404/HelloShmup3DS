#ifndef InputMgmt_H

#define InputMgmt_H

#define K_UP 0
#define K_DN 1
#define K_RT 2
#define K_LT 3
#define K_A 4
#define K_SELECT 5
#define K_QUIT 6
#define K_START 7

class InputMgmt {
        int key_held[8];
        void Reset();
    public:
        InputMgmt();

        int HandleEvent();
    	
        int IsKeyUpPressed();
        int IsKeyDownPressed();
        int IsKeyLeftPressed();
        int IsKeyRightPressed();
		
        int IsDirectionPressed();

        int IsKeyAPressed();
        int IsKeySelectPressed();
        int IsStartPressed();

        int IsQuitRequested();
};

#endif