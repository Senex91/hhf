#ifndef OGREFELHOUND_H
#define OGREFELHOUND_H

#define OgreFelhound_MESHNAME "plane727.mesh"
#define OgreFelhound_ENTITY_NAME "OgreFelhound"
#define OgreFelhound_MATERIAL_NAME "planeMaterial"

#include <OgreColourValue.h>
#include <OgreSubEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <string>



class OgreFelhound {
public:
	OgreFelhound(Ogre::SceneManager*, int);
	~OgreFelhound(void);

	void setPosition(float, float, float);
	void setOrientation(float);
	void setColour(Ogre::ColourValue);

	static Ogre::ColourValue getColour(unsigned int);


private:

	// static Ogre::ColourValue[] generateColors();

	int id;
	std::string name;
	

	Ogre::SceneManager* manager;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;

	// static Ogre::ColourValue colors[];




};

#endif