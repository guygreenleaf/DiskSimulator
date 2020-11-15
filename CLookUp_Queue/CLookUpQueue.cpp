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
//This can be done with TWO linked lists, and I realized this after my initial submission, where in the first
//"draft" I was using a very long (200+ line) addRequest function that was a mess of if-else and while loops.

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
    //Linkedlist for above the rwhead
        aboveHead = nullptr;

        //Linkedlist for below the rwhead
        belowHead = nullptr;

}

CLookUpQueueNode *CLookUpQueue::addToOrderedList(CLookUpQueueNode *listNode, Request *req){

    //request to be inserted
    CLookUpQueueNode *rNode = new CLookUpQueueNode(req);
    //Keep track of the current head of the list
    CLookUpQueueNode *currHead = listNode;
    //Use a pointer to traverse the list
    CLookUpQueueNode *currNode = listNode;

    //If the head is null, make the incoming request the head
    if(currHead == nullptr){
        currHead = rNode;
    }
    else {
        //Check if the next node is null, while it's not:
        while (currNode->next() != nullptr) {
            //if the current node's track is less than or equal to the request node's track AND the next node's track
            //is greater than or equal to the request node's track, insert it into the list ast the next node from currNode.
            if (currNode->request()->track() <= rNode->request()->track() && currNode->next()->request()->track() >= rNode->request()->track()) {
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }


            //If we're at the head AND the request node's track is less than the current head's track, make the request node
            //the new head.
            if (currNode == currHead && rNode->request()->track() < currHead->request()->track()) {
                rNode->next(currHead);
                currHead = rNode;
                break;
            }
            //Maintain FCFS property if the current node's request track is equal to the request node's track.
            if(rNode->request()->track() == currNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            //If all of the above cases fail to trigger, go to the next node and try again.
            currNode = currNode->next();
        }

        //If the next node is nullptr AND we're at the head (only 1 node in list):
        if (currNode->next() == nullptr && currNode == currHead) {
            //Determine which place to put the incoming request node
            if (currNode->request()->track() > req->track()) {
                rNode->next(currNode);
                currHead = rNode;
                return currHead;
            } else
                currNode->next(rNode);
        }
        //If we're at the end of a list with more than one node, insert the request as the next node
        if (currNode->next() == nullptr) {
            currNode->next(rNode);
        }
    }
    return currHead;
}


void CLookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    //Check if the request is greater than or equal to the rwhead. 
    //If it is, add to the aboveHead list
    //Otherwise, add it to the belowHead list.
    if(cRWHeadTrack <= request->track()){
        aboveHead = addToOrderedList(aboveHead, request);
    }
    else
        belowHead = addToOrderedList(belowHead, request);
}



Request *CLookUpQueue::getRequest() {
//If the aboveHead list has reached a nullptr, check the belowHead list
    if( aboveHead == nullptr ) {
        if(belowHead != nullptr) {
            aboveHead = nullptr;
            CLookUpQueueNode *belowNode = belowHead;
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
    //If the aboveHead list has a request in it, return and delete the it.
    else if(aboveHead != nullptr) {
        CLookUpQueueNode *aboveNode = aboveHead;
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
//int CLookUpQueue::currHead(){
//    return rwHead;
//}
//
////Used in testing
//void CLookUpQueue::changeRwHead(int track){
//    rwHead = track;
//}

bool CLookUpQueue::empty() {
    return aboveHead == nullptr && belowHead == nullptr;
}

//Print the above list, and then the below
void CLookUpQueue::print() {
    for(auto cur = aboveHead; cur; cur = cur->next() )
        cur->request()->print();

    for(auto cur = belowHead; cur; cur = cur->next())
        cur->request()->print();
}

void CLookUpQueue::incReqTracker(){
    reqTracker++;
}

int CLookUpQueue::getReqTracker(){
    return reqTracker;
}

//Deconstructor change this
CLookUpQueue::~CLookUpQueue() {
    while( aboveHead != nullptr ) {
        CLookUpQueueNode *node = aboveHead;
        aboveHead = node->next();
        delete node;
    }
    while( belowHead != nullptr ) {
        CLookUpQueueNode *node = belowHead;
        belowHead = node->next();
        delete node;
    }
}


