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
	{
		Mix_FreeMusic(m_pmusic);
		m_pmusic = nullptr;
	}

	if (m_psound)
	{
		Mix_FreeChunk(m_psound);
		m_psound = nullptr;
	}

	Mix_CloseAudio();
}

Enco3D::Core::ErrorResult Enco3D::Audio::AudioEngine::SoundLoad(const string &filename, int volume)
{
	if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
	{
		cerr << "[ERROR] Failed to start sound: " << Mix_GetError() << endl;
		return Error::Failed;
	}

	m_psound = Mix_LoadWAV(filename.c_str());
	if (m_psound == nullptr)
	{
		cerr << "[ERROR] Failed to load WAV file " << filename << endl;
		return Error::Failed;
	}

	Mix_VolumeChunk(m_psound, volume);

	return Error::Success;
}

Enco3D::Core::ErrorResult Enco3D::Audio::AudioEngine::SoundPlay()
{
	if (Mix_PlayChannel(-1, m_psound, 0) == -1)
	{
		cerr << "[ERROR] Failed to play WAV file: " << Mix_GetError() << endl;
		return Error::Failed;
	}

	return Error::Success;
}

Enco3D::Core::ErrorResult Enco3D::Audio::AudioEngine::MusicLoad(const string &filename, int volume)
{
	if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
	{
		cerr << "[ERROR] Failed to start music: " << Mix_GetError() << endl;
		return Error::Failed;
	}

	m_pmusic = Mix_LoadMUS(filename.c_str());
	if (m_pmusic == nullptr)
	{
		cerr << "[ERROR] Failed to load WAV file (music): " << filename << endl;
		return Error::Failed;
	}

	Mix_VolumeMusic(volume);

	return Error::Success;
}

Enco3D::Core::ErrorResult Enco3D::Audio::AudioEngine::MusicPlay()
{
	if (Mix_PlayMusic(m_pmusic, -1) == -1)
	{
		cerr << "[ERROR] Failed to play WAV file (music): " << Mix_GetError() << endl;
		return Error::Failed;
	}

	return Error::Success;
}