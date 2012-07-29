#include "Map.h"
#include "Game.h"
#include "Debug.h"

Map::Map(Game& game) : game(game), gameState(){
    std::vector<Elf> elves;
    elves.push_back((Elf) {1, 0, 0, 0, 0});
    gameState.elves = elves;
    gameState.felhound = (Felhound) {2, 2, 0, 0};
	
}

Map::~Map() {
	
}

void Map::initialize() {
	// Create an Entity
    // Ogre::Entity* ogreHead = game.getOgreManager().getSceneManager()->createEntity("Head", "ogrehead.mesh");
    // // Create a SceneNode and attach the Entity to it
    // Ogre::SceneNode* headNode = game.getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode("HeadNode");
    // headNode->attachObject(ogreHead);
    // // game.getOgreManager().getSceneManager()->getRootSceneNode()->addChild(headNode);

 
    // // Create a Light and set its position
    // Ogre::Light* light = game.getOgreManager().getSceneManager()->createLight("MainLight");
    // light->setPosition(20.0f, 80.0f, 50.0f);

    // game.getOgreManager().getSceneManager()->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    // game.getOgreManager().getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    // Ogre::Entity* entNinja = game.getOgreManager().getSceneManager()->createEntity("Ninja", "ninja.mesh");
    // entNinja->setCastShadows(true);
    // game.getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode()->attachObject(entNinja);
 
    // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
    // Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //     plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    // Ogre::Entity* entGround = game.getOgreManager().getSceneManager()->createEntity("GroundEntity", "ground");
    // game.getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    // entGround->setMaterialName("Examples/Rockwall");
    // entGround->setCastShadows(false);
 
    // Ogre::Light* pointLight = game.getOgreManager().getSceneManager()->createLight("pointLight");
    // pointLight->setType(Ogre::Light::LT_POINT);
    // pointLight->setPosition(Ogre::Vector3(0, 150, 250));
 
    // pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    // pointLight->setSpecularColour(1.0, 0.0, 0.0);
 
    // Ogre::Light* directionalLight = game.getOgreManager().getSceneManager()->createLight("directionalLight");
    // directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    // directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    // directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
 
    // directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 
 
    // Ogre::Light* spotLight = game.getOgreManager().getSceneManager()->createLight("spotLight");
    // spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    // spotLight->setDiffuseColour(0, 0, 1.0);
    // spotLight->setSpecularColour(0, 0, 1.0);
 
    // spotLight->setDirection(-1, -1, 0);
    // spotLight->setPosition(Ogre::Vector3(300, 300, 0));
 
    // spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    int numcols = 100;
    int numrows = 100;
    float unitsize = 3.0;

    Ogre::ManualObject* grid = game.getOgreManager().getSceneManager()->createManualObject("grid");    

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
	
    Ogre::Entity* gridEntity = game.getOgreManager().getSceneManager()->createEntity("Grid");
    Ogre::SceneNode* gridNode = game.getOgreManager().getSceneManager()->getRootSceneNode()->createChildSceneNode("GridNode");
    gridNode->attachObject(gridEntity);

    Ogre::MaterialPtr gridMat = gridEntity->getSubEntity(0)->getMaterial();
    gridMat->getTechnique(0)->getPass(0)->setAmbient(Ogre::ColourValue(.5, .5, .5, 0));
    gridMat->getTechnique(0)->getPass(0)->setDiffuse(Ogre::ColourValue(.5, .5, .5, 0));
    gridEntity->setMaterialName(gridMat->getName());


}

void Map::destroy() {
	
}

void Map::setGameState(const GameState& gamestate){
	// gameState = gamestate;
    std::vector<Elf> elfList;
    elfList.push_back((Elf) {1, 0, 0, 0, 0});
    elfList.push_back((Elf) {2, 0, 1, 0, 0});
    elfList.push_back((Elf) {3, 1, 0, 0, 0});
    GameState state1;
    gameState.elves = elfList;
    gameState.felhound = (Felhound) {2,2, 0, 0};

    // gameState = state1;gameState
}

void Map::update() {

	

    // std::vector<Elf> elfList;
    // elfList.push_back((Elf) {0, 0, 0});
    // elfList.push_back((Elf) {1, 0, 10});
    // elfList.push_back((Elf) {2, 10, 30});
    // GameState state1;
    // state1.elves = elfList;
    // state1.felhound = (Felhound) {2,2};

    // gameState = state1;

    DEBUG(gameStateToString(gameState));

	// for(int elfID = 0; elfID< gameState.elves.size(); elfID++){
 //        //DEBUG("Current elf:" << elfID);

	// 	OgreElf* current = NULL;

	// 	// If the elf does exist
	// 	if (elves.count(elfID)){
	// 		current = elves[elfID];
	// 	} else{ // Current elf doesn't exist
	// 		current = new OgreElf(
	// 			game.getOgreManager().getSceneManager(), 
	// 			elfID);
	// 		elves[elfID] = current;
	// 	}

	// 	//get Elf struct
	// 	Elf currentElfData;
	// 	for(int i = 0; i<gameState.elves.size(); i++){
	// 		if(gameState.elves[i].id == elfID){
	// 			currentElfData = gameState.elves[i];
	// 			break;
	// 		}
	// 	}

	// 	current->setPosition(currentElfData.x, 0, currentElfData.y);
	// }
	
}
