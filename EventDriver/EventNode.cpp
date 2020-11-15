//
// Created by Guy on 11/11/2020.
//

#include "EventNode.hpp"


void EventNode::addTimer(TimerEvent *timer) {
    timerEvent = timer;
    isTimer = true;
}
void EventNode::addRequest(Request *request) {
    requestEvent = request;
    isRequest = true;
}

void EventNode::addDiskDone(DiskDoneEvent *dDone) {
    ddoneEvent = dDone;
    isDDone = true;
}

double EventNode::getEventTime(){
    if(isDiskDoneEvent()){
        DiskDoneEvent *ddone = getDiskDone();
        return ddone->getTimeDone();
    }
    else if(isRequestEvent()){
        Request *currReq = getRequest();
        return currReq->time();
    }
    else{
        TimerEvent *timeEvent = getTimer();
        return timeEvent->getTime();
    }
}


bool EventNode::isTimerEvent()    { return isTimer; }
bool EventNode::isRequestEvent()  { return isRequest; }
bool EventNode::isDiskDoneEvent() { return isDDone; }

EventNode *EventNode::next(){ return _next;}
void EventNode::next(EventNode *node){ _next = node;};

TimerEvent *EventNode::getTimer() { return timerEvent; }
Request *EventNode::getRequest() { return requestEvent; }
DiskDoneEvent *EventNode::getDiskDone() { return ddoneEvent; }

void EventNode::testPrint(){
    if(isDiskDoneEvent()){
        DiskDoneEvent *ddone = getDiskDone();
        std::cout << "Disk Done " << ddone->getTimeDone() << std::endl;
    }
    if(isRequestEvent()) {
        Request *currReq = getRequest();
        std::cout << "Request " << currReq->time() << " " << currReq->track() << " " << currReq->sector() << std::endl;
    }
    if(isTimerEvent()) {
        TimerEvent *timeEvent = getTimer();
        std::cout << "Timer " << timeEvent->getTime() << std::endl;

    }
}