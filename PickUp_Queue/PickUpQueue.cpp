//
// Created by yaweh on 10/22/2020.
//

#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    PickUpQueueNode *currNode = head;

    PickUpQueueNode *rNode = new PickUpQueueNode(request);
    if( empty() ) {
        head = tail = rNode;
        cRWHeadTrack = rNode->request()->track();
    } else {
        while(currNode != tail){

            cRWHeadTrack = currNode->request()->track();
            if(cRWHeadTrack == rNode->request()->track() && currNode->next()->request()->track() != rNode->request()->track()){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
            else if(/**cRWHeadTrack < rNode->request()->track() &&**/  currNode->request()->track() == rNode ->request()->track() && rNode->request()->track() == currNode->next()->request()->track()){
                currNode = currNode->next();
            }
            else if (rNode->request()->track() < currNode->request()->track() && currNode == head){
                rNode->next(currNode);
                head = rNode;
                break;
            }

            else{
                if(rNode->request()->track() > currNode->request()->track() && rNode->request()->track() < currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                if(rNode->request()->track() > currNode->request()->track()){
                    currNode = currNode->next();
                }
            }
        }

        if(head != tail && currNode == tail){
            tail->next(rNode);
            tail = tail->next();
        }

        if(head != nullptr && head == tail){
            cRWHeadTrack = currNode->request()->track();
            if(rNode->request()->track() < cRWHeadTrack){
                rNode->next(currNode);
                head = rNode;
                tail = currNode;
            }
            else {
                head = currNode;
                tail = rNode;
                head->next(tail);
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
