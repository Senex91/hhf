#ifndef HEADLESS_LIENT_H
class HeadlessClient {
public:
	static Client& getInstance();

	inline OgreManager& getOgreManager() { return ogre; }
	inline OISManager& getOISManager() { return ois; }
	inline CEGUIManager& getCEGUIManager() { return cegui; }

	inline void setRunning(const bool& r) { running = r; }

	void initialize();
	void destroy();
	
	void run();

	void runBehavior();
private:

	HeadlessClient();
	HeadlessClient(Client const&);

	~HeadlessClient();
	HeadlessClient& operator=(HeadlessClient const&);
	OgreManager ogre;
	CEGUIManager cegui;

	GameRenderer gameRenderer;
	NetServer server;
	ClientAi ai;
	bool running;

};
#endif