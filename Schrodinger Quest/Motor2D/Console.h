#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "j1Module.h"

class ImageUI;

class Console :public j1Module {
public:
	Console();

	// Destructor
	virtual ~Console() {};

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt) { return true; };
	bool PostUpdate() { return true; };

	void ActivateConsole();

	// Called before quitting
	bool CleanUp() { return true; };

public:
	ImageUI* console_background;
	bool console_active;
private:
	SDL_Rect background_pos;
	int background_red;
	int background_green;
	int background_blue;
	int background_alpha;
};

#endif