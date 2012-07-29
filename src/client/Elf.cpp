#include "Elf.h"

OgreElf::OgreElf(Ogre::SceneManager* manager, int id): manager(manager), id(id), name(){

	name = OgreElf_ENTITY_NAME + id;
	entity = manager->createEntity(name, OgreElf_MESHNAME);
	node = manager->getRootSceneNode()->createChildSceneNode(name);
	node->attachObject(entity);
}

OgreElf::~OgreElf(void){

}

void OgreElf::setPosition(float x, float y, float z){
	node->setPosition(x,y,z);
}