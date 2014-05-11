#include "AudioEngine.h"

Enco3D::Audio::AudioEngine::AudioEngine(int audioRate, Uint16 audioFormat, int audioChannels, int audioBuffers)
{
	m_audioRate = audioRate;
	m_audioFormat = audioFormat;
	m_audioChannels = audioChannels;
	m_audioBuffers = audioBuffers;

	m_psound = nullptr;
	m_pmusic = nullptr;

	Mix_AllocateChannels(10);
}

Enco3D::Audio::AudioEngine::~AudioEngine()
{
	if (m_pmusic)
		Mix_FreeMusic(m_pmusic);
	if (m_psound)
		Mix_FreeChunk(m_psound);
	
	Mix_CloseAudio();
}

void Enco3D::Audio::AudioEngine::SoundLoad(const std::string &filename, int volume)
{
	if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
	{
		std::cerr << "[ERROR] Failed to start sound: " << Mix_GetError() << std::endl;
		return;
	}

	m_psound = Mix_LoadWAV(filename.c_str());
	if (m_psound == nullptr)
	{
		std::cerr << "[ERROR] Failed to load WAV file " << filename << std::endl;
		return;
	}

	Mix_VolumeChunk(m_psound, volume);
}

void Enco3D::Audio::AudioEngine::SoundPlay()
{
	if (Mix_PlayChannel(-1, m_psound, 0) == -1)
		std::cerr << "[ERROR] Failed to play WAV file: " << Mix_GetError() << std::endl;
}

void Enco3D::Audio::AudioEngine::MusicLoad(const std::string &filename, int volume)
{
	if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
	{
		std::cerr << "[ERROR] Failed to start music: " << Mix_GetError() << std::endl;
		return;
	}

	m_pmusic = Mix_LoadMUS(filename.c_str());
	if (m_pmusic == nullptr)
	{
		std::cerr << "[ERROR] Failed to load WAV file (music): " << filename << std::endl;
		return;
	}

	Mix_VolumeMusic(volume);
}

void Enco3D::Audio::AudioEngine::MusicPlay()
{
	if (Mix_PlayMusic(m_pmusic, -1) == -1)
		std::cerr << "[ERROR] Failed to play WAV file (music): " << Mix_GetError() << std::endl;
}