#ifndef INC_phold_h
#define INC_phold_h

#include <ross.h>

	/*
	 * PHOLD Types
	 */

class phold_state : public LP_State
{
    std::shared_ptr<long>	 dummy_state;

public:
    phold_state() = default;
    phold_state(const phold_state &a) = default;

    phold_state(phold_state&& rhs) = default;              // move constructor
    phold_state& operator=(phold_state&& rhs) = default;   // move assignment operator

    phold_state * clone() const override
    {
        return new phold_state(*this);
    }

    long get_dummy_state() { return *dummy_state.get(); }
    void set_dummy_state(long l) { dummy_state = std::make_shared<long>(l); }
};

struct phold_message
{
	long int	 dummy_data;
};

	/*
	 * PHOLD Globals
	 */
tw_stime lookahead = 1.0;
static unsigned int stagger = 0;
static unsigned int offset_lpid = 0;
static tw_stime mult = 1.4;
static tw_stime percent_remote = 0.25;
static unsigned int ttl_lps = 0;
static unsigned int nlp_per_pe = 8;
static int g_phold_start_events = 1;
static int optimistic_memory = 100;

// rate for timestamp exponential distribution
static tw_stime mean = 1.0;

static char run_id[1024] = "undefined";

#endif
