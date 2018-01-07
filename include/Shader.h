//
// Created by zander on 2017/12/26.
//

/*
 * Die actual shader programme word in aparte files geskryf... :. nie hier nie
 * Hierdie klas gaan die shader programme load
 * En dan build/compile vir GPU
 * En dan die build files na die GPU stuur
 */

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

#include "../include/Transform.h"
#include "../include/Camera.h"

class Shader
{
public:
	Shader(const std::string &file_name);
	virtual ~Shader();

	void bind(); // Set die GPU in toestand(state) om vertex en fragment shaders wat deel is van die spesifieke klas is te gebruik (bind die shaders????)
	//:. ^ As ek reeds ander shader funksies gebruik, die bind funksie se moenie meer aanhoud die built in shader funksies gebruik nie(hou op om hulle te gebruik) maar(en) gebruik eerder die wat deel is van hierdie klas
	void update(const Transform &transform, const Camera &camera); //update al die uniforms in array na nuwe waardes

protected:
private:
	Shader(const Shader &other) {} // Implementeer sommer hier want hulle doen niks -> bestaan nie
	void operator = (const Shader &other) {} //Leeg want hulle doen niks

	static const unsigned int NUM_SHADERS = 2; // 2 GLuint shaders -> Vertex en Fragment Shaders (Basics) | Kan ook 'n enumerator gebruik vir die

	//enumerator om ons lewe makliker te maak as ons heeltyd uniforms by sit
	enum//het nommers om ons te help verwys na ons verskillende uniforms
	{
		TRANSFORM_UNIFORM,

		NUM_UNIFORMS//Laaste een is maar soos 'n length ding sodate ons weet hoeveel ons het
	};

	//Shaders is GLuints----------
	GLuint m_program;// glew unigned integer : OpenGL gebruik die om track te hou van waar die program is ('n handle)
	GLuint m_shaders[NUM_SHADERS]; // Array want die twee wat ons maak is nie die enigste twee tipes Shaders wat ons kan maak nie -> Daar is bv Geometry Shaders,
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
