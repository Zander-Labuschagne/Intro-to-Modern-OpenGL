//
// Created by zander on 2017/12/25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h> //SDL goed
#include <GL/glew.h> //OpenGL funksies

class Display
{
public:
	Display(int width, int height, const std::string &title);
	virtual ~Display();

	bool is_closed();

	void clear_display(float r, float g, float b, float a);
	void update_display(); //Vir die dubble buffer ding -> Sien Display.cpp implementering l:21 en boek figuur 2

protected:
private:
    	Display(const Display &other) {} // Copy Constructor
    	//Display& operator = (const Display &other) {} // Operator Overloading
	void operator = (const Display &other) {} // Operator Overloading //Want ons return niks

	SDL_Window *m_window; //Pointer sodat ek nie die hele window hier in Display store nie
	SDL_GLContext m_glContext; //OpenGL Context -> Sien boek figuur 1

	bool m_is_closed; //die m_ is maar convention om "member" of "class member" voor te stel <- sal maar sien
};


#endif //DISPLAY_H
