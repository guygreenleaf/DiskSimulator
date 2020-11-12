#ifndef EventDriver_EventNode_HPP
#define EventDriver_EventNode_HPP

#include "DiskDoneEvent.hpp"
#include "TimerEvent.hpp"
#include <stdlib.h>
#include <iostream>

class TimerEvent;
class Request;
class DiskDoneEvent;


class EventNode {
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false), _next(nullptr) {}

    void addTimer(TimerEvent *timer);

    void addRequest(Request *request);

    void addDiskDone(DiskDoneEvent *dDone);

    double getEventTime();

    EventNode *next();
    void next(EventNode *node);

    TimerEvent *getTimer();
    Request *getRequest();
    DiskDoneEvent *getDiskDone();


    bool isTimerEvent();
    bool isRequestEvent();
    bool isDiskDoneEvent();


    void testPrint();


private: 
    TimerEvent *timerEvent; 
    Request *requestEvent;
    DiskDoneEvent *ddoneEvent;
    EventNode *_next;
    bool isTimer, isRequest, isDDone;
};

#endif