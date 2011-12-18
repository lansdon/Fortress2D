#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <Framework.h>
//#include <openal/include/al.h>
//#include <openal/include/alc.h>

#include <cstdio>

#include "settings.h"
#include "Vector3.h"
#include <vector>
#include <sstream>
#include <map>




//#define NUM_BUFFERS 1
//#define NUM_SOURCES 1
//#define NUM_ENVIRONMENTS 1







class SoundManager
{
public:
	SoundManager(void);
	~SoundManager(void);

	enum Sounds {
		SND_NULL, 
		SND_DOG_MELEE, SND_DOG_MOVE, SND_DOG_DAMAGED, SND_DOG_DEATH, SND_DOG_IDLE,															// wardog
		SND_ARCHER_MELEE, SND_ARCHER_RANGED, SND_ARCHER_MOVE, SND_ARCHER_DAMAGED, SND_ARCHER_DEATH, SND_ARCHER_IDLE,						// archer
		SND_STONEWALL_MELEE, SND_STONEWALL_RANGED, SND_STONEWALL_MOVE, SND_STONEWALL_DAMAGED, SND_STONEWALL_DEATH, SND_STONEWALL_IDLE,		// stonewall
		SND_WOODWALL_MELEE, SND_WOODWALL_RANGED, SND_WOODWALL_MOVE, SND_WOODWALL_DAMAGED, SND_WOODWALL_DEATH, SND_WOODWALL_IDLE,			// wood wall
		SND_ARROW_IMPACT																													// arrow
	};

	bool SoundManager::init();
	ALuint SoundManager::loadSound(std::string file = "sound\test.wav");
	void SoundManager::playtest();

	ALuint registerObject();								// create a new source and tie it to the calling object
	void playSound(ALuint objID, Sounds sndID, b2Vec2 pos);										// Calling Objects supply ID acquired when registered and specify a sound (attack, etc)
	void setSourcePos(ALuint objID, b2Vec2 pos);
	void loadSounds(std::vector<bool> spawnListTypeID);					// Argument = A list of object types loaded into a vector (from level Loader)

	int getSourceCount() { return sourceCount; }
	int getBufferCount() { return bufferCount; }

	void setSoundEngineStatus(bool bSoundOn) { SOUND_ON = bSoundOn; }
	bool getSoundEngineStatus() { return SOUND_ON; }

private:

	bool SOUND_ON;								// Toggle if sound is on or off

	unsigned int sourceCount;					// number of sources registered
	unsigned int bufferCount;					// number of buffers loaded


	void reset();								// remove all sounds, reset all counters and resources.

	Vector3 listenerPos;
	Vector3 listenerVel;
	Vector3 listenerOri;
//	ALfloat listenerOri[6];

	//Vector3 source0Pos;
	//Vector3 source0Vel;

//	ALuint buffer[NUM_BUFFERS];
	std::vector<ALuint> source;
//	ALuint environemnt[NUM_ENVIRONMENTS];
	std::map<unsigned int, ALuint> bufferMap;


	//ALsizei size, freq;
	//ALenum format;
	//ALvoid *data;

	// Framework test
//	ALuint      uiBuffer;
//	ALuint      uiSource;  
//	ALint       iState;


};

