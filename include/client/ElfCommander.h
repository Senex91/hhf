#ifndef ElfCommander_H
#define ElfCommander_H


class ElfCommander {
public:
	ElfCommander(NetServer);
	~ElfCommander();


protected:

	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );


private:

	NetServer* server = NULL;
};

#endif