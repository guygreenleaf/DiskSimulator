//
// Created by yaweh on 10/26/2020.
//

#ifndef DISKSIM_X_CLOOKUPQUEUE_HPP
#define DISKSIM_X_CLOOKUPQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "CLookUpQueueNode.hpp"

class Request;

class CLookUpQueue: public Queue {

public:
    CLookUpQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~CLookUpQueue();

private:
    CLookUpQueueNode *head, *tail;
};


#endif //DISKSIM_X_CLOOKUPQUEUE_HPP
