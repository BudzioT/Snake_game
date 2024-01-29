#include "headers/Sounds.h"

Sounds::Sounds()
{
}

void Sounds::addSoundEffect(Mix_Chunk& soundEffect)
{
	/* Add the given sound effect */
	m_soundEffects.push_back(&soundEffect);
}

void Sounds::addMusic(Mix_Music& music)
{
	/* Add the given music */
	m_music.push_back(&music);
}

Mix_Chunk* Sounds::getSoundEffect(int index)
{
	return m_soundEffects[index];
}

Mix_Music* Sounds::getMusic(int index)
{
	return m_music[index];
}

int Sounds::numberSoundEffects() const
{
	return m_soundEffects.size();
}

int Sounds::numberMusic() const
{
	return m_music.size();
}