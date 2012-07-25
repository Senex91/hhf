
#ifndef __Axes_h_
#define __Axes_h_

#include "BaseApplication.h"
#include <vector>

class Axes {
public:
    Axes(Ogre::Root*, Ogre::SceneManager*, std::string);
    virtual ~Axes(void);
    void setPosition(float, float, float);
    void setHeading(float);

    static void loadMesh(Ogre::SceneManager*, int);
protected:
    Ogre::Entity* mEntity;
    Ogre::SceneNode* mSceneNode;
    Ogre::SceneManager* mSceneManager;
    Ogre::Root* mRoot;
    std::string mName;
    float angle;
    int pathIndex;

private:
};

#endif // #ifndef __Axes_h_
