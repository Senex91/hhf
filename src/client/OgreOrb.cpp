#include "OgreOrb.h"
#include "OgreEuler.h" // from our source tree
#include "Debug.h"
#include <stdlib.h>
#include <time.h>
#include <OgreMaterialManager.h>

std::vector<Ogre::ColourValue> initialOrbColors(){
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

OgreOrb::OgreOrb(Ogre::SceneManager* pManager, int pId){
	manager = pManager;
	id = pId;

	name = OgreOrb_ENTITY_NAME + id;
	entity = manager->createEntity(name, OgreOrb_MESHNAME);
	node = manager->getRootSceneNode()->createChildSceneNode(name);
	node->attachObject(entity);
    setColour(getColour(id));
}

OgreOrb::~OgreOrb(void){

}

void OgreOrb::setPosition(float x, float y, float z){
	node->setPosition(x,y,z);
}

void OgreOrb::setColour(Ogre::ColourValue colour){
	std::string matName = OgreOrb_MATERIAL_NAME;
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

Ogre::ColourValue OgreOrb::getColour(unsigned int id){
    static std::vector<Ogre::ColourValue> colors = initialOrbColors();
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