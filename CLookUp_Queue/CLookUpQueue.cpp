//
// Created by Guy Greenleaf on 10/26/2020.
//

#include "CLookUpQueue.hpp"
#include "../CommonFiles/Request.hpp"

//According to the project pdf and the way tracks are laid out,
//the objective of this queue is to have the requests only serviced on
//INWARD sweeps. From the pdf directly: "...,requests are only serviced on the
//inward sweeps (the outward sweeps just return to the outer most request.)"
//According to the picture provided in the pdf, track 1 is on the outermost track, meaning
//this function will sweep in increasing order to the furthest inward track from the r/w head,
//then return to the outer most request and travel back up to the request closest but less than
//the first request that was serviced.

void CLookUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

    CLookUpQueueNode *currNode = head;

    CLookUpQueueNode *rNode = new CLookUpQueueNode(request);
    //Easy way to reference the incoming request's track
    int reqTrack = rNode->request()->track();

    if( empty() ) {
        head = tail = rNode;

    } else {
        //While we haven't hit the tail, do the following:
        while (currNode != tail) {
            //Check if the request track is greater than the read/write head track. If it is, do the following:
            if (reqTrack > cRWHeadTrack) {
                //If the current node is the head of the queue AND the current node's track is less than the read/write head,
                //Set the incoming request as the head, then break.
                if(currNode == head && currNode->request()->track() < cRWHeadTrack){
                    rNode->next(head);
                    head = rNode;
                    break;
                }
                //If the current node's track is greater than the read write head AND the the next node's track is
                //greater than the read write head as well, do the following checks:
                if (currNode->request()->track() > cRWHeadTrack &&
                    currNode->next()->request()->track() > cRWHeadTrack) {
                    //If the request track is greater than the current node's request track AND the request track
                    //is less than or equal to the next node's track,
                    //Set the request node's next to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    if (reqTrack > currNode->request()->track() && reqTrack <= currNode->next()->request()->track()) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                    //If the request track is less than the current node's track, check the following:
                    if(reqTrack < currNode->request()->track()){
                        //If the current node is equal to the head at this point, set the request track to the head
                        //and break.
                        if(currNode == head){
                            rNode->next(currNode);
                            head = rNode;
                            break;
                        }
                        //Otherwise, at this point
                        //Set the request node's next to the next node in the queue and then set the current nodes next to the request node
                        //Then break.
                        else{
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }
                    }
                    //If the request track is equal to the current node's track and the current node is the head,
                    //Set the request node's next to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    if(reqTrack == currNode->request()->track() && currNode == head) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                        //Otherwise, go to the next node and continue.
                    }else{
                        currNode = currNode->next();
                        continue;
                    }

                }
                //If this point is hit it means the current node's track is less than or equal to the read/write track OR
                //the NEXT node's track is less than or equal to the read/write head.
                else {
                    //If the request track is less than the read write head AND the request track is less than or equal
                    //to the head's track, set the request track equal to the head, then break.
                    if (reqTrack > cRWHeadTrack && reqTrack <= head->request()->track()) {
                        rNode->next(head);
                        head = rNode;
                        break;
                    }
                    //If the next node's track is greater than the read/write head, go the next node and continue.
                    if (currNode->next()->request()->track() > cRWHeadTrack){
                        currNode = currNode->next();
                        continue;
                    }
                    //Otherwise, if the next node's track is not equal to the current node's track,
                    //Set the request node's next to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    else if (currNode->next()->request()->track() != currNode->request()->track()) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                }
            }

            //If the request track is less than or equal to the read/write head track, do the following checks:
            if (reqTrack <= cRWHeadTrack) {
                //If the head is equal to the current node and the current node's request track is less than the read/write head,
                //check the following:
                if(head == currNode && currNode->request()->track() < cRWHeadTrack){
                    //If the request track is less than or equal to the current node's request track,
                    //set the request node as the new head, then break.
                    if(reqTrack <= currNode->request()->track()){
                        rNode->next(currNode);
                        head = rNode;
                        break;

                    }
                }
                //If the current node's track is greater than or equal to the read/write head, check the following:
                if (currNode->request()->track() >= cRWHeadTrack) {
                    //If the current node's track is less than the read/write head AND the request track is less than
                    //the current node's track AND the next node's track is greater than the request track,
                    //Set the request node's next to the next node in the queue and then set the current nodes next to the request node
                    //Then break.
                    if (currNode->next()->request()->track() < cRWHeadTrack && reqTrack < currNode->request()->track() && currNode->next()->request()->track() > reqTrack) {
                        rNode->next(currNode->next());
                        currNode->next(rNode);
                        break;
                    }
                    else{
                        //Otherwise, if the request track is greater than the current node's track AND the request
                        //track is less than or equal to the next node's track,
                        //set the request node's next to the next node in the queue and then set the current nodes next to the request node
                        //then break.
                        if (reqTrack > currNode->request()->track() &&
                            reqTrack <= currNode->next()->request()->track()) {
                            rNode->next(currNode->next());
                            currNode->next(rNode);
                            break;
                        }
                        //Else, if the current node is the head AND the request track is less than or equal
                        //to the head's track AND the request track is greater than or equal to the r/w head,
                        //set the request node as the new head and break.
                        else if(currNode == head && reqTrack <= head->request()->track() && reqTrack >= cRWHeadTrack){
                            rNode->next(currNode);
                            head=rNode;
                            break;
                        }
                    }
                }
                //If the request track is less than the next node's track AND the request track is greater than
                //or equal to the current node's track,
                //set the request node's next to the next node in the queue and then set the current nodes next to the request node
                //then break.
                if (reqTrack < currNode->next()->request()->track() && reqTrack >= currNode->request()->track()){
                    rNode->next(currNode->next());
                    currNode->next(rNode);
                    break;
                }
            //If the request track is equal to the current read/write head at this point, set the request track
            //as the new head and break.
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
                currNode = currNode->next();
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
