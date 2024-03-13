#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>


struct vertex
{
	float x, y, z, r, g, b, u, v;
};

class Kube
{
public:
	std::vector<vertex>mVertices;
	//eller (til å lagre objektets eget origo
	glm::vec3 position;
		std::string name;
	//legge inn en variable(for kuben posisjons greier me thinks)
	Kube (float storrelse = 1.0f);
private:
	float a{ 1.0f };
};


