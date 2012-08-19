#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <set>
#include "SDL_timer.h"

class DelayedCallBase {
public:
	DelayedCallBase(const Uint32& time) : time(time) {}
	virtual ~DelayedCallBase();
	
	virtual void call() = 0;
	inline const Uint32& getCallTime() { return time; }
private:
	Uint32 time;
};

template<class Callable>
class DelayedCall : public DelayedCallBase {
public:
	DelayedCall(const Uint32& time, const Callable& c) : DelayedCallBase(time), c(c) {}
	virtual ~DelayedCall() {}
	
	virtual void call() {
		c();
	}
	
private:
	Callable c;
};

class CallComp {
public:
	CallComp() {}
	~CallComp() {}
	bool operator()(DelayedCallBase* a,DelayedCallBase* b);
};

class TimerManager {
public:
	TimerManager();
	~TimerManager();
	
	void update();
	void addCall(DelayedCallBase*);
	int getRemainingCalls();
	
	template<class Callable>
	void addCall(const Callable& c,const Uint32& delay) { //delay is relative to now
		addCall(new DelayedCall<Callable>(SDL_GetTicks()+delay,c));
	}
	
private:
	std::set<DelayedCallBase*,CallComp> calls;
};

#endif