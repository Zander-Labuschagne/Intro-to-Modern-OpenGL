//
// Created by zander on 2017/12/26.
//

#include "include/Mesh.h"

Mesh::Mesh(Vertex *vertices, unsigned int num_vertices, unsigned int *indices, unsigned int num_indices)
{
	//m_draw_count = num_vertices;
	IndexedModel model;

	for (unsigned int i = 0; i < num_vertices; i++) {
		model.positions.push_back(*vertices[i].get_position());
		model.texCoords.push_back(*vertices[i].get_texture_coordinate());
		model.normals.push_back(*vertices[i].get_normals());
	}

	for(unsigned int i = 0; i < num_indices; i++)
		model.indices.push_back(indices[i]);

	init_mesh(model);
}

Mesh::Mesh(const std::string &file_name)
{
	IndexedModel model = OBJModel(file_name).ToIndexedModel(); //Convert na indexed model nadat obj file/model geload is
	init_mesh(model);
}

void Mesh::init_mesh(const IndexedModel &model)
{
	m_draw_count = model.indices.size();


	// 1 vertex array object generate, stoor in m_vertex_array_object
	glGenVertexArrays(1, &m_vertex_array_object);
	glBindVertexArray(m_vertex_array_object); //Dis hoe ons die vertex array object gebruik

	//1ste attribute
	//Buffer is 'n blok data op GPU
	//OpenGL verwys na data op GPU deur buffer
	glGenBuffers(NUM_BUFFERS, m_vertex_array_buffers);//Array word klaar gestoor as pointer so klaar pass by reference
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[POSITION_VB]);//Enige OpenGL funksie wat buffers affekteer sal nou ons buffer affekteer
	//GL_ARRAY_BUFFER se vir OpenGL hoe om ons data m_vertex_array_buffers te interpreteer
	//num_vertices * sizeof(verttices[0]) gee die totale groote van die data blok/buffer
	//glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW); //Vat data vanaf RAM en skuif na GRAM behalwe met integrated graphics
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //Updated vir texture
	//GL_STATIC_DRAW argument se waar in GPU moet ons die data stoor
	//GL_STATIC_DRAW se ons gaan nie aan die data verander nie :. stoor in plek met vinniger access maar behoort stadige write spoed te he

	//Die data is nou op die GPU

	//Nou moet ons vir OpenGL se hoe om die data te interpreteer om te teken
	glEnableVertexAttribArray(0); //Deel al ons data op in attributes bv:
	//as ek position en color attributes het in my Vertex klas dan in realiteit is dit pos col pos col pos col :. alternating maar:
	//die GPU soek sequential array van data so die vertex atrrib array maak dit sequential pos pos pos pos pos pos col col col col ens.
	//Kan baie attributes he
	//Die boonste statement se daar gaan attributes array wees -> se vir OpenGL ons gaan vir hom se hoe om dit as array te lees
	//Onderste een se vir OpenGL hoe om dit as array te lees-
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//which attribute array its part of, how many pieces of data(vec3):.3, tipe van data->glm stoor as float, ons wil nie normalize nie->false, hoeveel data attributes om te skip voor volgende attribute, hoe ver om vanag begin te begin om eersta attribute te kry

	//2de attribute
	//Doen nou dieselfde as bo set up nog 'n buffer vir die coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[TEXTURE_COORDINATE_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	//Die data is nou op die GPU
	//Nou moet ons vir OpenGL se hoe om die data te interpreteer om te teken
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertex_array_buffers[INDEX_VB]); //ELEMENT ARRAY BUFFER is nie buffer vir array nie maar buffer vir array met elemente vir ander array :. reference ander array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	//vir die lighting
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);//which attribute array its part of, how many pieces of data(vec3):.3, tipe van data->glm stoor as float, ons wil nie normalize nie->false, hoeveel data attributes om te skip voor volgende attribute, hoe ver om vanag begin te begin om eersta attribute te kry

	//glBindVertexArray(1);//Unbind vertex array object
	glBindVertexArray(0);//Unbind vertex array object
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertex_array_object);
}

/*
 * Vat mesh en stuur dit na GPU en teken die mesh
 * Die mesh is wat deur die pyplyn beweeg
 */
void Mesh::draw()
{
	glBindVertexArray(m_vertex_array_object);
						//indices is unsigned int
	glDrawElements(GL_TRIANGLES, m_draw_count, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, m_draw_count); //Mode:3hoeke en 3hoek variants en lyne en punte, waar in die array om te begin, hoe ver ons wil lees(hoeveel vertices)

	glBindVertexArray(0);
}