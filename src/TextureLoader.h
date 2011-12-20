#pragma once
#include <Windows.h>
#include<gl\GL.h>
#include <gl\GLU.h>
#include "soil\src\SOIL.h"
#include <string>
#include <vector>


class TextureLoader
{
public:
	TextureLoader(void);
	~TextureLoader(void);
	static GLuint LoadGLTextures(std::string file, int newid = 0);                                   // Load Bitmaps And Convert To Textures

private:
//	std::vector<GLuint> textures;



};

