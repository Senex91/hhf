#include "ElfCommander.h"
#include "Command.h"
#include "Client.h"
#include "Debug.h"

ElfCommander::ElfCommander(NetServer& server) : server(server){

}

ElfCommander::~ElfCommander(){

}

// OIS::KeyListener
bool ElfCommander::keyPressed( const OIS::KeyEvent &arg ) {
	return true;
}

bool ElfCommander::keyReleased( const OIS::KeyEvent &arg ) {
	return true;
}

// OIS::MouseListener
bool ElfCommander::mouseMoved( const OIS::MouseEvent &arg ) {
	return true;
}
bool ElfCommander::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	return true;
}
bool ElfCommander::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	if(id == OIS::MB_Right){
		float x = (float)arg.state.X.abs / (float)arg.state.width;
		float y = (float)arg.state.Y.abs / (float)arg.state.height;
		Ogre::MovableObject* entityClicked = NULL;
		if((entityClicked = Client::getInstance().getOgreManager().rayCastEntity(x,y))) {
			DEBUG("I clicked on " << entityClicked->getName());
			if(entityClicked->getUserAny().getType() == typeid(OgreElf*)) {
				OgreElf* clickedElf = Ogre::any_cast<OgreElf*>(entityClicked->getUserAny());
				server.sendCommand(ThrowCommand(clickedElf->getID()));
			}
		} else {
			Ogre::Vector3 pt = Client::getInstance().getOgreManager().rayCast(x,y);
			
			DEBUG("MOVE!: " << pt.x <<" \t" << pt.z);
			server.sendCommand(MoveCommand(pt.x, pt.z));
		}
	}
	return true;
}