Guy Greenleaf

Attended tutoring with Soren - discussed general concepts relating to the project

No help given

Implementation is all original code, no external websites used.

All features required for this submission have been implemented.

I have included multiple files for testing, as well as a few things in the main.cpp files that have been commented out
Once I figured out how the random request function was being used, I started doing my own testing with changing the
read/write head, inserting new requests, getting requests from the queues, etc etc.  These tests are detailed in the main.cpp files
and have been commented out for ease of use.  I have removed the random request generator from a few of the main.cpp files for readability
purposes and to avoid clutter, as I would be commenting it out at this point anyway if the main.cpp does not use it in a test.

These different queues can be compiled in the following manner:

I have zipped up the entirety of the DiskSim folder.  Once this is unzipped, we can go into the the DiskSim directory and compile different
queues independently from eachother.

As mentioned in lectures and labs, this phase of the project only writes output to STDOUT, no additional files are generated.

An example of compiling and running each queue:

Let's say that DiskSim.zip was sitting in the current working directory:

$unzip DiskSim.zip

$cd DiskSim

1. Compile and run FCFS queue

$