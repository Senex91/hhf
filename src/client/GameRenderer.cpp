#include "GameRenderer.h"

#include "Debug.h"
#include "Client.h"
#include <Ogre.h>


GameRenderer::GameRenderer(){

}

GameRenderer::~GameRenderer(){

}

void GameRenderer::initialize(){

	cameraMan = new OgreBites::SdkCameraMan(Client::getInstance().getOgreManager().getCamera());
	Client::getInstance().getOISManager().addInputListener(this);


	int numcols = 100;
    int numrows = 100;
    float unitsize = 3.0;

    Ogre::ManualObject* grid = Client::getInstance().getOgreManager().getSceneManager()->createManualObject("grid");    

    grid->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

    float width = (float)numcols * unitsize;
    float depth = (float)numrows * unitsize;
    Ogre::Vector3 center = Ogre::Vector3((-width / 2.0f), 0 ,( -depth / 2.0f));

    Ogre::ColourValue white = Ogre::ColourValue(1.0f, 1.0f, 1.0f, 0.5f); 
    int count = 0;
    for (int i = 0; i < numrows; ++i)
    {   
        Ogre::Vector3 s, e;
        s.x = 0.0f;
        s.z = i * unitsize; s.y = 0.0f;

        e.x = width;
        e.z = i * unitsize;
        e.y = 0.0f;

        grid->position(s + center);
        grid->colour(white);
        grid->position(e + center);
        grid->colour(white);
        grid->index(count++);
        grid->index(count++);
    }   
    grid->position(Ogre::Vector3(0.0f, 0.0f, numrows * unitsize) + center);
    grid->colour(white);
    grid->position(Ogre::Vector3(width, 0.0f, numrows * unitsize) + center);
    grid->colour(white);
    grid->index(count++);
    grid->index(count++);

    for (int i = 0; i < numcols; ++i)
    {   
        Ogre::Vector3 s, e;
        s.x = i * unitsize;
        s.z = depth;
        s.y = 0.0f;

        e.x = i * unitsize;
        e.z = 0.0f;
        e.y = 0.0f;

        grid->position(s + center);
        grid->colour(white);
        grid->position(e + center);
        grid->colour(white);
        grid->index(count++);
        grid->index(count++);
    }   
    grid->position(Ogre::Vector3(numcols * unitsize, 0.0f, 0.0f) + center);
    grid->colour(white);
    grid->position(Ogre::Vector3(numcols * unitsize, 0.0f, depth) + center);
    grid->colour(white);
    grid->index(count++);
    grid->index(count++);
    grid->end();

    Ogre::String meshName= "Grid";
    Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
    grid->convertToMesh(meshName); 
	
    Ogre::Entity* gridEntity = Client::getInstance().getOgreManager().getSceneManager()->createEntity("Grid");
    Ogre::SceneNode* gridNode = Client::getInstance().getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode("GridNode");
    gridNode->attachObject(gridEntity);

    Ogre::MaterialPtr gridMat = gridEntity->getSubEntity(0)->getMaterial();
    gridMat->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(.5, .5, .5, 0));
    gridMat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(.5, .5, .5, 0));
    gridEntity->setMaterialName(gridMat->getName());


}

void GameRenderer::renderNextState(GameState const& newState){
	// DEBUG(gameStateToString(newState));

}



// OIS::KeyListener
bool GameRenderer::keyPressed( const OIS::KeyEvent &arg ) {
	cameraMan->injectKeyDown(arg);
	// DEBUG("keypressed! " << arg.key);
	return true;
}
bool GameRenderer::keyReleased( const OIS::KeyEvent &arg ) {
	// if(arg.key == OIS::KC_F12) {
	cameraMan->injectKeyUp(arg);
	return true;
}
// OIS::MouseListener
bool GameRenderer::mouseMoved( const OIS::MouseEvent &arg ) {
	cameraMan->injectMouseMove(arg);
	// float x = (float)arg.state.X.abs / (float)arg.state.width;
	// float y = (float)arg.state.Y.abs / (float)arg.state.height;
	
	// Ogre::Vector3 pt = Client::getInstance().getOgreManager().rayCast(x,y);
	// Client::getInstance().getConnection().move(pt);
	
	return true;
}
bool GameRenderer::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	cameraMan->injectMouseDown(arg,id);
	return true;
}
bool GameRenderer::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	cameraMan->injectMouseUp(arg, id);
	return true;
}