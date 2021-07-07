

// Prevent Multiple Inclusion
#ifndef MESSAGEBN_HH
#define MESSAGEBN_HH

// Include Files
#include "rcs.hh" 	// Common RCS definitions

#include "NMLmsgExn.hh"
// Trying to merge the type ids often results in redefinn the ID twice..
// RCS-Design-MERGE-DISABLE Edits to the following area will NOT be preserved by the RCS-Design tool.
#include "CommonDefinitionX.hh"


// Define the integer type ids.
#define MESSAGEB_MSG_TYPE 40102
// RCS-Design-MERGE-ENABLE Edits after this line will be preserved by the RCS-Design tool.




// Define the NML Message Classes
class MESSAGEB_MSG : public NMLmsgEx
{
public:
    //Constructor
    MESSAGEB_MSG();

    // CMS Update Function
    void update(CMS *);

    // Place custom variables here.
    char b;
    double B;



};

// Declare NML format function
extern int MessageBFormat(NMLTYPE, void *, CMS *);

#endif 	// MESSAGEBN_HH
