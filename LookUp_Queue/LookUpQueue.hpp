//
// Created by Guy Greenleaf on 10/26/2020.
//

#ifndef DISKSIM_X_LOOKUPQUEUE_HPP
#define DISKSIM_X_LOOKUPQUEUE_HPP
#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "LookUpQueueNode.hpp"

class Request;

class LookUpQueue: public Queue {

public:
    LookUpQueue();

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();

    LookUpQueueNode *addToOrderedList(LookUpQueueNode *listNode, Request *req);
    LookUpQueueNode *addToOrderedListTwo(LookUpQueueNode *listNode, Request *req);
    int currHead();
    void changeRwHead(int track);
    virtual bool empty();
    virtual void print();
    virtual void incReqTracker();
    virtual int getReqTracker();
    virtual ~LookUpQueue();

private:
    LookUpQueueNode *aboveHead, *belowHead;
    int reqTracker;
//    int rwHead;
};




#endif //DISKSIM_X_LOOKUPQUEUE_HPP
