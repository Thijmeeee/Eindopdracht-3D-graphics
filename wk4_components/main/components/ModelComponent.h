#pragma once

#include "DrawComponent.h"
#include "../tigl.h"
#include "../game/Texture.h"
#include <string>
#include <vector>
#include <list>

using tigl::Vertex;

class Texture;

class ModelComponent : public DrawComponent
{
	std::vector<Vertex> verts;

public:
	ModelComponent(const std::string& filename);
	~ModelComponent(void);


	virtual void draw() override;

private
:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord;
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
		std::vector<tigl::Vertex> model;
	};


	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	void loadMaterialFile(const std::string& fileName, const std::string& dirName);

public
:
	void loadModel();
};
