#include "../include/Display.h"
#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Texture.h"
//#include "../include/Transform.h"
//#include "../include/Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char **argv)
{
	//{  // Maar net om die funksionaliteit van die braces voor te stel
		std::cout << "Before Display" << std::endl;
		Display display(WIDTH, HEIGHT, "Hello OpenGL");
		std::cout << "After Display" << std::endl;
	//}

	//Setup example mesh
	//vec3 is -1 tot 1 :. -1 vir x is links, +1 vir x is regs; -1 vir y is onder; +1 vir y is bo
	Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)), Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 1.0)), Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0))};

	unsigned int indices[] = {0, 1, 2};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); //Number of bytes of array / number of bytes 1 element vat = hoeveelheid elemente
	Mesh mesh_3d_model("./res/models/monkey3.obj");

	Shader shader("./res/basic_shader");

	Texture texture("./res/texture/bricks.jpg");

	//70.0f is ~ wat mens se oe sien in grade    //aspect ratio           //naby oog
	Camera camera(glm::vec3(0, 0, -4), 70.0f, (float)WIDTH /(float)HEIGHT, 0.01f, 1000.0f);

	Transform transform;

	std::cout << sizeof(vertices) / sizeof(vertices[0]) << std::endl;

	float counter = 0.0f;

	while (!display.is_closed()) {// Soos 'n while (true) om die program aan die gang te hou
		display.clear_display(0.0f, 0.15f, 0.3f, 1.0f); //Wys blou venster

		float sin_counter = sinf(counter);
		float cos_counter = cosf(counter);

		transform.get_position().x = sin_counter;
		transform.get_position().z = cos_counter;
		transform.get_rotation().z = counter;//cosf(counter);
		transform.get_rotation().y = counter + 180;//cosf(counter);
		transform.get_rotation().x = counter;//cosf(counter);

		//transform.set_scale(glm::vec3(cos_counter, cos_counter, cos_counter));

		shader.bind(); //Gebruik hom wanneer ons iets teken vir die kleur ->
		texture.bind(0); //Gebruik die texture wanneer draw
		shader.update(transform, camera); //All die vertices vermenigvuldig met die matriks in paralel om te transformeer
		//mesh.draw(); //Ek het lenient graphics driver so ek kan wit 3hoek sien met slegs die een sonder shader
		mesh_3d_model.draw();

		display.update_display(); // Update die screen -> display.swap_buffers;
		counter += 0.01f; //spoed van rotasie hang af van processor spoed, ek dink CPU spoed?
	}

	std::cout << "Before return 0" << std::endl;

	return 0;

	std::cout << "After return 0" << std::endl;
}