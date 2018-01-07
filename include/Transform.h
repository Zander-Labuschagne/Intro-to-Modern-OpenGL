//
// Created by zander on 2017/12/26.
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

/*
 * Transforming out object and moving it around in space
 * Kan ook 'n struct maak
 */

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> //Al die transformasie funksies

class Transform
{
public: //Kyk die!??
	Transform(const glm::vec3 &position = glm::vec3(), const glm::vec3 &rotation = glm::vec3(), const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		m_position(position),
		m_rotation(rotation),
		m_scale(scale) {}

	//Convert ons position, rotation en scale na 'n matrix
	//mat4 is 4x4 matriks
	//n matriks wat posisie, rotasie en scale bevat word 'n model matriks genoem of world matriks
	inline glm::mat4 get_model() const//const want hy gaan nie position, rotation of scale verander nie
	{
		glm::mat4 position_matrix = glm::translate(m_position); //Ingeboude funksie om die translasie matriks te kry vanaf die posisie
		glm::mat4 rotation_X_matrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));//Rotasie om x as: hoeveelheid roteer vanuit ons vector, die as vir rotasie soos x
		glm::mat4 rotation_Y_matrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));//Rotasie om y as
		glm::mat4 rotation_Z_matrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));//Rotasie om z as
		glm::mat4 scale_matrix = glm::scale(m_scale);
		//Nou het ons 5 matrikse wat ons kan gebruik om ons objek/wereld/model voor te stel
		//Matriks eienskap: matriks vermenigvuldig kombineer 2 of meer matrikse in een maar verskillende volgordes gee verskillende resultate
		glm::mat4 rotation_matrix = rotation_Z_matrix * rotation_Y_matrix * rotation_X_matrix; //matriks vermenigvuldiging werk van regs af

		return position_matrix * rotation_matrix * scale_matrix; //Doen posisie laaste anders roteer hy om 'n as in die wereld waar hy was en nie om sy eie as nie
	}

	//Accessors
	//Return reference want ons wil nie get en dan verander en dan weer set nie, as ons wil verander/update dan wil ons verander/update
	inline glm::vec3 &get_position() { return m_position; }
	inline glm::vec3 &get_rotation() { return m_rotation; }
	inline glm::vec3 &get_scale() { return m_scale; }

	//Mutators
	inline void set_position(const glm::vec3 &position) {m_position = position; }
	inline void set_rotation(const glm::vec3 &rotation) {m_rotation = rotation; }
	inline void set_scale(const glm::vec3 &scale) {m_scale = scale; }

protected:
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif //TRANSFORM_H
