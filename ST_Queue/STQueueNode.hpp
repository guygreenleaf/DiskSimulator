//
// Created by Guy Greenleaf on 10/22/2020.
//

#ifndef DISKSIM_X_STQUEUENODE_HPP
#define DISKSIM_X_STQUEUENODE_HPP
class Request;

class STQueueNode {
public:
    STQueueNode(Request *req);
    STQueueNode *next();
    void next(STQueueNode *node);
    Request *request();

private:
    STQueueNode *_next;
    Request *_request;
};





#endif //DISKSIM_X_STQUEUENODE_HPP
