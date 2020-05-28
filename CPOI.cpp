/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;
//preprosesor directives
//Own Include Files
#include "CPOI.h"
#include "CWaypoint.h"
//Method Implementations
/*
 * Constructor of class CPOI
 * @param t_poi type	-The initial value of poi type, default value = RESTAURANT(IN)
 * @param string name	-The initial value of poi name, default value = random (iN)
 * @param string description -  The initial value of poi description, default value = Test Poi (IN)
 * @param double latitude - The initial value of poi latitude, default value = 0 (IN)
 * @param double longitude - The initial value of poi longitude, default value = 0 (IN)
 *
 */
CPOI::CPOI(t_poi type,string name,string description,double latitude,double longitude):CWaypoint(){
	m_type = type;
	m_description = description;
	set(name,latitude,longitude);
}
/*
 * Print method of CPOI class
 * @param void
 * @returnvalue void
 * It simply calls the print method of CWaypoint to print the values.
 */
void CPOI::print(){
	cout<<"Point Of Interest"<<endl<<"============="<<endl;
	switch(m_type){
		case RESTAURANTVal:
			cout << "of type RESTAURANT"<<": "<<m_description<<endl;
			break;
		case TOURISTICVal:
			cout << "of type TOURISTIC"<<": "<<m_description<<endl;
			break;
		case GASSTATIONVal:
			cout << "of type GASSTATION"<<": "<<m_description<<endl;
			break;
		case UNIVERSITYVal:
			cout << "of type UNIVERSITY"<<": "<<m_description<<endl;
			break;
	}
	CWaypoint::print(MMSS);
}
/*
 * Function returns all the values of class CPOI by reference
 * @param t_poi type	-The value of poi type(OUT)
 * @param string name	-The value of poi name (OUT)
 * @param string description -  The value of poi description (OUT)
 * @param double latitude - The value of poi latitude(OUT)
 * @param double longitude - The value of poi longitude (OUT)
 * @returnvalue void
 */
void CPOI::getAllDataByReference(string& name, double& latitude,
		double& longitude,t_poi& type, string& description){
	type = m_type;
	description = m_description;
	CWaypoint::getAllDataByReference(name,latitude,longitude);
	/*name = getName();
	latitude = getLatitude();
	longitude = getLongitude();*/
}

ostream& operator<<(ostream& out, const CPOI& poi)
{
	out<<"Point Of Interest"<<endl<<"============="<<endl;
	switch(poi.m_type){
		case RESTAURANTVal:
			out << "of type RESTAURANT"<<": "<<poi.m_description<<endl;
			break;
		case TOURISTICVal:
			out << "of type TOURISTIC"<<": "<<poi.m_description<<endl;
			break;
		case GASSTATIONVal:
			out << "of type GASSTATION"<<": "<<poi.m_description<<endl;
			break;
		case UNIVERSITYVal:
			out << "of type UNIVERSITY"<<": "<<poi.m_description<<endl;
			break;
	}
	int deg,mm = 0;
	double ss = 0;
	poi.transformLatitude2degmmss(deg,mm,ss);
	out << poi.getName() << " on "<<"Latitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s";
	poi.transformLongitude2degmmss(deg,mm,ss);
	out<<" and Longitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s"<<endl;
	//out<<poi.getName()<<" on Latitude "<<poi.getLatitude()<<" and on Longitude "<<poi.getLongitude();
	return out;
}

bool CPOI::operator ==(const CPOI& poi)
{
	bool checkEquality;
	if(this->m_name == poi.m_name &&
			this->m_latitude == poi.m_latitude &&
			this->m_longitude == poi.m_longitude&&
			this->m_description == poi.m_description&&
			this->m_type == poi.m_type){
		checkEquality = true;
	}
	else{
		checkEquality = false;
	}
	return checkEquality;
}
