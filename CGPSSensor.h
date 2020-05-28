/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H
#include "CWaypoint.h"
class CGPSSensor {
public:

    CGPSSensor();

    CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
