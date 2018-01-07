//
// Created by zander on 2017/12/25.
//
#include "../include/Display.h"

Display::Display(int width, int height, const std::string &title)//ctor
{
	std::cout << "Constructor" << std::endl;

	m_is_closed = false; // want ons is nie toe nie ons maak nou net oop pfffft..

	//Begin SDL instance
	SDL_Init(SDL_INIT_EVERYTHING);//Moenie die doen wanneer ek SDL vir meer as net windowing wil gebruik nie (Dan doen die buite iewers dalk? in main of iets?)

	//Set addisionele parameters wat nie deel is van create window method is nie
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // Number of bits used to display red colors, so 2^8=256 kleure
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // Die mens se oog sien ~256 kleure
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // Minder sal leliker lyk, meer sal mens nie verskil sien nie maar kan dalk stadiger wees
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // Vir transparency... is soveel regtig nodig ?
	// ^ Die is as one OpenGL gebruik vir Window // 32-bits=4 bytesper pixel  se kleur data
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //Set die hoeveelheid data in bits SDL sal alokeer vir 'n enkele pixel
	// SDL sal dan TEN MINSTE 8 en 32 bits gee nie noodwendig presies 8 of 32 nie
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //16 is gewoonlik genoeg kan ook 32 maak of 24 //nodig om nie toe te laat dat agterkant pixels voorkat overwrit enie
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Alokeer spasie vir 2 windows al wys ons net een, maar daar kan nog steeds op die tweede een geteken word al wys hy nie

	//SDL_CreateWindow(Title, x/y posisie, x/y posisie, window width, window height, gebruik OpenGL nie ander SDL goed nie om window te teken)
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); // SDL_Window is C, nie C++ so convert die C++ string na c_str sodat C kan voort gaan met die "string". Sien ook figuur 1.1 in boek
	m_glContext = SDL_GL_CreateContext(m_window); // Nou kan ons in die window of eerder Display wat ons opgestel het teken -> Sien boek figuur 1.2 oor OpenGL wat beheer neem(blou)

	//Die is GLEW construct/enumerator
	GLenum status = glewInit(); //Soek deur OS en vind elke liew OpenGL funksie wat die OS support
	if (status != GLEW_OK) //Wel dan het ons 'n probleem, die OS support nie ons objective nie
		std::cerr << "GLEW failed to initialize" << std::endl;
	//Nou het ons toegang tot OpenGL funksies en kode

	glEnable(GL_DEPTH_TEST); //nou sal hy nie toelaat dat agterkant pixels voorkant pixels overwrite nie
	//^kan dalk duurder wees as om net alles in volgorde te teken, bietjie meer memory

	//die werk net vir konveks models
	//glEnable(GL_CULL_FACE); //Gaan nie die agter kant wat weg kyk van kamera teken nie
	//glCullFace(GL_BACK); //Spesifiseer dat die cull face die agter kan is
}

Display::~Display()//dtor
{
	std::cout << "Destructor" << std::endl;

	//Delete alles wat in RAM gemaak was. Delete hulle in reverse order as waarin hulle created was
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit; //Eindig SDL instance
}

bool Display::is_closed()
{
	return m_is_closed;
}

void Display::clear_display(float r, float g, float b, float a)
{
	//glClearColor(0.0f, 0.15f, 0.3f, 1.0f); //Stel die verstek kleur van die clear color funksie na iets spesifiek
	glClearColor(r, g, b, a); //Stel die verstek kleur van die clear color funksie na iets spesifiek
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear die color buffer -> Fill al die kleure met die specified^ clear kleur
					//^ clear die depth buffer ook
}

//update() die screen
void Display::update_display() //Sien boek figuur 2
{
	SDL_GL_SwapWindow(m_window); //Die sal die buffers ruil. -> Sien boek figuur 2 -> swap_buffers

	//Kom ons handle sommer die events hier ook aangesien dit 'n update funskie is was die screen update
	SDL_Event e; // Storage vir OS event
	while (SDL_PollEvent(&e))//Poll vir enige OS event wat ons dalk kry -> sodat ons die event kan hanteer en sodate die OS nie virewig vir ons wag om die event te hanteer en dink ons respond nie
		if (e.type == SDL_QUIT) // As die user window geclose het dan hanteer ons dit en exit die program
			m_is_closed = true;
}