#include "TextureLoader.h"


TextureLoader::TextureLoader(void)
{
}


TextureLoader::~TextureLoader(void)
{
}

GLuint TextureLoader::LoadGLTextures(std::string file, int newid) {                                  // Load Bitmaps And Convert To Textures
	GLuint temp = 0;
    std::string fileLocation = "textures/" + file;
	/* load an image file directly as a new OpenGL texture */
    temp = SOIL_load_OGL_texture (
		fileLocation.c_str(),
        SOIL_LOAD_AUTO,
 //       SOIL_CREATE_NEW_ID,
		newid,
		SOIL_FLAG_INVERT_Y
	);
 
 //   if(temp == 0)
	//	temp = SOIL_load_OGL_texture (
	//	"textures/default.jpg",
 //       SOIL_LOAD_AUTO,
	//	newid,
 //       SOIL_FLAG_INVERT_Y
	//);
	
	if(temp) { 
		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, temp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
 
    return temp;                                        // Return Success
}