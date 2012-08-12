#include "OgreElf.h"
#include "OgreEuler.h" // from our source tree
#include "Debug.h"
#include <stdlib.h>
#include <time.h>
#include <OgreMaterialManager.h>

OgreElf::OgreElf(Ogre::SceneManager* pManager, Ogre::ColourValue color,  int pId){
	manager = pManager;
	id = pId;

	name = OgreElf_ENTITY_NAME + id;
	entity = manager->createEntity(name, OgreElf_MESHNAME);
	entity->setUserAny(Ogre::Any(this));
	node = manager->getRootSceneNode()->createChildSceneNode(name);
	node->attachObject(entity);
    node->scale(.1, .1, .1);
    setColour(color);
}

OgreElf::~OgreElf(void){
	node->detachObject(entity);
	manager->destroyEntity(entity);
	manager->getRootSceneNode()->removeChild(node);
	manager->destroySceneNode(node);
}

void OgreElf::setPosition(float x, float y, float z){
	node->setPosition(x,y+2,z);
}

void OgreElf::setOrientation(float heading){
    Ogre::Euler angle(
            Ogre::Radian(heading), //yaw
            Ogre::Radian(0), //pitch
            Ogre::Radian(0));//bank
    node->setOrientation(angle);
}

void OgreElf::setColour(Ogre::ColourValue colour){
	std::string matName = OgreElf_MATERIAL_NAME;
    matName+=id;

    if(Ogre::MaterialManager::getSingleton().resourceExists(matName)){
        Ogre::MaterialPtr mat = entity->getSubEntity(1)->getMaterial();
        mat->getTechnique(0)->getPass(0)->setAmbient(colour);
        mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
    } else{
        Ogre::MaterialPtr mat = entity->getSubEntity(1)->getMaterial()->clone(matName);
        mat->getTechnique(0)->getPass(0)->setAmbient(colour);
        mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
        entity->setMaterialName(mat->getName());
    }
}
