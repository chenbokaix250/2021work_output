

// Prevent Multiple Inclusion
#ifndef MESSAGECN_HH
#define MESSAGECN_HH

// Include Files
#include "rcs.hh" 	// Common RCS definitions

#include "NMLmsgExn.hh"
// Trying to merge the type ids often results in redefinn the ID twice..
// RCS-Design-MERGE-DISABLE Edits to the following area will NOT be preserved by the RCS-Design tool.
#include "CommonDefinitionX.hh"


// Define the integer type ids.
#define MESSAGEC_MSG_TYPE 40103
// RCS-Design-MERGE-ENABLE Edits after this line will be preserved by the RCS-Design tool.




// Define the NML Message Classes
class MESSAGEC_MSG : public NMLmsgEx
{
public:
    //Constructor
    MESSAGEC_MSG();

    // CMS Update Function
    void update(CMS *);

    // Place custom variables here.
    char c;
    double C;




};

// Declare NML format function
extern int MessageCFormat(NMLTYPE, void *, CMS *);

#endif 	// MESSAGECN_HH
