
I have included multiple files for testing (The main one being sim.txt), as well as a few things in the main.cpp files that have been commented out.
Once I figured out how the random request function was being used, I started doing my own testing with changing the
read/write head, inserting new requests, getting requests from the queues, etc etc.  These tests are detailed in the main.cpp files
and have been commented out for ease of use (or not used at all, just initialized).  I have removed the random request generator from a few of the main.cpp files for readability
purposes and to avoid clutter, as I would be commenting it out at this point anyway if the main.cpp does not use it in a test.

These different queues can be compiled in the following manner:

I have zipped up the entirety of the DiskSim folder.  Once this is unzipped, we can go into the the DiskSim directory and compile different
queues independently from each other.

As mentioned in lectures and labs, this phase of the project only writes output to STDOUT, no additional files are generated.

An example of compiling and running each queue:


1. Compile and run FCFS queue

$ g++ -std=c++17 CommonFiles/Request.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp FCFS_Queue/main.cpp -o fcfs.x
$ ./fcfs.x sim.txt

------------------------------------------------------------------------------

2. Compile and run ST queue

$ g++ -std=c++17 CommonFiles/Request.cpp ST_Queue/STQueue.cpp ST_Queue/STQueueNode.cpp ST_Queue/main.cpp -o st.x
$ ./st.x sim.txt

------------------------------------------------------------------------------

3. Compile and run PickUp Queue

$ g++ -std=c++17 CommonFiles/Request.cpp PickUp_Queue/PickUpQueue.cpp PickUp_Queue/PickUpQueueNode.cpp PickUp_Queue/main.cpp -o pu.x
$ ./pu.x sim.txt

-------------------------------------------------------------------------------

4. Compile and run LookUp queue

$ g++ -std=c++17 CommonFiles/Request.cpp LookUp_Queue/LookUpQueue.cpp LookUp_Queue/LookUpQueueNode.cpp LookUp_Queue/main.cpp -o lu.x
$ ./lu.x sim.txt

--------------------------------------------------------------------------------

5. Compile and run CLookUp queue

$ g++ -std=c++17 CommonFiles/Request.cpp CLookUp_Queue/CLookUpQueue.cpp CLookUp_Queue/CLookUpQueueNode.cpp CLookUp_Queue/main.cpp -o clu.x
$ ./clu.x sim.txt
