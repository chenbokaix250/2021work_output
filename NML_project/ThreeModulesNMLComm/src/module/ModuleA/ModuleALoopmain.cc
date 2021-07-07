
#include <stdlib.h>
#include <signal.h>

#include "rcs.hh"
#include "ModuleA.hh"

#include <sys/time.h>
#include <stdio.h>

int ModuleALoop_done = 0;

extern "C" void ModuleALoop_quit(int sig);
void ModuleALoop_quit(int sig)
{
    ModuleALoop_done = 1;
}

int main(int argc, char **argv)
{
	set_rcs_print_destination(RCS_PRINT_TO_STDOUT);
    nml_start();

    RCS_TIMER *timer = new RCS_TIMER(0.01);
    MODULE_A *Module_a = new MODULE_A();

    signal(SIGINT, ModuleALoop_quit);

    while(!ModuleALoop_done)
	{
        Module_a->PRE_PROCESS();
        Module_a->DECISION_PROCESS();
        Module_a->POST_PROCESS();
//        usleep(10000);
	}

    delete Module_a;
	delete timer;
    nml_cleanup();
}

