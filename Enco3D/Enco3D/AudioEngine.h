#ifndef _ENCO3D_AUDIOENGINE_H_
#define _ENCO3D_AUDIOENGINE_H_

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <iostream>

namespace Enco3D
{
	namespace Audio
	{
		class AudioEngine
		{
		private:
			int m_audioRate{ 0 };
			Uint16 m_audioFormat{ 0 };
			int m_audioChannels{ 0 };
			int m_audioBuffers{ 0 };
			Mix_Chunk *m_psound{ nullptr };
			Mix_Music *m_pmusic{ nullptr };

		public:
			AudioEngine(int audioRate = 44100, Uint16 audioFormat = AUDIO_S16SYS, int audioChannels = 2, int audioBuffers = 4096);
			~AudioEngine();

			void SoundLoad(const std::string &filename, int volume);
			void SoundPlay();

			void MusicLoad(const std::string &filename, int volume);
			void MusicPlay();
		};
	}
}

#endif