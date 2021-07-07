
#ifndef ATTRIBUTEANALYSIS_HH
#define ATTRIBUTEANALYSIS_HH

#include "rcs.hh"

#include "MessageCn.hh"



#include "stdio.h"
//#include "Common.h"


#include <pthread.h>



class Module_C
{
public:

    Module_C(int _is_base_class = 0); // Constructor
    ~Module_C();

	virtual void PRE_PROCESS();
    virtual void DECISION_PROCESS();
	virtual void POST_PROCESS();
	virtual void INITIALIZE_NML();

    NML *MESSAGE_C_CHANNEL;
    MESSAGEC_MSG *Message_c_data;



    bool m_c_recv;



};

#endif








