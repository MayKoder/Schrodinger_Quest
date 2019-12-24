#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "j1App.h"
#include "j1Input.h"

#define CURSOR_WIDTH 2

enum class Type
{
	NONE,
	BUTTON,
	IMAGE,
	WINDOW,
	TEXT,
	UNKNOWN
};
class UI :public j1Module
{
public:
	UI(Type type, SDL_Rect r, UI* p, bool d);

	// Destructor
	virtual ~UI() {}

	// Called when before render is available
	virtual bool Awake(pugi::xml_node&) { return true; }

	// Call before first frame
	virtual bool Start() { return true; }

	// Called before all Updates
	virtual bool PreUpdate();

	// Called after all Updates
	virtual bool PostUpdate() { return true; }

	// Called before quitting
	virtual bool CleanUp() { return true; }

	bool Move();

	SDL_Rect GetScreenRect();
	SDL_Rect GetLocalRect();
	iPoint GetScreenPos();
	iPoint GetLocalPos();
	void SetLocalPos(iPoint pos);
	bool CheckMouse();
	SDL_Rect Check_Printable_Rect(SDL_Rect sprite, iPoint& dif_sprite);

public:
	SDL_Rect sprite1;
private:
	SDL_Rect screen_rect;
	SDL_Rect local_rect;
	SDL_Rect mask_rect;
	UI* parent;
	bool drageable;
};
class ImageUI :public UI
{
public:
	ImageUI(Type type, UI* p, SDL_Rect r, SDL_Rect sprite, bool d);

	// Destructor
	virtual ~ImageUI() {}

	// Called after all Updates
	bool PostUpdate();
};
class WindowUI :public UI
{
public:
	WindowUI(Type type, UI* p, SDL_Rect r, SDL_Rect sprite, bool d);

	// Destructor
	virtual ~WindowUI() {}

	// Called after all Updates
	bool PostUpdate();
};
class TextUI :public UI
{
public:
	TextUI(Type type, UI* p, SDL_Rect r, p2SString str, bool d);

	// Destructor
	virtual ~TextUI() {}

	// Called after all Updates
	bool PostUpdate();

public:

	p2SString stri;
};
class ButtonUI :public UI
{
public:

	ButtonUI(Type type, UI* p, SDL_Rect r, SDL_Rect sprite, SDL_Rect spriten2, SDL_Rect spriten3, bool d);

	// Destructor
	virtual ~ButtonUI() {}

	// Called when before render is available
	bool Awake(pugi::xml_node&) { return true; };

	// Call before first frame
	bool Start() { return true; };

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp() { return true; };

public:
	SDL_Rect sprite2;
	SDL_Rect sprite3;
	bool pushed;
	bool over;
};
// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	UI* CreateUIElement(Type type, UI* p, SDL_Rect r, SDL_Rect sprite = { 0,0,0,0 }, p2SString str = "", SDL_Rect sprite2 = { 0,0,0,0 }, SDL_Rect sprite3 = { 0,0,0,0 });
	bool DeleteUIElement(UI*);


	const SDL_Texture* GetAtlas() const;

private:

	p2List <UI*> UIs;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__