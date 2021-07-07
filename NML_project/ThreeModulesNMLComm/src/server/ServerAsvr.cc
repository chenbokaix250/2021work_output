

// Include Files
#include <stdlib.h> // exit()
#include <stdio.h>
#include "rcs.hh" 	// Common RCS definitions
#include "MessageCn.hh"



static NML *MessageC = NULL;

static bool InitNML()
{

    MessageC = new NML(MessageCFormat, "MessageC", "ServerAsvr", "TestConfig.nml");
    if(NULL == MessageC){
        printf("creat MessageC Buffer failed \n");
        return false;
    }
    if(!MessageC->valid())
        return false;



    return true;
}

static void DeleteNML()
{
	// TrafficSign
    if(NULL != MessageC)
	{
        delete MessageC;
        MessageC = NULL;
	}

    if(NULL != MessageC)
	{
        delete MessageC;
        MessageC = NULL;
	}

}

// Main 

int main(int argc, char **argv)
{
    printf("ServerAsvr process begin ... \n");
    nml_cleanup();
    nml_start();

    set_rcs_print_destination(RCS_PRINT_TO_STDOUT);

    if(InitNML() )
    {
        printf("ServerAsvr run_nml_servers() ... \n");
        run_nml_servers();
    }
    else {
        DeleteNML();
    }


}

