//
// Created by Guy Greenleaf on 10/26/2020.
//

#include "CLookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"


void CLookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    CLookUpQueueNode *currNode = head;

    CLookUpQueueNode *rNode = new CLookUpQueueNode(request);
    int reqTrack = rNode->request()->track();

    if( empty() ) {
        head = tail = rNode;

    } else {
        while (currNode != tail) {
            if (reqTrack > cRWHeadTrack) {
                if(currNode == head && currNode->request()->track() < cRWHeadTrack){
                    rNode->next(head);
                    head = rNode;
                    break;
                }
                if (currNode->request()->track() > cRWHeadTrack &&
                    currNode->next()->request()->track() > cRWHeadTrack) {
                    if (reqTrack > currNode->request()->track() && reqTrack <= currNode->next()->request()->track()) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                    if(reqTrack < currNode->request()->track()){
                        if(currNode == head){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }
                        else{
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }


                    }
                    if(reqTrack == currNode->request()->track() && currNode == head) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }else{
                        currNode = currNode->next();
                        continue;
                    }

                } else {
                    if (reqTrack > cRWHeadTrack && reqTrack <= head->request()->track()) {
                        rNode->next(head);
                        head = rNode;
                        break;
                    }
                    if (currNode->next()->request()->track() > cRWHeadTrack){
                        currNode = currNode->next();
                        continue;
                    }
                    else if (currNode->next()->request()->track() != currNode->request()->track()) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                }
            }

            if (reqTrack <= cRWHeadTrack) {
                if(head == currNode && currNode->request()->track() < cRWHeadTrack){
                    if(reqTrack <= currNode->request()->track()){
                        rNode->next(currNode);
                        head = rNode;
                        break;

                    }

                }
                if (currNode->request()->track() >= cRWHeadTrack) {
                    if (currNode->next()->request()->track() < cRWHeadTrack && reqTrack < currNode->request()->track() && currNode->next()->request()->track() > reqTrack) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }else {
                        if (reqTrack > currNode->request()->track() &&
                            reqTrack <= currNode->next()->request()->track()) {
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }
                        else if(currNode == head && reqTrack <= head->request()->track() && reqTrack >= cRWHeadTrack){
                            rNode->next(currNode);
                            head=rNode;
                            break;
                        }
//
//                        else
//                            currNode = currNode->next();
                    }
                }
                if (reqTrack < currNode->next()->request()->track() && reqTrack >= currNode->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }

            if (reqTrack == cRWHeadTrack) {
                rNode->next(head);
                head = rNode;
                break;

            }


        }
            if(head == currNode && tail == head->next() ){
                if(reqTrack > currNode->request()->track() && reqTrack <= currNode->next()->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
            }
            if(reqTrack == currNode->request()->track() && currNode == head){
                rNode->next(currNode->next());
                currNode->next(rNode);
                break;
            }
//            if(reqTrack > currNode->request()->track()){
                currNode = currNode->next();
//            }
        }

        if (head != tail && currNode == tail) {
            tail->next(rNode);
            tail = tail->next();
        }

        if(head != nullptr && head == tail){
            if(reqTrack > cRWHeadTrack){
                if(reqTrack < currNode->request()->track()){
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

            if(reqTrack <= cRWHeadTrack){
                if(currNode->request()->track() <= cRWHeadTrack){
                    rNode->next(currNode);
                    head = rNode;
                    tail = currNode;

                }
                else if(reqTrack > currNode->request()->track()){
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
        }
    }
}


//CHANGE HOW THIS BEHAVES TO HANDLE SAME TRACK REQUESTS AT ANY TIME.
Request *CLookUpQueue::getRequest() {
    if( empty() ) {
        std::cout << "Calling STQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    CLookUpQueueNode *stQueueNode = head;
    Request *request = stQueueNode->request();
    //Set the track to rwhead since that's where we now are.
    rwHead = request->track();
    head = head->next();
    if( head == nullptr )
        tail = nullptr;
    delete stQueueNode;
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
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

CLookUpQueue::~CLookUpQueue() {
    while( head != nullptr ) {
        CLookUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
