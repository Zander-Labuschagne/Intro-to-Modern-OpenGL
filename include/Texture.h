//
// Created by zander on 2017/12/26.
//

#ifndef TEXTURE_H //Header guards
#define TEXTURE_H

#include <string>
#include <iostream>
#include <cassert>

#include <GL/glew.h>

#include "../include/stb_image.h"

class Texture
{
public:
	Texture(const std::string &file_name);
	virtual ~Texture();

	//ons kan baie textures op 'n slag bind ~32 textures
	//unit spesifiseer watter texture is watter een
	void bind(unsigned int unit=0); //Set OpenGL op vit texture
protected:
private:
	Texture(const Texture &other){}
	void operator = (const Texture &other){}

	GLuint m_texture;
};


#endif //TEXTURE_H
