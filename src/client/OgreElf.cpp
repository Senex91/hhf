#include "OgreElf.h"
#include "OgreEuler.h" // from our source tree
#include "Debug.h"
#include <stdlib.h>
#include <time.h>

std::vector<Ogre::ColourValue> initialColors(){
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

OgreElf::OgreElf(Ogre::SceneManager* pManager, int pId){
	manager = pManager;
	id = pId;

	name = OgreElf_ENTITY_NAME + id;
	entity = manager->createEntity(name, OgreElf_MESHNAME);
	node = manager->getRootSceneNode()->createChildSceneNode(name);
	node->attachObject(entity);
    setColour(getColour(id));
}

OgreElf::~OgreElf(void){

}

void OgreElf::setPosition(float x, float y, float z){
	node->setPosition(x,y,z);
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
    Ogre::MaterialPtr mat = entity->getSubEntity(0)->getMaterial()->clone(matName);
    mat->getTechnique(0)->getPass(0)->setAmbient(colour);
    mat->getTechnique(0)->getPass(0)->setDiffuse(colour);
    entity->setMaterialName(mat->getName());
}

Ogre::ColourValue OgreElf::getColour(unsigned int id){
    static std::vector<Ogre::ColourValue> colors = initialColors();
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