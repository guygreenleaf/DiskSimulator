//
// Created by Guy Greenleaf on 10/26/2020.
//

#ifndef DISKSIM_X_CLOOKUPQUEUENODE_HPP
#define DISKSIM_X_CLOOKUPQUEUENODE_HPP

class Request;

class CLookUpQueueNode {
public:
    CLookUpQueueNode(Request *req);
    CLookUpQueueNode *next();
    void next(CLookUpQueueNode *node);
    Request *request();

private:
    CLookUpQueueNode *_next;
    Request *_request;
};

#endif //DISKSIM_X_CLOOKUPQUEUENODE_HPP
