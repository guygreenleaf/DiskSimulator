//
// Created by yaweh on 11/6/2020.
//

#ifndef DISKSIM_X_EVENTQUEUE_H
#define DISKSIM_X_EVENTQUEUE_H

class EventNode;

class EventQueue {

public:
    virtual EventNode addEvent() = 0;
    virtual bool processEvent() = 0;
    virtual bool isEmpty() = 0;
    virtual ~EventQueue(){};

};

#endif //DISKSIM_X_EVENTQUEUE_H
