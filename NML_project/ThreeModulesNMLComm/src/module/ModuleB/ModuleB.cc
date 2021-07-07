
#include "rcs.hh"
#include "ModuleB.hh"

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#include <fstream>







MODULE_B::MODULE_B(int _is_base_class)
{
    if(!_is_base_class)
        INITIALIZE_NML();

    Message_a_data = new MESSAGEA_MSG;
    Message_b_data = new MESSAGEB_MSG;

    m_a_send = false;
    m_b_send = false;

}

MODULE_B::~MODULE_B()
{

}

void MODULE_B::INITIALIZE_NML()
{
    MESSAGE_A_CHANNEL = new NML(MessageAFormat, "MessageA", "ModuleB", "TestConfig.nml");
//    Message_a_data = (MESSAGEA_MSG *) MESSAGE_A_CHANNEL->get_address();

    MESSAGE_B_CHANNEL = new NML(MessageBFormat, "MessageB", "ModuleB", "TestConfig.nml");
//    Message_b_data = (MESSAGEB_MSG *) MESSAGE_B_CHANNEL->get_address();



}


void MODULE_B::PRE_PROCESS()
{
    m_a_send = false;
    m_b_send = false;



}

void MODULE_B::POST_PROCESS()
{

    MESSAGE_A_CHANNEL->write(Message_a_data);
    m_a_send = true;


    MESSAGE_B_CHANNEL->write(Message_b_data);
    m_b_send = true;


}


void MODULE_B::DECISION_PROCESS()
{

    Message_a_data->a = 'a';
    Message_a_data->A = 2;
    Message_b_data->b = 'b';
    Message_b_data->B = 4;
    std::cout<<"send successed !!!"<<std::endl;
}
