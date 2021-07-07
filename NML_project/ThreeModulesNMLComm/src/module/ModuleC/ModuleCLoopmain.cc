
#include <stdlib.h>
#include <signal.h>

#include "rcs.hh"
#include "ModuleC.hh"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int ModuleCLoop_done = 0;

extern "C" void ModuleCLoop_quit(int sig);
void ModuleCLoop_quit(int sig)
{
    ModuleCLoop_done = 1;
}

int main(int argc, char **argv)
{
	set_rcs_print_destination(RCS_PRINT_TO_STDOUT);
    nml_start();

    RCS_TIMER *timer = new RCS_TIMER(0.01);
    Module_C *Module_c = new Module_C();

    signal(SIGINT, ModuleCLoop_quit);

    while(!ModuleCLoop_done)
	{
        Module_c->PRE_PROCESS();
        Module_c->DECISION_PROCESS();
        Module_c->POST_PROCESS();
        usleep(10000);
	}

    delete Module_c;
	delete timer;
    nml_cleanup();
}

