//
// Created by Guy on 11/11/2020.
//

#ifndef DISKSIM_X_TIMEREVENT_HPP
#define DISKSIM_X_TIMEREVENT_HPP

#include <string>
#include <cstdlib> //Included to use abs() for dist calcs
#include "../CommonFiles/Request.hpp"
#include "../SimulationFiles/Disk.hpp"
#include "../EventDriver/EventQueue.hpp"


class TimerEvent{
public:
    TimerEvent(double setTime){time=setTime;};

    double getTime(){
        return time;
    }


private:

    double time;
};

#endif //DISKSIM_X_TIMEREVENT_HPP
