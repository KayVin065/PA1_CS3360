#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;

// constants
const double MTBF = 500; // Mean Time Between Failures in hours
const int TOTAL_HOURS = 365 * 24 * 20; // Total number of hours in 20 years
const int RESTORATION_TIME = 10; // Restoration time in hours

// generate exponentially distributed value using uniform distribution
double genExpDistr(double t) {
    double z = ((double)rand()/(double)RAND_MAX);
    double x = (-1 * t) * (log(z));
    return x;
}

// loop to simulate a server's failure and recovery times
// uses exponentially distributed nums to generate time between failures
void simulateServer(vector<double>& failures, vector<double>& recoveries) {
    double currTime = 0.0,
           uptime = 0.0,
           recoveryTime = 0.0;

    while(currTime < TOTAL_HOURS) {
        // failure time handling
        // exponentially generate time until the next failure
        uptime = genExpDistr(MTBF);
        currTime += uptime;

        // ensure time does not go over total number of hours
        if(currTime >= TOTAL_HOURS) { break; }

        failures.push_back(currTime); // record time of failure

        // recovery time handling
        recoveryTime = currTime + RESTORATION_TIME;

        if(currTime >= TOTAL_HOURS) { break; }

        recoveries.push_back(recoveryTime); // record recovery time
        currTime = recoveryTime;
    }
}

// checks if there's overlap between system recovery times
double systemFailure(vector<double>& s1Recovery, vector<double>& s2Recovery) {
    size_t i = 0, j = 0;

    // compare recovery times for both systems
    while(i < s1Recovery.size() && j < s2Recovery.size()) {
        // recovery times are not equal, so there's no overlap
        if(s1Recovery[i] < s2Recovery[j]) {
            i++;
        } else {
            if(i > 0 && s2Recovery[j] < s1Recovery[i - 1] + RESTORATION_TIME) {
                return s2Recovery[j];
            }

            j++;
        }
    }


    // check for remaining values in system 1
    while(i < s1Recovery.size()) {
        if(s1Recovery[i] < s2Recovery.back() + RESTORATION_TIME) {
            return s1Recovery[i];
        }

        i++;
    }

    // check for remaining values in system 2
    while(j < s2Recovery.size()) {
        if(s2Recovery[j] < s1Recovery.back() + RESTORATION_TIME) {
            return s2Recovery[j];
        }

        j++;
    }

    return TOTAL_HOURS;
}

int main() {
    const int NUM_SIMULATIONS = 100;
    double totalFailTime = 0.0,
           failTime = 0.0;

    // part a
    vector<double> s1Failure,
                   s1Recovery,
                   s2Failure,
                   s2Recovery;

    simulateServer(s1Failure, s1Recovery); // simulate first server
    simulateServer(s2Failure, s2Recovery); // simulate second server

    cout << "System 1 Failures:\n\n";
    for(int i = 0; i < s1Failure.size(); i++) {
        cout << s1Failure[i] << " hours" << endl;
    }

    cout << "\nSystem 1 Recoveries:\n\n";
    for(int i = 0; i < s1Recovery.size(); i++) {
        cout << s1Recovery[i] << " hours" << endl;
    }

    cout << "\nSystem 2 Failures:\n\n";
    for(int i = 0; i < s2Failure.size(); i++) {
        cout << s2Failure[i] << " hours" << endl;
    }

    cout << "\nSystem 2 Recoveries:\n\n";
    for(int i = 0; i < s2Recovery.size(); i++) {
        cout << s2Recovery[i] << " hours" << endl;
    }


    // part b
    // simulate multiple times
    for(int i = 0; i < NUM_SIMULATIONS; i++) {
        vector<double> s1FailureB,
                       s1RecoveryB,
                       s2FailureB,
                       s2RecoveryB;

        srand(time(0) + i); // generate a unique seed for each simulation

        simulateServer(s1FailureB, s1RecoveryB); // simulate first server
        simulateServer(s2FailureB, s2RecoveryB); // simulate second server

        failTime = systemFailure(s1RecoveryB, s2RecoveryB);
        totalFailTime += failTime;
    }

    cout << "\nAverage Time Before Failure: "
         << totalFailTime / NUM_SIMULATIONS << " hours" << endl;

    return 0;
}
