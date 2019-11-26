#ifndef __ESNAKEENEMY_H__
#define __ESNAKEENEMY_H__

#include"p2Point.h"
#include"p2Log.h"
#include"p2SString.h"
#include"p2List.h"
#include"eCreature.h"
#include"eGroundEnemy.h"


class eGroundEnemy;
//Player class
class eSnakeEnemy : public eGroundEnemy
{

public:

	eSnakeEnemy(Types type) :eGroundEnemy(type) {
		name.create("enemy_info");
	}

	// Destructor
	~eSnakeEnemy() {

	}

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	//// Called each loop iteration
	//bool PreUpdate();
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	////Start level again
	//void Start_F3();

	////Save
	//bool Save(pugi::xml_node&) const;

	////Load
	//bool Load(pugi::xml_node&);

	////Load animation pushbacks by name
	//void LoadAnimationFromTMX(pugi::xml_node* animation_node, Animation* anim, const char* name);

	////Load sound by TMX
	//void LoadSoundFXFromTMX(pugi::xml_node* sound_node, unsigned int& fx, const char* name);

	////Move player to spawn
	//void MoveToSpawn();


};
#endif // __ESNAKEENEMY_H__

