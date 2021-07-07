/*
NMLmsgEx.hh
This C++ header file defines the NMLmsgEx Messages derived from
NMLmsg .

MODIFICATIONS:
Mon Mar 31 21:37  2014	Created by wza.


*/

// Prevent Multiple Inclusion
#ifndef NMLMSGEX_HH
#define NMLMSGEX_HH

// Include Files
#include "nml.hh"
#include "nmlmsg.hh"
//#include "CommonDefinitionX.hh"

#define NMLmsgEx_TYPE 40100






// Define the NML Message Classes
struct PositionData{
    int		llhPos[2];		//经纬度，llpos[i]/SC_POS 单位为度
    int	        gaussPos[2];		//高斯投影位置,cm，
    int         height;                 //cm
    
    int         pitch;                  //欧拉角，单位为0.01度
    int         roll;                   //欧拉角，单位为0.01度
    int         azimuth;                //欧拉角，单位为0.01度,向东为零度，逆时针0-360

    int		positionStatus;		//系统运行状态

    int         reserved[2];
};

class NMLmsgEx : public NMLmsg
{
public:

    //Constructor
    NMLmsgEx(NMLTYPE t,long s);
    NMLmsgEx();

    // CMS Update Function
    void update(CMS *);

    // Place custom variables here.
    int MessageID;

    int MessageSeqNum;

    double local_PC_time;

    PositionData    Position;
};

extern int NMLmsgExFormat(NMLTYPE, void *, CMS *);

#endif 	// NMLMSGEX_HH
