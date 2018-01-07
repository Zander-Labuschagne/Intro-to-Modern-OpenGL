//
// Created by zander on 2017/12/26.
//

/*
 * Load texture vanaf file of drive
 * Die klas gebruik stb_image om textures te load
 */

#include "include/Texture.h"

Texture::Texture(const std::string &file_name)
{
	int width, height, num_components;
	unsigned char * image_data = stbi_load(file_name.c_str(), &width, &height, &num_components, 4); //Gebruik die om textures te load

	if (image_data == NULL)
		std::cerr << "Texture Loading failed for texture: " << file_name << std::endl;

	//Onthou OpenGL stoor alles in buffers so ons maak 'n buffer om spasie vir texture te kry
	glGenTextures(1, &m_texture); //Generate space for 1 texture, by m_texture se adres
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Soos exception handling om te hanteer wanneer daar buite die texture map gelees word, een vir x, een vir y
	//GL_REPEAT spesifiseer wat gebeur dan -> soos tiling, lees dan pixel 1 by 513 bv; GL_CLAMP sal bv swart lees
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Moenie die gebruik nie
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//Werk nie
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Die eerste argument spesifiseer die tipe texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Hanteer wanneer die hoeveelheid pixels gealokeer is nie gelyk is aan die texture se pixels nie
	//Doen interpolasie wanneer texture gewarp word soos bv rotasie
	//GL_LINEAR se linear interpolasie; GL_NEAREST; GL_CUBIC??? TODO: Test this
	//glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Moenie die gebruik nie
	//glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Werk nie
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//Minification
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//Magnification Wanneer texture minder pixels gebruik as die resolution

	//Stuur texture na GPU
	//Tipe texture, mipmapping level, 0=default mipmapping level, formaat van pixels, width van texture, height van texture, 1 vir 1 pixel wydte border, input format van data wat na GPU gestuur word, tipe van image_data -> unsigned char, pixel data
	//Mipmapping: 128x128, 256x256, 512x512, 1024x1024 textures en gebruik hoer resolusie wanneer kamera naby is en laer resolusie wanneer kamera verder is
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	//Die kan dalk na destructor toe skuif
	stbi_image_free(image_data); //Gebruik om textures te delete
}

Texture::~Texture()
{
	//delete 1 texture, by m_texture
	glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned int unit)
{
	//OpenGL kan net 32 textures op 'n slag gebruik
	assert(unit >= 0 && unit <= 31); //Maak seker unit is binne perke

	glActiveTexture(GL_TEXTURE0 + unit);// gebruik die om textures te ruil wanr ons kan met baie werk so nou werk ons met 0, ons enigste texture
	//Die +unit is daar om groot switch te vermy dan + ons net ons unit by 0 om die regte texture te kry
	glBindTexture(GL_TEXTURE_2D, m_texture);
}