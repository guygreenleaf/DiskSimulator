//
// Created by yaweh on 10/22/2020.
//

#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


bool inRange(int low, int high, int x)
{
    return  ((x-low) <= (high-low));
}

void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    PickUpQueueNode *currNode = head;

    PickUpQueueNode *rNode = new PickUpQueueNode(request);
    int reqTrack = rNode->request()->track();
    if( empty() ) {
        head = tail = rNode;
    } else {
        while(currNode != tail){
            if(inRange()){
                if(reqTrack >= currNode->request()->track()){

                }
            }
            else if(reqTrack < cRWHeadTrack){

            }
        }

        if(head != tail && currNode == tail){

        }

        if(head != nullptr && head == tail){
            if(reqTrack >= cRWHeadTrack){
                if(reqTrack >= currNode->request()->track()){
                    currNode->next(rNode);
                    head = currNode;
                    tail = rNode;
                }
                else{
                    rNode->next(currNode);
                    head = rNode;
                    tail = currNode;
                }

            }
            else if(reqTrack < cRWHeadTrack){
                if(reqTrack < currNode->request()->track()){
                    currNode->next(rNode);
                    head = currNode;
                    tail = rNode;
                }
                else{
                    rNode->next(currNode);
                    head = rNode;
                    tail = currNode;
                }
            }
        }
    }
}

//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
Request *PickUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    PickUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

bool PickUpQueue::empty() {
    return head == nullptr;
}

void PickUpQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

PickUpQueue::~PickUpQueue() {
    while( head != nullptr ) {
        PickUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
