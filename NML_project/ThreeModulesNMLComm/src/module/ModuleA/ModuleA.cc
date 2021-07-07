
#include "rcs.hh"
#include "ModuleA.hh"

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include <fstream>







MODULE_A::MODULE_A(int _is_base_class)
{
    if(!_is_base_class)
        INITIALIZE_NML();

    Message_c_data = new MESSAGEC_MSG;
    m_a_recv = false;
    m_b_recv = false;
    m_c_send = false;

}

MODULE_A::~MODULE_A()
{
    delete MESSAGE_A_CHANNEL;
    delete Message_a_data;
    delete MESSAGE_B_CHANNEL;
    delete Message_b_data;
    delete MESSAGE_C_CHANNEL;
    delete Message_c_data;

}

void MODULE_A::INITIALIZE_NML()
{
    MESSAGE_A_CHANNEL = new NML(MessageAFormat, "MessageA", "ModuleA", "TestConfig.nml");
    Message_a_data = (MESSAGEA_MSG *) MESSAGE_A_CHANNEL->get_address();

    MESSAGE_B_CHANNEL = new NML(MessageBFormat, "MessageB", "ModuleA", "TestConfig.nml");
    Message_b_data = (MESSAGEB_MSG *) MESSAGE_B_CHANNEL->get_address();

    MESSAGE_C_CHANNEL = new NML(MessageCFormat, "MessageC", "ModuleA", "TestConfig.nml");
    Message_c_data = (MESSAGEC_MSG *) MESSAGE_C_CHANNEL->get_address();

}


void MODULE_A::PRE_PROCESS()
{
    m_a_recv = false;
    m_b_recv = false;
    m_c_send = false;


    switch(MESSAGE_A_CHANNEL->blocking_read(0.2)) {
    case 0:
        break;
    case -1:
        break;
    case MESSAGEA_MSG_TYPE:
        m_a_recv = true;
        break;
    }

    switch(MESSAGE_B_CHANNEL->blocking_read(0.2)) {
    case 0:
        break;
    case -1:
        break;
    case MESSAGEB_MSG_TYPE:
        m_b_recv = true;
        break;
    }


}

void MODULE_A::POST_PROCESS()
{
    if(m_b_recv && m_a_recv) {

        MESSAGE_C_CHANNEL->write(Message_c_data);




        m_c_send = true;
         std::cout<<"send successed !!!"<<std::endl;

    }


}


void MODULE_A::DECISION_PROCESS()
{
    if( m_b_recv && m_a_recv ) {

        /* --------------
         * -------------*/
//        std::cout<<"recved successed !!!"<<std::endl;

        Message_c_data->c =Message_a_data->a;
        Message_c_data->C = Message_b_data->B;
        std::cout<<"c = a = "<<Message_c_data->c<<",  C = B = "<<Message_c_data->C<<std::endl;

    }


}
