#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "EntityManager.h"
#include "j1Pathfinding.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
	isMainMenu = true;
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	main_menu_background = App->tex->Load("maps/main_menu.png");

	//App->gui->CreateUIElement(Type::WINDOW, nullptr, { (int)App->win->width / 2 - (334), 75, 334 * 2, 300 }, { 0, 0, 0, 0 })->active = false;

	//App->gui->CreateUIElement(Type::IMAGE, menu_window, { (int)App->win->width / 2 - (334), 75, 334 * 2, 29 * 2 }, { 0, 0, 334, 29 });


	//App->gui->CreateUIElement(Type::BUTTON, menu_window, { (int)App->win->width / 2 - (334), 80, 334 * 2, 29 * 2 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 });
	//App->gui->CreateUIElement(Type::BUTTON, menu_window, { (int)App->win->width / 2 - (334), 90, 334 * 2, 29 * 2 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 });
	//App->gui->CreateUIElement(Type::BUTTON, menu_window, { (int)App->win->width / 2 - (334), 100, 334 * 2, 29 * 2 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 }, { 0, 0, 334, 29 });
	////App->gui->CreateUIElement(Type::BUTTON, test, { 0, 0, 100, 100 }, {0, 0, 0, 0}, "PLAY", { 0, 0, 0, 0 }, { 0, 0, 0, 0 });


	// TODO 3: Create the banner (rect {485, 829, 328, 103}) as a UI element
	//App->gui->CreateUIElement(Type::IMAGE, { 485,829,328,103 });
	// TODO 4: Create the text "Hello World" as a UI element

	int w, h;
	App->font->CalcSize("Schrodinger Quest", w, h);
	//UI* window = App->gui->CreateUIElement(Type::WINDOW, nullptr, { ((int)App->win->width / 2) - 450 / 2, 10, 450, ((int)App->win->height - 30) });
	//App->gui->CreateUIElement(Type::TEXT, window, { 0, 10, w, h }, { 0, 0, 229, 69 }, "Schrodinger Quest");
	//UI* button = App->gui->CreateUIElement(Type::BUTTON, window, { 0, 0, 229, 69 }, { 0, 0, 0, 0 }, "", { 0,0,0,0 }, { 0,0,0,0 });
	//App->font->CalcSize("Button", w, h);
	//App->gui->CreateUIElement(Type::TEXT, button, { 0, 0, w, h }, { 0, 0, 0, 0 }, "Button");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	//if (!isMainMenu) 
	//{
	//	// debug pathfing ------------------
	//	static iPoint origin;
	//	static bool origin_selected = false;

	//	int x, y;
	//	App->input->GetMousePosition(x, y);
	//	App->map->Translate_Coord(&x, &y);

	//	iPoint p = { x, y };

	//	//PathFinding with	E
	//	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	//	{
	//		if (origin_selected == true)
	//		{
	//			App->map->WorldToMap(&origin.x, &origin.y);

	//			p.x = App->entity_manager->Player->collider->collider_rect.x;
	//			p.y = App->entity_manager->Player->collider->collider_rect.y + (App->entity_manager->Player->collider->collider_rect.h / 2);

	//			App->map->WorldToMap(&p.x, &p.y);
	//			App->pathfinding->CreatePath(origin, p);
	//			origin_selected = false;
	//		}
	//		else
	//		{
	//			origin = p;
	//			origin_selected = true;
	//		}
	//	}
	//}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	//Volume change +
	if (App->input->GetKey(SDL_SCANCODE_RIGHTBRACKET) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHTBRACKET) == KEY_REPEAT)
		App->audio->ChangeVolume(true);

	//Volume change -
	if (App->input->GetKey(SDL_SCANCODE_SLASH) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_SLASH) == KEY_REPEAT)
		App->audio->ChangeVolume(false);

	//Start from the first level
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) 
	{
		App->map->map_id = 1;
		Load_Map_By_Name(App->map->GetSourceFromID(App->map->map_id).GetString());
	}

	//Start from the second level
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) 
	{
		App->map->map_id = 2;
		Load_Map_By_Name(App->map->GetSourceFromID(App->map->map_id).GetString());
	}

	//Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		App->entity_manager->Player->Start_F3();

	//Save the current state
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	//Load the previous state (even across levels)
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();
	
	//Debug UI
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		App->gui->ChangeDebug();

	//Enable and disable 30fps cap
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN) 
	{
		if (App->fps_limit == App->fps_min) 
		{
			App->fps_limit = App->fps_max;
		}
		else
		{
			App->fps_limit = App->fps_min;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		App->gui->ChangeFocus();

	//Draw map
	if (!isMainMenu) 
	{
		App->map->Draw();
	}
	else
	{
		App->render->BlitBackgroud(main_menu_background);
	}

	return true;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	if (main_menu_background) 
	{
		App->tex->UnLoad(main_menu_background);
	}


	return true;
}


//Load map by name
void j1Scene::Load_Map_By_Name(const char* name)
{
	isMainMenu = false;
	App->map->active = true;
	App->entity_manager->active = true;

	App->colliders->ClearColliders();
	App->map->CleanUp();

	App->map->Load(name);
	App->pathfinding->UpdatePathFindingMap();

	App->colliders->LoadColliders();
	App->render->SetMapLimitsWithTMX();
	App->entity_manager->Player->Start_F3();
}