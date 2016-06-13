/*
 * Resources.h
 *
 *  Created on: 23 de mar de 2016
 *      Author: Caio
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_
#include<unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <SDL_mixer.h>
#include "Text.h"

class Resources {

public:
	Resources();
	static SDL_Texture* GetImage(std::string file);
	static void ClearImages();

	static Mix_Music* GetMusic(std::string file);
	static void ClearMusic();

	static Mix_Chunk* GetSound(std::string file);
	static void ClearSound();

	static TTF_Font* GetFont(std::string file, int fontSize);
	static void ClearFont();

	static Text* GetNumber(int number);
	static void ClearNumber();

	~Resources();
private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
	static std::unordered_map<std::string, TTF_Font*> fontTable;
	static std::unordered_map<int, Text*> numbersTable;
};

#endif /* RESOURCES_H_ */
