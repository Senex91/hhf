#include "TimerManager.h"

DelayedCallBase::~DelayedCallBase() {
	
}

bool CallComp::operator()(DelayedCallBase* a,DelayedCallBase* b) {
	if(a->getCallTime() == b->getCallTime()) {
		return a < b;
	}
	else {
		return a->getCallTime() < b->getCallTime();
	}
}


TimerManager::TimerManager() {
	
}

TimerManager::~TimerManager() {
	
}

void TimerManager::update() {
	//set is sorted with the earliest calls at the front
	DelayedCallBase* b;
	while(calls.size() > 0 && (b = *(calls.begin()))->getCallTime() <= SDL_GetTicks()) {
		b->call();
		calls.erase(b);
		delete b;
		b = *(calls.begin());
	}
}

void TimerManager::addCall(DelayedCallBase* b) {
	calls.insert(b);
}

int TimerManager::getRemainingCalls() {
	return calls.size();
}