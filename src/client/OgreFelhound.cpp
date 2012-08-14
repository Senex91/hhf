#include "OgreFelhound.h"
#include "OgreEuler.h" // from our source tree
#include "Debug.h"
#include <stdlib.h>
#include <time.h>
#include <OgreMaterialManager.h>

std::vector<Ogre::ColourValue> initialFelhoundColors(){
    // initiates random seed for additional colors
    srand((unsigned)time(0));
    std::vector<Ogre::ColourValue> colors;
    colors.push_back(Ogre::ColourValue::Red);
    colors.push_back(Ogre::ColourValue::Green);
    colors.push_back(Ogre::ColourValue::Blue);
    colors.push_back(Ogre::ColourValue(1, 1, 0, 1));
    colors.push_back(Ogre::ColourValue::White);

    return colors;
}

OgreFelhound::OgreFelhound(Ogre::SceneManager* pManager, int pId){
	manager = pManager;
	id = pId;

	name = OgreFelhound_ENTITY_NAME + id;
	entity = manager->createEntity(name, OgreFelhound_MESHNAME);
	node = manager->getRootSceneNode()->createChildSceneNode(name);
	node->attachObject(entity);
	node->setScale(2, 2, 2);
	setColour(Ogre::ColourValue::White);
}

OgreFelhound::~OgreFelhound(void) {
	
}

void OgreFelhound::setPosition(float x, float y, float z){
	node->setPosition(x,y+2,z);
}

void OgreFelhound::setOrientation(float heading){
	Ogre::Euler angle(
			Ogre::Radian(3.1415926 / 2.0 - heading), //yaw
			Ogre::Radian(0), //pitch
			Ogre::Radian(0));//bank
	node->setOrientation(angle);
}

void OgreFelhound::setColour(Ogre::ColourValue colour){
	std::string matName = OgreFelhound_MATERIAL_NAME;
	matName+=id;

	if(Ogre::MaterialManager::getSingleton().resourceExists(matName)){
		Ogre::MaterialPtr mat = entity->getSubEntity(0)->getMaterial();
		mat->getTechnique(0)->getPass(0)->setAmbient(colour);
		mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
	} else{
		Ogre::MaterialPtr mat = entity->getSubEntity(0)->getMaterial()->clone(matName);
		mat->getTechnique(0)->getPass(0)->setAmbient(colour);
		mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
		entity->setMaterialName(mat->getName());
	}
}

Ogre::ColourValue OgreFelhound::getColour(unsigned int id){
	static std::vector<Ogre::ColourValue> colors = initialFelhoundColors();
	if(id >= colors.size()){ //if the colour does not exist
		colors.push_back(
			Ogre::ColourValue(
				(float)rand()/(float)RAND_MAX,
				(float)rand()/(float)RAND_MAX,
				(float)rand()/(float)RAND_MAX, 1)
						);

	}

	return colors[id];
}