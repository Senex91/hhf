
#include "Axes.h"
#include "OgreEuler.h" // from our source tree
#include <iostream>
#include <sstream>

//-------------------------------------------------------------------------------------
Axes::Axes(Ogre::Root* root, Ogre::SceneManager* manager, std::string name){


    mRoot = root;
    mSceneManager= manager;
    mName = name;
    //loadMesh(10);
    mEntity = mSceneManager->createEntity(mName,"MeshAxe");
    mSceneNode= mSceneManager->getRootSceneNode()->createChildSceneNode(mName); 
    mSceneNode->attachObject(mEntity);


}

void Axes::setHeading(float radians){
    Ogre::Euler angle(
            Ogre::Radian(radians),
            Ogre::Radian(0),
            Ogre::Radian(0));
    mSceneNode->setOrientation(angle);
}
//-------------------------------------------------------------------------------------
Axes::~Axes(void){
}

//-------------------------------------------------------------------------------------
void Axes::setPosition(float x, float y, float z){
    mSceneNode->setPosition(x, z, y);
}


void Axes::loadMesh(Ogre::SceneManager* mSceneManager, int size){
    Ogre::ManualObject* lManualObject = mSceneManager->createManualObject("axes");

    lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    {
        float lAxeSize = size;

        // X red
        lManualObject->position(0.0f, 0.0f, 0.0f);
        lManualObject->colour(Ogre::ColourValue::Red);
        lManualObject->position(lAxeSize, 0.0f, 0.0f);
        lManualObject->colour(Ogre::ColourValue::Red);

        // Y green
        lManualObject->position(0.0f, 0.0f, 0.0f);
        lManualObject->colour(Ogre::ColourValue::Green);
        lManualObject->position(0.0, lAxeSize, 0.0);
        lManualObject->colour(Ogre::ColourValue::Green);

        // Z blue
        lManualObject->position(0.0f, 0.0f, 0.0f);
        lManualObject->colour(Ogre::ColourValue::Blue);
        lManualObject->position(0.0, 0.0, lAxeSize);
        lManualObject->colour(Ogre::ColourValue::Blue);

        lManualObject->index(0);
        lManualObject->index(1);
        lManualObject->index(2);
        lManualObject->index(3);
        lManualObject->index(4);
        lManualObject->index(5);
    }
    lManualObject->end();

    Ogre::String lNameOfTheMesh = "MeshAxe";
    Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    lManualObject->convertToMesh(lNameOfTheMesh);


}
