//
// Created by zander on 2017/12/26.
//

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <GL/glew.h> // OpenGL functions
#include <glm/glm.hpp> // OpenGL se math library

#include "../include/obj_loader.h" //basic loader vir die obj file format

/*
 * Data class -> veronderstel om data na OpenGL se interne  formaat te convert en ons wil so naby aan daardie formaat bly as moontlik
 * 	Die formaat van die interne OpenGL data is koordinate(almal tussen -1 en 1), verwag 3 van hulle in sequence om 3hoek voor te stel
 * 	'n Vertex klas gaan 1 van daardie 3 punte voor stel
 * 	Sien boek figuur 3
 * In die toekoms sal ons funksies hier wil add om goed te doen so dis hoekom ons dit in klas sit
 * Maar in die tutorial act hy net as struct met accessors
 */
class Vertex
{
public:
	Vertex(const glm::vec3 &position, const glm::vec2 &texture_coordiante, const glm::vec3 &normal = glm::vec3(0,0,0)) // Implementeer hom sommer net hier
	{
		this->position = position;
		this->texture_coordinate = texture_coordiante;
		this->normal = normal;
	}

	inline glm::vec3 *get_position() { return &position; }
	inline glm::vec2 *get_texture_coordinate() { return &texture_coordinate; }
	inline glm::vec3 *get_normals() { return &normal; }

protected:
private:
	//Die is ons vertex attribute en ons enigste vertex attribute
	glm::vec3 position; // Stoor 3 waardes, x, y, z koordinaat -> Posisie
	//glm::vec3 color; //Sal 'n tweede vertex attribute wees -> kan baie attributes he

	//Nou om textures te support sit ons die by
	glm::vec2 texture_coordinate; // Die is die posisie op die texture map wat ons na die vertex map

	glm::vec3 normal; //'n vector wat die normaal op rigting wys, benodig vir lighting
};

class Mesh
{
public:
	Mesh(Vertex *vertices, unsigned int num_vertices, unsigned int *indices, unsigned int num_indices);
	Mesh(const std::string &file_name);
	virtual ~Mesh();
	void draw(); // Vat doe mesh en teken dit met GPU, die is wat deur die pylplyn beweeg

protected:
private:
	Mesh(const Mesh &other);
	void operator = (const Mesh &other);

	enum //Kan uitbrei hier | enumeration of buffers
	{
		POSITION_VB,
		TEXTURE_COORDINATE_VB, //nog 'n vertex buffer vir die texture coord
		INDEX_VB,
		NORMAL_VB, //die buffer stoor al die normals

		NUM_BUFFERS
	};

	void init_mesh(const IndexedModel &model);

	// Verwys na Mesh data op GPU -> Slegs vanaf OpenGL 3.0
	GLuint m_vertex_array_object; // GLuint is hoe OpenGL na die data op die GPU verwys
	GLuint m_vertex_array_buffers[NUM_BUFFERS];

	unsigned int m_draw_count; //Se vir OpenGL hoeveel van die vertex array object ons wil teken(hoeveel vertices ons wil teken in hierdie geval)
};


#endif //MESH_H
