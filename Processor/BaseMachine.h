/*
 * BaseMachine.h
 *
 */

#ifndef PROCESSOR_BASEMACHINE_H_
#define PROCESSOR_BASEMACHINE_H_

#include "Tools/time-func.h"
#include "OT/OTTripleSetup.h"
#include "ThreadJob.h"
#include "ThreadQueues.h"

#include <map>
#include <fstream>
using namespace std;

class BaseMachine
{
protected:
    static BaseMachine* singleton;

    std::map<int,Timer> timer;

    string compiler;
    string domain;

    void print_timers();

    virtual void load_program(string threadname, string filename);

public:
    static thread_local int thread_num;

    string progname;
    int nthreads;

    vector<OTTripleSetup> ot_setups;

    ThreadQueues queues;

    static BaseMachine& s();
    static bool has_singleton() { return singleton != 0; }

    static string memory_filename(string type_short, int my_number);

    static string get_domain(string progname);
    static int ring_size_from_schedule(string progname);
    static int prime_length_from_schedule(string progname);
    static bigint prime_from_schedule(string progname);

    BaseMachine();
    virtual ~BaseMachine() {}

    void load_schedule(string progname, bool load_bytecode = true);
    void print_compiler();

    void time();
    void start(int n);
    void stop(int n);

    virtual void reqbl(int n) { (void)n; throw runtime_error("not defined"); }

    OTTripleSetup fresh_ot_setup();
};

inline OTTripleSetup BaseMachine::fresh_ot_setup()
{
    return ot_setups.at(thread_num).get_fresh();
}

#endif /* PROCESSOR_BASEMACHINE_H_ */
