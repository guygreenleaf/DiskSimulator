//
// Created by Guy on 11/6/2020.
//

#ifndef DISKSIM_X_EVENTQUEUE_H
#define DISKSIM_X_EVENTQUEUE_H

#include "EventNode.hpp"
#include "../CommonFiles/Request.hpp"
#include "../CommonFiles/Queue.hpp"
#include "TimerEvent.hpp"
class EventNode;
class Request;
class DiskDoneEvent;

class EventQueue{

public:
    EventQueue(): head(nullptr){};

    void addRequest(Request *req);

    void addTimerEvent(TimerEvent *aTimer);
    void addDiskDoneEvent(DiskDoneEvent *dDoneEvent);
    EventNode *getEvent();
    bool isEmpty();
    void print();

    float getTime();
    void setTime(float timeSet);
    ~EventQueue(){};

private:
    EventNode *head;
    float currentTime = 0;
};

#endif //DISKSIM_X_EVENTQUEUE_H
