//
// Created by Guy Greenleaf on 10/26/2020.
//

#include "CLookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"

//According to the project pdf and the way tracks are laid out according to the pdf,
//the objective of this queue is to have the requests only serviced on
//INWARD sweeps. From the pdf directly: "...,requests are only serviced on the
//inward sweeps (the outward sweeps just return to the outer most request.)"
//According to the picture provided in the pdf, track 1 is on the outermost track, meaning
//this function will sweep in increasing order to the furthest inward track from the r/w head,
//then return to the outer most request without picking things up and travel back up to the request closest but less than
//the first request that was serviced, grabbing every incoming request on the way back up.
//This can also be done with TWO queues, and I realized this

//Example:
//  RW head at 50
//  Queue Currently contains:  52, 65, 79
//  Request comes in at track 55
//  55 is bigger than the r/w head and in between 52 and 65 (it's on the way up from 52 to 65)
//  Queue now contains: 52, 55, 65, 79
//  Request comes in at track 9 and another comes in at track 12 , and then a third at track 48
//  Queue now contains: 52, 55, 65, 79, 9, 12, 48
//  This is because we "jump" back down to 9 after reaching the highest request track (79),
//  and then move back up towards 52 on subsequent requests
//  where tracks are less than the r/w head.


CLookUpQueue::CLookUpQueue() {
    //Linked list for above the rwhead
        aboveHead = nullptr;
        aboveTail = nullptr;

        //Linked list for below the rwhead
        belowHead = nullptr;
        belowTail = nullptr;
}

bool CLookUpQueue::aboveOrBelow(Request *request, int cRWHeadTrack){
    if(request->track() >= cRWHeadTrack){
        return true;
    }
    return false;
}

void CLookUpQueue::addToAbove(Request *request, int cRWHeadTrack){
    if()
}

void CLookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    CLookUpQueueNode *rNode = new CLookUpQueueNode(request);

    if(aboveOrBelow(request, cRWHeadTrack)){
        if(empty()){
             aboveHead = aboveTail = rNode;
        }
        else if(aboveHead == aboveTail){
            if(request->track() > aboveHead->request()->track()){
                aboveHead->next(rNode);
                aboveTail = rNode;
            }
        }
        else{
            addToAbove(request, cRWHeadTrack);
        }
    }

    else{
        if(empty()){
            belowHead = belowTail = rNode;
        }
    }
}



Request *CLookUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    CLookUpQueueNode *aboveNode = aboveHead;
    Request *request = aboveNode->request();

    CLookUpQueueNode *belowNode = belowHead;
    Request *belowRequest = belowNode->request();
    //Set the track to rwhead since that's where we now are.

    aboveHead = aboveHead->next();
    if( aboveHead == nullptr ) {
        if(aboveTail != nullptr) {
            aboveTail = nullptr;
        }
        rwHead = belowRequest->track();
        delete belowNode;
        return belowRequest;
    }
    rwHead = request->track();
    delete aboveNode;
    return request;


}

//Used in testing
int CLookUpQueue::currHead(){
    return rwHead;
}

//Used in testing
void CLookUpQueue::changeRwHead(int track){
    rwHead = track;
}

bool CLookUpQueue::empty() {
    return head == nullptr;
}

void CLookUpQueue::print() {
    for(auto cur = aboveHead; cur; cur = cur->next() )
        cur->request()->print();

    for(auto cur = belowHead; cur; cur = cur->next())
        cur->request()->print();
}

CLookUpQueue::~CLookUpQueue() {
    while( head != nullptr ) {
        CLookUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
