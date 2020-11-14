cmake_minimum_required(VERSION 3.12)
project(DiskSim.x)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcfs.x FCFS_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp)
add_executable(st.x ST_Queue/main.cpp CommonFiles/Request.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp)
add_executable(pu.x PickUp_Queue/main.cpp CommonFiles/Request.cpp PickUp_Queue/PickUpQueue.cpp PickUp_Queue/PickUpQueueNode.cpp)
add_executable(lu.x LookUp_Queue/main.cpp CommonFiles/Request.cpp LookUp_Queue/LookUpQueue.cpp LookUp_Queue/LookUpQueueNode.cpp)
add_executable(clu.x CLookUp_Queue/main.cpp CommonFiles/Request.cpp CLookUp_Queue/CLookUpQueue.cpp CLookUp_Queue/CLookUpQueueNode.cpp)

add_executable(simulation.x main.cpp SimulationFiles/Disk.cpp EventDriver/EventQueue.cpp EventDriver/EventNode.cpp EventDriver/DiskDoneEvent.cpp EventDriver/TimerEvent.hpp CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp LookUp_Queue/LookUpQueue.cpp LookUp_Queue/LookUpQueueNode.cpp CLookUp_Queue/CLookUpQueue.cpp CLookUp_Queue/CLookUpQueueNode.cpp PickUp_Queue/PickUpQueueNode.cpp PickUp_Queue/PickUpQueue.cpp EventDriver/QueueReport.cpp)