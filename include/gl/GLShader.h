// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "geo/Matrix.h"
#include <string>
#include <SDL2/SDL_opengl.h>

namespace GL_
{

class Shader
{
public:
	Shader();
	~Shader();
	// Load the vertex/fragment shaders with the given names
	bool load(const std::string &vertName, const std::string &fragName);
	void unload();
	// Set this as the active shader program
	void setActive();
	// Sets a Matrix uniform
	void setMatrixUniform(const char* name, const geo::Matrix4x4f &matrix);
private:
	// Tries to compile the specified shader
	bool compileShader(const std::string& fileName,
					   GLenum shaderType,
					   GLuint& outShader);
	
	// Tests whether shader compiled successfully
	bool isCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool isValidProgram();
private:
	// Store the shader object IDs
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};

}
