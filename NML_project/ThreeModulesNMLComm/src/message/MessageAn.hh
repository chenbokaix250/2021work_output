

// Prevent Multiple Inclusion
#ifndef MESSAGEAN_HH
#define MESSAGEAN_HH

// Include Files
#include "rcs.hh" 	// Common RCS definitions

#include "NMLmsgExn.hh"
// Trying to merge the type ids often results in redefinn the ID twice..
// RCS-Design-MERGE-DISABLE Edits to the following area will NOT be preserved by the RCS-Design tool.
#include "CommonDefinitionX.hh"


// Define the integer type ids.
#define MESSAGEA_MSG_TYPE 40101
// RCS-Design-MERGE-ENABLE Edits after this line will be preserved by the RCS-Design tool.




// Define the NML Message Classes
class MESSAGEA_MSG : public NMLmsgEx
{
public:
    //Constructor
    MESSAGEA_MSG();

    // CMS Update Function
    void update(CMS *);

    // Place custom variables here.
    char a;
    double A;



};

// Declare NML format function
extern int MessageAFormat(NMLTYPE, void *, CMS *);

#endif 	// MESSAGEAN_HH
