#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

// given the time t, generate an exponentially distributed number
// uses formula x = -t(ln(z)), where z is a real number uniformly
// distributed (0,1)
// t = 1 for calculating requested service time
// t = 1 / lambda for calculating inter-arrival time
double genExpDistr(double t) {
    double z = ((double)rand()/(double)RAND_MAX);
    double x = (-1 * t) * (log(z));
    return x;
}

int main() {

    srand(time(0));
    int processID = 1;
    double currIA = 0.0,            // current inter-arrival time
           arrivalTime = 0.0,       // arrival time of current process
           prevArrival = 0.0,       // arrival time of previous process
           reqServiceTime = 0.0,    // requested service time
           totalServiceTime = 0.0;  // sum of all service times

    while(processID <= 1000) {
        // generate exponentially distributed random numbers for
        // inter-arrival time and requested service time
        currIA = genExpDistr(0.5);
        reqServiceTime = genExpDistr(1.0);
        arrivalTime = currIA + prevArrival;

        // increment total service time
        totalServiceTime += reqServiceTime;

        cout << processID << ", " << arrivalTime << ", " << reqServiceTime << endl;

        // update the previous arrival time and processID
        prevArrival = arrivalTime;
        processID++;
    }

    // output calculated actual average arrival rate and service time
    cout << endl << "Avg Arrival Rate: " << (1000 / arrivalTime)
         << ", Avg Service Time: " << (totalServiceTime / 1000) << endl;

    return 0;
}
