//
// Created by zander on 2017/12/26.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 &position, float fov, float aspect, float z_near, float z_far) //z_far is die verste wat ons objects kan sien, ons wys hom nie as hy so ver is nie; z_near is die naaste wat ons object sien, voor ons oe en dan verby
	{
		m_perspective = glm::perspective(fov, aspect, z_near, z_far);
		m_position = position;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 get_view_projection() const
	{
		//par: camera position, where we want to look AT, up direction
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}
protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward; //n normaal voorentoe direction
	glm::vec3 m_up; //n normaal op direction
};

#endif //CAMERA_H
