#ifndef OgreElf_H
#define OgreElf_H

#define OgreElf_MESHNAME "ogrehead.mesh"
// #define OgreElf_MESHNAME "plane727.mesh"
#define OgreElf_ENTITY_NAME "OgreElf"
#define OgreElf_MATERIAL_NAME "planeMaterial"

#include <OgreColourValue.h>
#include <OgreSubEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <string>



class OgreElf {
public:
	OgreElf(Ogre::SceneManager*,Ogre::ColourValue,  int);
	~OgreElf(void);
	
	void setPosition(float, float, float);
	void setOrientation(float);
	void setColour(Ogre::ColourValue);
	
	inline const int& getID() { return id; }
	
private:
	
	int id;
	std::string name;
	
	Ogre::SceneManager* manager;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
};

#endif