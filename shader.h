#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFile(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();

	void useShader();
	void cleanShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void compileShader(const char *vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const GLchar* shaderCode, GLenum shaderType);
};