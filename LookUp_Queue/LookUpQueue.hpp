//
// Created by yaweh on 10/26/2020.
//

#ifndef DISKSIM_X_LOOKUPQUEUE_HPP
#define DISKSIM_X_LOOKUPQUEUE_HPP
#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "LookUpQueueNode.hpp"

class Request;

class LookUpQueue: public Queue {

public:
    LookUpQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~LookUpQueue();

private:
    LookUpQueueNode *head, *tail;
};




#endif //DISKSIM_X_LOOKUPQUEUE_HPP
