#include "editor.h"



int main() { 
    TTF_Init();
    Editor editor;
    
    editor.iniciar_editor();
    
    TTF_Quit();
    return 0; 
    }


