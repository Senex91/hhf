#ifndef OgreElf_H
#define OgreElf_H

#define OgreElf_MESHNAME "plane727.mesh"
#define OgreElf_ENTITY_NAME "OgreElf"

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreEntity.h"
#include "string"

class OgreElf {
public:
	OgreElf(Ogre::SceneManager*, int);
	~OgreElf(void);

	void setPosition(float, float, float);



private:
	int id;
	std::string name;
	

	Ogre::SceneManager* manager;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;


};

#endif