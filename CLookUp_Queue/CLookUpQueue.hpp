//
// Created by Guy Greenleaf on 10/26/2020.
//

#ifndef DISKSIM_X_CLOOKUPQUEUE_HPP
#define DISKSIM_X_CLOOKUPQUEUE_HPP

#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "CLookUpQueueNode.hpp"

class Request;

class CLookUpQueue: public Queue {

public:
    CLookUpQueue();

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);

    virtual Request *getRequest();
    CLookUpQueueNode *addToOrderedList(CLookUpQueueNode *listNode, Request *req);
    int currHead();
    void changeRwHead(int track);
    virtual bool empty();
    virtual void print();
    virtual void incReqTracker();
    virtual int getReqTracker();
    virtual ~CLookUpQueue();

private:
    CLookUpQueueNode *aboveHead, *belowHead;
    int reqTracker;
//    int rwHead;
};


#endif //DISKSIM_X_CLOOKUPQUEUE_HPP
