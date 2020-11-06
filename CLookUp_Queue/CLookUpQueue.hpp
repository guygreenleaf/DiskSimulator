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
    bool aboveOrBelow(Request *request, int cRWHeadTrack);
    virtual Request *getRequest();
    void addToAbove(Request *request, int cRWHeadTrack);
    int currHead();
    void changeRwHead(int track);
    virtual bool empty();
    virtual void print();
    virtual ~CLookUpQueue();

private:
    CLookUpQueueNode *aboveHead, *aboveTail, *belowHead, *belowTail;
    int rwHead;
};


#endif //DISKSIM_X_CLOOKUPQUEUE_HPP
