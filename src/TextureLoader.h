#pragma once
#include <vector>
#include <Windows.h>
#include<gl\GL.h>
#include <gl\GLU.h>
#include "soil\src\SOIL.h"
#include <string>


class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static GLuint TextureLoader::LoadGLTextures(std::string file);                                   // Load Bitmaps And Convert To Textures

private:
//	std::vector<GLuint> textures;



};

