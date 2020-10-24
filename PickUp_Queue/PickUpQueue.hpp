//
// Created by yaweh on 10/22/2020.
//

#ifndef DISKSIM_X_PICKUPQUEUE_HPP
#define DISKSIM_X_PICKUPQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "PickUpQueueNode.hpp"

class Request;

class PickUpQueue: public Queue {

public:
    PickUpQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PickUpQueue();

private:
    PickUpQueueNode *head, *tail;
};








#endif //DISKSIM_X_PICKUPQUEUE_HPP
