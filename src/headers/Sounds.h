#pragma once
#include "SDL.h"
#include "SDL_mixer.h"

#include <vector>
#include <initializer_list>

class Sounds
{
public:
	Sounds();

	/* Add sound effects */
	void addSoundEffect(Mix_Chunk& soundEffect);
	/* Add music */
	void addMusic(Mix_Music& music);

	/* Get sound effect at given index */
	Mix_Chunk* getSoundEffect(int index);
	/* Get music at given index */
	Mix_Music* getMusic(int index);

	/* Get number of sound effects */
	int numberSoundEffects() const;
	/* Get number of music */
	int numberMusic() const;

private:
	/* Vector of sound effects */
	std::vector<Mix_Chunk*> m_soundEffects;
	/* Vector of music */
	std::vector<Mix_Music*> m_music;
};