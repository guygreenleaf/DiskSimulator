//
// Created by Guy on 11/9/2020.
//

#include "EventQueue.hpp"
#include "../SimulationFiles/Disk.hpp"

void EventQueue::addRequest(Request *req) {
    EventNode *currNode = head;
    EventNode *trackHead = head;
    EventNode *requestNode = new EventNode();
    requestNode->addRequest(req);

    if(currNode == nullptr){
        head = requestNode;
    }
    else{
        while (currNode->next() != nullptr) {
            if(requestNode->getEventTime() < currNode->getEventTime() && currNode == trackHead){
                requestNode->next(currNode);
                head = requestNode;
                break;
            }
            if(requestNode->getEventTime() >= currNode->getEventTime() && requestNode->getEventTime() <= currNode->next()->getEventTime()){
                requestNode->next(currNode->next());
                currNode->next(requestNode);
                break;
            }
            else
                currNode = currNode->next();
        }
        if(currNode->next() == nullptr && currNode == trackHead){
            if(requestNode->getEventTime() < currNode->getEventTime()) {
                requestNode->next(currNode);
                head = requestNode;
            }
            else
            currNode->next(requestNode);
        }
        else if(currNode->next() == nullptr){
            currNode->next(requestNode);
        }
    }
}


void EventQueue::addTimerEvent(TimerEvent *aTimer ) {
    EventNode *trackHead = head;
    EventNode *currNode = head;
    EventNode *timerNode = new EventNode();
    timerNode->addTimer(aTimer);
    if(currNode == nullptr){
        head = timerNode;
    }
    else{
        while (currNode->next() != nullptr) {
            if(timerNode->getEventTime() < currNode->getEventTime() && currNode == trackHead){
                timerNode->next(currNode);
                head = timerNode;
                break;
            }
            if(timerNode->getEventTime() >= currNode->getEventTime() && timerNode->getEventTime() <= currNode->next()->getEventTime()){
                timerNode->next(currNode->next());
                currNode->next(timerNode);
                break;
            }
            else
                currNode = currNode->next();
        }
        if(currNode->next() == nullptr && currNode == trackHead){
            if(timerNode->getEventTime() < currNode->getEventTime()) {
                timerNode->next(currNode);
                head = timerNode;
            }
            else {
                currNode->next(timerNode);
            }
        }
        else if(currNode->next() == nullptr){
            currNode->next(timerNode);
        }
    }
}

void EventQueue::addDiskDoneEvent(DiskDoneEvent *dDoneEvent){
    EventNode *trackHead = head;
    EventNode *currNode = head;
    EventNode *ddNode = new EventNode();
    ddNode->addDiskDone(dDoneEvent);
    if(currNode == nullptr){
        head = ddNode;
    }
    else{
        while (currNode->next() != nullptr) {
            if(ddNode->getEventTime() < currNode->getEventTime() && currNode == trackHead){
                ddNode->next(currNode);
                head = ddNode;
                break;
            }
            if(ddNode->getEventTime() >= currNode->getEventTime() && ddNode->getEventTime() <= currNode->next()->getEventTime()){
                ddNode->next(currNode->next());
                currNode->next(ddNode);
                break;
            }
            else
                currNode = currNode->next();
        }
        if(currNode->next() == nullptr && currNode == trackHead) {
            if(ddNode->getEventTime() < currNode->getEventTime()) {
                ddNode->next(currNode);
                head = ddNode;
            }
            else{
                currNode->next(ddNode);
            }
        }
        else if(currNode->next() == nullptr){
            currNode->next(ddNode);
        }
    }
}


EventNode *EventQueue:: getEvent(){
    if(isEmpty()){
        std::cout << "Trying to get event from empty queue. Terminating..\n";
        exit(1);
    }
    EventNode *evNode = head;

    head = head->next();

    return evNode;
}

void EventQueue::print(){
    for(EventNode *curNode = head; curNode != nullptr; curNode = curNode->next()){
        curNode->testPrint();
    }
}

void EventQueue::setTime(float timeSet){currentTime = timeSet;}

float EventQueue::getTime(){return currentTime;}

bool EventQueue::isEmpty() {
    if(head == nullptr){
        return true;
    }
    return false;
}