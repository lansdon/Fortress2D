

#include "SoundManager.h"


SoundManager::SoundManager(void)
{
	setSoundEngineStatus(true);			// Set sound on/off

	sourceCount = 0;					// number of sources registered
	bufferCount = 0;					// number of buffers loaded

	listenerPos.set(0.0, 0.0, 4.0);
	listenerVel.set(0.0, 0.0, 0.0);
	listenerOri.set(0.0, 0.0, -1.0);

	//source0Pos.set(-2.0, 0.0, 0.0);
	//source0Vel.set(0.0, 0.0, 0.0);

}


SoundManager::~SoundManager(void)
{
	// Clean up by deleting Source(s) and Buffer(s)
	std::vector<ALuint>::iterator itSource = source.begin();
	while(itSource != source.end()) {
		alSourceStop(*itSource);
		alDeleteSources(1, &(*itSource));
		++itSource;
	}
	std::map<unsigned int, ALuint>::iterator it = bufferMap.begin();
	while(it != bufferMap.end()) {
//		ALint temp = (*it).second;
		alDeleteBuffers(1, &(*it).second);
		++it;
	}

//	alDeleteBuffers(1, buffer);

	ALFWShutdownOpenAL();

	ALFWShutdown();
}


bool SoundManager::init() {

	// Check if sound is on
	if(!getSoundEngineStatus()) 
		return false;		

	// Initialize Framework
	ALFWInit();

	if (!ALFWInitOpenAL()) {
		ALFWShutdown();
		return 0;
	}

	return 0;
}

ALuint SoundManager::loadSound(std::string filename) {
	// Check if sound is on
	if(!getSoundEngineStatus()) 
		return -1;		

	std::stringstream file;
	file << "sound/" << filename;

	// Load Wave file into OpenAL Buffer
	ALuint temp = 0;
	alGenBuffers(1, &temp);

	if (!ALFWLoadWaveToBuffer((char*)file.str().c_str(), temp)) {
		return 0;
	}
	bufferCount++;			// Track number of buffers created

	return temp;
}

//void SoundManager::playtest() {
//
////	alSourcePlay(source[0]);
//	//do
//	//{
//	//	Sleep(100);
//	//	ALFWprintf(".");
//	//	// Get Source State
//	//	alGetSourcei( uiSource, AL_SOURCE_STATE, &iState);
//	//} while (iState == AL_PLAYING);
//
//
//}



ALuint SoundManager::registerObject() {								// create a new source and tie it to the calling object
	// Check if sound is on
	if(!getSoundEngineStatus()) 
		return -1;		

	ALuint temp = 0;
	alGenSources(1, &temp);			// create source ID
	sourceCount++;
	if(source.size() < sourceCount) {
		source.resize(sourceCount);
	}
	source[sourceCount-1] = temp;
	return sourceCount-1;								// return the index of the new source
}

// Calling Objects supply ID acquired when registered and specify a sound (attack, etc)
void SoundManager::playSound(ALuint objID, Sounds sndID, b2Vec2 pos) {		
	// Check if sound is on
	if(!getSoundEngineStatus()) 
		return;		

	// update position
	setSourcePos(objID, pos);
	// Attach Source to Buffer
	alSourcei( source[objID], AL_BUFFER, bufferMap[sndID] );
	// play sound

	ALint state=0;
	alGetSourcei( objID, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING) {
		alSourcePlay(source[objID]);
	}
}


void SoundManager::setSourcePos(ALuint objID, b2Vec2 pos) {
		// Check if sound is on
	if(!getSoundEngineStatus()) 
		return;		

	alSource3f(objID, AL_POSITION, pos.x, pos.y, 0.0);
}



void SoundManager::loadSounds(std::vector<bool> spawnListTypeID) {				// Argument = A list of object types loaded into a vector (from level Loader)

	// Check if sound is on
	if(!getSoundEngineStatus()) 
		return;		
	
	reset();

	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}

	// ARCHER TOWER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER_TOWER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARROW SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARROW]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// STONEWALL SFX
	if(spawnListTypeID[Settings::OBJ_ID_STONEWALL]) {
//		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_MELEE, loadSound("stonewall_melee.wav")));
//		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_RANGED, loadSound("stonewall_ranged.wav")));
//		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_MOVE, loadSound("stonewall_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_DAMAGED, loadSound("stonewall_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_DEATH, loadSound("stonewall_death.wav")));
//		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_STONEWALL_IDLE, loadSound("stonewall_idle.wav")));
	}
	

	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}
	// ARCHER SFX
	if(spawnListTypeID[Settings::OBJ_ID_ARCHER]) {			
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DAMAGED, loadSound("archer_damaged.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_DEATH, loadSound("archer_death.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_IDLE, loadSound("archer_idle.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MELEE, loadSound("archer_melee.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_MOVE, loadSound("archer_move.wav")));
		bufferMap.insert( std::pair<unsigned int, ALuint>(SND_ARCHER_RANGED, loadSound("archer_ranged.wav")));
	}

	// Todo - Finish adding the rest of the sfx files for each type
	bufferCount = bufferMap.size();
}

void SoundManager::reset() {							// remove all sounds, reset all counters and resources.

	bufferMap.clear();
	sourceCount = 0;					// number of sources registered
	bufferCount = 0;					// number of buffers loaded
	
}
