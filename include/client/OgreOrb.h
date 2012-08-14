#ifndef OGREORB_H
#define OGREORB_H

#define OgreOrb_MESHNAME "plane727.mesh"
#define OgreOrb_ENTITY_NAME "OgreOrb"
#define OgreOrb_MATERIAL_NAME "planeMaterial"

#include <OgreColourValue.h>
#include <OgreSubEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <string>

class OgreOrb {
public:
	OgreOrb(Ogre::SceneManager*);
	~OgreOrb(void);
	
	void setPosition(float, float, float);
	// void setOrientation(float);
	void setColour(Ogre::ColourValue);
	
	static Ogre::ColourValue getColour(unsigned int);
	
private:
	int id;
	std::string name;
	
	Ogre::SceneManager* manager;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
};

#endif