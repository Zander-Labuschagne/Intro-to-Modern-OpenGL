//
// Created by zander on 2017/12/26.
//

#include "include/Shader.h"

//3 Helper methods/funksies - sooo kom hulle nie in die header nie??
static std::string load_shader(const std::string &file_name);
static void check_shader_err(GLuint shader, GLuint flag, bool is_program, const std::string err_message);
static GLuint create_shader(const std::string &text, GLenum shader_type);

Shader::Shader(const std::string &file_name)
{
	m_program = glCreateProgram(); //Maak OpenGL program en OpenGL gee vir ons 'n nommer=m_program om na die program te verwys
	//Nou moet ons ons shaders maak(Vertex, Fragment ens):
	m_shaders[0] = create_shader(load_shader(file_name + ".vs.glsl"), GL_VERTEX_SHADER); // Maak 'n vertex shader deur die kode inhoud van die shader file/program te stuur
	m_shaders[1] = create_shader(load_shader(file_name + ".fs.glsl"), GL_FRAGMENT_SHADER); // Maak 'n fragment shader

	//Add shaders na over-arching shader program
	for (GLuint m_shader : m_shaders) //Range-based for loop
		glAttachShader(m_program, m_shader); // Add die shaders na die shader program

	glBindAttribLocation(m_program, 0, "position"); //Sal later hierna terug kom
	glBindAttribLocation(m_program, 1, "texture_coordinate"); //Stel die attribute in Vertex klas gelyk aan die attribute variable in die vertex shader
	glBindAttribLocation(m_program, 2, "normal");

	//Link die shaders vir compilation en validate die shaders
	glLinkProgram(m_program); // Hierdie kan fail so dis hoekom ons 'n check_err funksie het
	check_shader_err(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: "); //Check vir link_status error/flag en concattenate die OpenGL error agterna

	glValidateProgram(m_program); // As linking suksesvol was kyk of die program valid is
	check_shader_err(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: "); //Check of die program validated properly

	m_uniforms[TRANSFORM_UNIFORM] = glGetUniformLocation(m_program, "transform_matrix"); //Kry die adres van 'n uniform: program van waar ons die uniform soek, naam van uniform


}

Shader::~Shader()
{
	for (GLuint m_shader : m_shaders) {
		glDetachShader(m_program, m_shader); //Haal shaders uit program uit
		glDeleteShader(m_shader);
	}

	glDeleteProgram(m_program); // Delete die program sodat hy van die GPU af kan kom
}

void Shader::bind()
{
	glUseProgram(m_program);
}

void Shader::update(const Transform &transform, const Camera &camera)
{
	//update die uniforms
	//par: uniform wat ons wil update, hoeveel goed ons in stuur, of ons matriks wil transpose, actual data
	glm::mat4 model = camera.get_view_projection() * transform.get_model();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_UNIFORM], 1, GL_FALSE, &model[0][0]); //4x4 matrix containing float values
}

/*
 * Kry file name van shader program, load sy content na string reg vir compilation
 */
static std::string load_shader(const std::string &file_name)
{
	std::ifstream file; //Ek dink die is C++
	file.open(file_name.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
		while (file.good()) { // Wat die hel is die????
			getline(file, line); //getline(ifstream, line)
			output.append(line + "\n");
		}
	else
		std::cerr << "Unable to load shader: " << file_name << std::endl;

	return output; //Maak ons nie die file toe nie?
}

/*
 * Exception handling
 * Wanneer shader compile word kan daar compilation errors wees
 * Die method soek die errors as daar is en gee hulle vir ons
 * is_program=true check die over-arching program
 * is_program=false check die individuele shaders
 */
static void check_shader_err(GLuint shader, GLuint flag, bool is_program, const std::string err_message)
{
	GLint success = 0;
	GLchar err[1024] = {0};

	if (is_program)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (is_program)
			glGetProgramInfoLog(shader, sizeof(err), NULL, err);
		else
			glGetShaderInfoLog(shader, sizeof(err), NULL, err);
		std::cerr << err_message << ": '" << err << "'" << std::endl;
	}
}

/*
 * Maak die shader
 * ontvang text wat full text van die shader program is
 * compile die text en build
 * sit dit in die GLuint shader en return dit
 */
static GLuint create_shader(const std::string &text, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);

	if (shader == 0) // Dan bestaan shader nie want OpenGL het nie een vir ons terug gestuur nie, want hy is 0 (soos memory wat vol is of iets)
		std::cerr << "ErrorL Shader creation failed" << std::endl;

	const GLchar *shader_source_strings[1];
	GLint shader_source_string_lengths[1];
	shader_source_strings[0] = text.c_str();
	shader_source_string_lengths[0] = text.length(); //Want die OpenGL C kode kan nie die length van 'n c_str kry nie

	//die shader, hoeveel shaders ons compile, die source code van die shaders, die length van die source code van die shaders
	glShaderSource(shader, 1, shader_source_strings, shader_source_string_lengths); //Die manier hoe hierdie funksie geimplementeer is is afhangend van jou GPU
	glCompileShader(shader);

	check_shader_err(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}