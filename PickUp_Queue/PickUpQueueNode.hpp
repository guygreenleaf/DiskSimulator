//
// Created by Guy Greenleaf on 10/22/2020.
//

#ifndef DISKSIM_X_PICKUPQUEUENODE_HPP
#define DISKSIM_X_PICKUPQUEUENODE_HPP

class Request;

class PickUpQueueNode {
public:
    PickUpQueueNode(Request *req);
    PickUpQueueNode *next();
    void next(PickUpQueueNode *node);
    Request *request();

private:
    PickUpQueueNode *_next;
    Request *_request;
};





#endif //DISKSIM_X_PICKUPQUEUENODE_HPP
