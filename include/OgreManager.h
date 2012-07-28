#ifndef OGRE_MANAGER_H
#define OGRE_MANAGER_H

#include <Ogre.h>

class Game;

class OgreManager {
public:
	OgreManager(Game&);
	~OgreManager();
	
	void initialize();
	void destroy();
	
	void update();
	
	Ogre::Root* getRoot() { return root; }
	Ogre::Camera* getCamera() { return camera; }
	Ogre::SceneManager* getSceneManager() { return sceneManager; }
	Ogre::RenderWindow* getWindow() { return window; }
	
private:
	Game& game;
	
	Ogre::Root *root;
	Ogre::Camera* camera;
	Ogre::SceneManager* sceneManager;
	Ogre::RenderWindow* window;
	Ogre::String resourcesCfg;
	Ogre::String pluginsCfg;
};

#endif