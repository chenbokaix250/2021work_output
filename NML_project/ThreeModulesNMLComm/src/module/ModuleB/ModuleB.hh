
#ifndef ATTRIBUTEANALYSIS_HH
#define ATTRIBUTEANALYSIS_HH

#include "rcs.hh"

#include "MessageAn.hh"
#include "MessageBn.hh"



#include "stdio.h"
//#include "Common.h"


#include <pthread.h>



class MODULE_B
{
public:

    MODULE_B(int _is_base_class = 0); // Constructor
    ~MODULE_B();

	virtual void PRE_PROCESS();
    virtual void DECISION_PROCESS();
	virtual void POST_PROCESS();
	virtual void INITIALIZE_NML();

    NML *MESSAGE_A_CHANNEL;
    MESSAGEA_MSG *Message_a_data;

    NML *MESSAGE_B_CHANNEL;
    MESSAGEB_MSG *Message_b_data;

    bool m_a_send;
    bool m_b_send;



};

#endif








