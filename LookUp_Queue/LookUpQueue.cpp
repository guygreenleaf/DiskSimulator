//
// Created by Guy Greenleaf on 10/26/2020.
//
#include "LookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"

//First go from the rwhead to the largest track of incoming requests, then go out to the smallest picking up the
//requests that weren't picked up on the initial sweep.

//Constructor for two linked lists
LookUpQueue::LookUpQueue() {
    aboveHead = nullptr;
    belowHead = nullptr;
}

//This operates the same exact way the addToOrderedList in CLOOKUP works, infact it is the same function,
//I have just replaced the datatypes in order to support LookUp. Please see comments on addToOrderedList for CLookUp_Queue
//for a thorough analysis of this function and how it works.

LookUpQueueNode *LookUpQueue::addToOrderedList(LookUpQueueNode *listNode, Request *req){
    LookUpQueueNode *rNode = new LookUpQueueNode(req);
    //Keep track of the current head of the list
    LookUpQueueNode *currHead = listNode;
    //Use a pointer to traverse the list
    LookUpQueueNode *currNode = listNode;
    //If the head is null, make the incoming request the head
    if(currHead == nullptr){
        currHead = rNode;
    }
    else {
        while (currNode->next() != nullptr) {
            if (currNode->request()->track() <= rNode->request()->track() && currNode->next()->request()->track() >= rNode->request()->track()) {
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            if (currNode == currHead && rNode->request()->track() < currHead->request()->track()) {
                rNode->next(currHead);
                currHead = rNode;
                break;
            }
            if(rNode->request()->track() == currNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            currNode = currNode->next();
        }

        if (currNode->next() == nullptr && currNode == currHead) {
            if (currNode->request()->track() > req->track()) {
                rNode->next(currNode);
                currHead = rNode;
                return currHead;
            } else
                currNode->next(rNode);

        }
        if (currNode->next() == nullptr) {
            currNode->next(rNode);
        }
    }
    return currHead;
}

//This is wildly similar to the above, the only difference is the changing of the operands > and <  in order to facilitate
//descending order insertion.

LookUpQueueNode *LookUpQueue::addToOrderedListTwo(LookUpQueueNode *listNode, Request *req) {
    LookUpQueueNode *rNode = new LookUpQueueNode(req);
    //Keep track of the current head of the list
    LookUpQueueNode *currHead = listNode;
    //Use a pointer to traverse the list
    LookUpQueueNode *currNode = listNode;
    //If the head is null, make the incoming request the head
    if(currHead == nullptr){
        currHead = rNode;
    }
    else {
        while (currNode->next() != nullptr) {
            if (currNode->request()->track() >= rNode->request()->track() && currNode->next()->request()->track() <= rNode->request()->track()) {
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            if (currNode == currHead && rNode->request()->track() > currHead->request()->track()) {
                rNode->next(currHead);
                currHead = rNode;
                break;
            }
            if(rNode->request()->track() == currNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            currNode = currNode->next();
        }

        if (currNode->next() == nullptr && currNode == currHead) {
            if (currNode->request()->track() < req->track()) {
                rNode->next(currNode);
                currHead = rNode;
                return currHead;
            } else
                currNode->next(rNode);

        }
        if (currNode->next() == nullptr) {
            currNode->next(rNode);
        }
    }
    return currHead;
}

void LookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    //Compare request track w/RWHead and add to either list accordingly
    if(cRWHeadTrack <= request->track()){
        aboveHead = addToOrderedList(aboveHead, request);
    }
    else
        belowHead = addToOrderedListTwo(belowHead, request);

}


Request *LookUpQueue::getRequest() {
    //Check if aboveHead list has hit a nullptr, if it has, check the belowHead list.
    if( aboveHead == nullptr ) {
        if(belowHead != nullptr) {
            aboveHead = nullptr;
            LookUpQueueNode *belowNode = belowHead;
            Request *belowRequest = belowNode->request();
            belowHead = belowHead->next();
//            rwHead = belowRequest->track();
            delete belowNode;
            return belowRequest;
        }
        else {
            std::cout << "Attempted to getrequest on empty queue. Terminating..." << std::endl;
            exit(1);
        }

    }
    //If the aboveHead list has requests in it, return one and delete it from the list.
    else if(aboveHead != nullptr) {
        LookUpQueueNode *aboveNode = aboveHead;
        Request *request = aboveNode->request();
        aboveHead = aboveHead->next();
//        rwHead = request->track();
        delete aboveNode;
        return request;
    }
    else{
        std::cout << "Attempted to getrequest on empty queue. Terminating..." <<std::endl;
        exit(1);
    }
}

////Used in testing
//int LookUpQueue::currHead(){
//    return rwHead;
//}
//
////Used in testing
//void LookUpQueue::changeRwHead(int track){
//    rwHead = track;
//}

bool LookUpQueue::empty() {
    return aboveHead == nullptr && belowHead == nullptr;
}

void LookUpQueue::print() {
    for(auto cur = aboveHead; cur; cur = cur->next() )
        cur->request()->print();

    for(auto cur = belowHead; cur; cur = cur->next())
        cur->request()->print();
}

void LookUpQueue::incReqTracker(){
    reqTracker++;
}

int LookUpQueue::getReqTracker(){
    return reqTracker;
}

LookUpQueue::~LookUpQueue() {
    while( aboveHead != nullptr ) {
        LookUpQueueNode *node = aboveHead;
        aboveHead = node->next();
        delete node;
    }
    while( belowHead != nullptr ) {
        LookUpQueueNode *node = belowHead;
        belowHead = node->next();
        delete node;
    }
}
