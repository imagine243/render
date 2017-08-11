#include <fstream>
#include <string>

#include "Mesh.h"
#include "rutil.h"

Mesh::Mesh(const char *path, const char * texturePath)
{
		position = vector(0, 0, 0);
		rotation = vector(0, 0, 0);
		scale = vector(1, 1, 1);

		t = new texture(texturePath);

		const char delimiter = ' ';
		std::ifstream meshFIle(path);
		std::string line;

		std::getline(meshFIle, line);
		std::getline(meshFIle, line); 

		std::getline(meshFIle, line);
		auto vs = split(line, delimiter);
		int numOfVertices = atoi(vs[1].c_str());

		std::getline(meshFIle, line);
		auto ts = split(line, delimiter);
		int numOfTriangles = atoi(ts[1].c_str());

		for (int i = 0; i < numOfVertices; i++)
		{
			std::getline(meshFIle, line);
			auto vs = split(line, delimiter);

			float x = atof(vs[0].c_str());
			float y = atof(vs[1].c_str());
			float z = atof(vs[2].c_str());

			float nx = atof(vs[3].c_str());
			float ny = atof(vs[4].c_str());
			float nz = atof(vs[5].c_str());

			float u = atof(vs[6].c_str());
			float v = atof(vs[7].c_str());

			vertices.push_back(Vertex(vector(x, y, z), vector(nx, ny, nz), u, v, color::randomColor()));
		}

		for (int i = 0; i < numOfTriangles; i++)
		{
			std::getline(meshFIle, line);
			auto t = split(line, delimiter);
			int a = atof(t[0].c_str());
			int b = atof(t[1].c_str());
			int c = atof(t[2].c_str());
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
			
		}

		meshFIle.close();
}
