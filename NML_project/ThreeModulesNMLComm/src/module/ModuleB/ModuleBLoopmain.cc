
#include <stdlib.h>
#include <signal.h>

#include "rcs.hh"
#include "ModuleB.hh"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int ModuleBLoop_done = 0;

extern "C" void ModuleBLoop_quit(int sig);
void ModuleBLoop_quit(int sig)
{
    ModuleBLoop_done = 1;
}

int main(int argc, char **argv)
{
	set_rcs_print_destination(RCS_PRINT_TO_STDOUT);
    nml_start();

    RCS_TIMER *timer = new RCS_TIMER(0.01);
    MODULE_B *Module_b = new MODULE_B();

    signal(SIGINT, ModuleBLoop_quit);

    while(!ModuleBLoop_done)
	{
        Module_b->PRE_PROCESS();
        Module_b->DECISION_PROCESS();
        Module_b->POST_PROCESS();
        usleep(10000);
	}

    delete Module_b;
	delete timer;
    nml_cleanup();
}

