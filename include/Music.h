#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include <string>

using namespace std;

class Music {
public:
	Music();
	Music(string file);
	~Music();
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	void Open(string file);
	bool IsOpen();
private:
	Mix_Music* music;
};