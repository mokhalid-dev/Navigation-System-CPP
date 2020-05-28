/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPOI_H
#define CPOI_H
#include <string>
#include "t_poi.h"
#include "CWaypoint.h"
using namespace std;
#define RESTAURANTVal 0
#define TOURISTICVal 1
#define GASSTATIONVal 2
#define UNIVERSITYVal 3
/*
 * Class CPOI inherits class CWaypoint
 */
class CPOI:public CWaypoint{
	friend ostream& operator<<(ostream& out, const CPOI& poi);
private:
    string m_description;
    t_poi m_type;
    //CWaypoint wp;
public:

    CPOI(t_poi type=RESTAURANT,string name="random",string description="Test Poi",
    		double latitude=0,double longitude=0);

    void print();

    void getAllDataByReference(string& name, double& latitude, double& longitude,t_poi& type, string& description);

    bool operator==(const CPOI& poi);
};
/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
