#include "OgreElf.h"

OgreElf::OgreElf(Ogre::SceneManager* pManager, int pId){
	manager = pManager;
	id = pId;

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

void OgreElf::setColour(Ogre::ColourValue colour){
	std::string matName = OgreElf_MATERIAL_NAME;
    matName+=id;
    Ogre::MaterialPtr mat = entity->getSubEntity(0)->getMaterial()->clone(matName);
    mat->getTechnique(0)->getPass(0)->setAmbient(colour);
    mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
    entity->setMaterialName(mat->getName());
}