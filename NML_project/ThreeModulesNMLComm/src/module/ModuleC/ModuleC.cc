
#include "rcs.hh"
#include "ModuleC.hh"

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include <fstream>







Module_C::Module_C(int _is_base_class)
{
    if(!_is_base_class)
        INITIALIZE_NML();

//    Message_c_data = new MESSAGEC_MSG;

    m_c_recv = false;

}

Module_C::~Module_C()
{
    delete MESSAGE_C_CHANNEL;
    delete Message_c_data;

}

void Module_C::INITIALIZE_NML()
{

    MESSAGE_C_CHANNEL = new NML(MessageCFormat, "MessageC", "ModuleC", "TestConfig.nml");
    std::cout<<"hello"<<std::endl;

    Message_c_data = (MESSAGEC_MSG *) MESSAGE_C_CHANNEL->get_address();

    std::cout<<"hello"<<std::endl;



}


void Module_C::PRE_PROCESS()
{
    m_c_recv = false;

    switch(MESSAGE_C_CHANNEL->blocking_read(0.2)) {
    case 0:
        break;
    case -1:
        printf("error reading: %d\n", MESSAGE_C_CHANNEL->error_type);
        break;
    case MESSAGEC_MSG_TYPE:
        m_c_recv = true;
        break;
    }



}

void Module_C::POST_PROCESS()
{


}


void Module_C::DECISION_PROCESS()
{
    if( m_c_recv ){
        std::cout<<"recved: "<<Message_c_data->c<<"     "<<Message_c_data->C<<std::endl;





    }

}
