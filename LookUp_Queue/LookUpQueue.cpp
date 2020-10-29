//
// Created by Guy on 10/26/2020.
//
#include "LookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void LookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    LookUpQueueNode *currNode = head;

    LookUpQueueNode *rNode = new LookUpQueueNode(request);

    int reqTrack = rNode->request()->track();

    if( empty() ) {
        head = tail = rNode;

    } else {
        while (currNode != tail) {
            if(reqTrack > cRWHeadTrack){
                if(reqTrack > currNode->request()->track() && reqTrack < currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                if(reqTrack > currNode->request()->track() && reqTrack > currNode->next()->request()->track()){
//                    if(currNode->next()->request()->track() > cRWHeadTrack){
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
//                    }
//                    if(currNode->next()->request()->track() <= cRWHeadTrack){
//
//                    }
//                    else {
//                        currNode = currNode->next();
//                    }

                }

            }


            if(reqTrack < cRWHeadTrack){
                if(reqTrack > currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
                else {
                    currNode = currNode->next();
                }

            }


            if(reqTrack == cRWHeadTrack){
                rNode->next(head);
                head = rNode;
            }
        }

        if (head != tail && currNode == tail) {
            if(reqTrack <= tail->request()->track()) {
                tail->next(rNode);
                tail = rNode;
            }
            else{
                currNode->next(rNode);
                rNode->next(tail);
            }
        }

        if(head != nullptr && head == tail){
            if(reqTrack < cRWHeadTrack) {
               if(reqTrack > currNode->request()->track()){
                   rNode->next(currNode);
                   head = rNode;
                   tail = currNode;
               }
               else{
                   currNode->next(rNode);
                   head = currNode;
                   tail = rNode;
               }
            }

            if(reqTrack > cRWHeadTrack){
                if(currNode->request()->track() >= cRWHeadTrack){
                    if(reqTrack >= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    else{
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }
                if(currNode->request()->track() < cRWHeadTrack){
                    if(reqTrack <= currNode->request()->track()){
                        currNode->next(rNode);
                        tail = rNode;
                        head = currNode;
                    }
                    if(reqTrack > currNode->request()->track()){
                        rNode->next(currNode);
                        head = rNode;
                        tail = currNode;
                    }
                }

            }
            if(reqTrack == cRWHeadTrack){
                currNode->next(rNode);
                head = currNode;
                tail = rNode;
            }
        }
    }
}


//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
Request *LookUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    LookUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
    return request;
}

bool LookUpQueue::empty() {
    return head == nullptr;
}

void LookUpQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

LookUpQueue::~LookUpQueue() {
    while( head != nullptr ) {
        LookUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
