/*
 * CWaypoint.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: swapnil
 */

#include "CWaypoint.h"
#include <iostream>
#include <string>
#include <math.h>
#define Radius 6378.17
#define pi 3.14159265
//#define SHOWADDRESS
//#define SHOWVALUE

using namespace std;

/*CWaypoint::CWaypoint()
{
	// TODO Auto-generated constructor stub
	m_name = "Random";
	m_latitude = 0;
	m_longitude = 0;
#ifdef SHOWADDRESS
		cout <<"Default Object created at : " << this<<endl;
		cout << "name is at \t"<<&m_name<<endl<<"latitude is at \t"<<&m_latitude<<endl<<"longitude is at \t"<<&m_longitude<<endl;
#endif
#ifdef SHOWVALUE
		cout << "name is : "<<m_name<<endl;
		cout << "Latitude is : "<<m_latitude<<endl;
		cout << "Longitude is : "<<m_latitude<<endl;
#endif
}*/
/*
 * Constructor of class CWaypoint
 * @param string name	-> it allows it to add name to CWaypoint default value = "Random"(IN)
 * @param double latitude -> It allows it to add latitude to CWaypoint default value = 0(IN)
 * @param double longitude -> It allows it to add longitude to CWaypoint default value = 0(IN)
 */
CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	// Condition Based Object Creator
	set(name,latitude,longitude);
#ifdef SHOWADDRESS
		cout <<"Object created at : " << this<<endl;
		cout << "name is at \t"<<&m_name<<endl<<"latitude is at \t"<<&m_latitude<<endl<<"longitude is at \t"<<&m_longitude<<endl;
#endif
#ifdef SHOWVALUE
		cout << "name is : "<<m_name<<endl;
		cout << "Latitude is : "<<m_latitude<<endl;
		cout << "Longitude is : "<<m_longitude<<endl;
#endif
}
/*
 * Destructor of CWaypoint
 */
CWaypoint::~CWaypoint()
{
	// TODO Auto-generated destructor stub
}
/*
 * This method is used to set value for the object
 * @param string name	-> it allows it to add name to CWaypoint (IN)
 * @param double latitude -> It allows it to add latitude to CWaypoint (IN)
 * @param double longitude -> It allows it to add longitude to CWaypoint (IN)
 */
void CWaypoint::set(string name, double latitude, double longitude)
{
	// Function to set the Values for an object
	// counter variable to store the no. of alphabets in name string
	unsigned int counter =0;
	// check variables to check all three conditions for member variables
	bool checkName,checkLatitude,checkLongitude = false;
	for (unsigned int pos=0;pos<name.length();pos++){
		// To check whether the string is correct or not
		if(isalpha(name[pos]) || isspace(name[pos])){

			counter++;
		}
	}
	// To check the length of the string name matches the counter variable
	if (counter == name.length()){
		m_name = name;
		checkName = true;
	}
	else{
		m_name = "Random";
	}
	// Condition to check whether the latitude values are in range or not
	if (latitude >= -90 && latitude <=90){
		m_latitude = latitude;
		checkLatitude = true;
	}
	else{
		m_latitude = 0;
	}
	// Condition to check whether the longitude values are in range or not
	if (longitude >= -180 && longitude <= 180){
		m_longitude = longitude;
		checkLongitude = true;
	}
	else{
		m_longitude = 0;
	}
	// returning the checked result
	if ((checkName || checkLatitude || checkLongitude)!= true){
		cout << "Warning!!! Since All the attributes are wrong calling default constructor : ";
		m_name = "Random";
		m_longitude = 0;
		m_latitude = 0;
	}
}
/*
 * Getter Function for name
 * @param void
 * @returnvalue string
 */
string CWaypoint::getName() const
{
	// Function to get the name from an object
	return m_name;
}
/*
 * Getter Function for Latitude
 * @param void
 * @returnvalue double
 */
double CWaypoint::getLatitude() const
{
	// Function to get the Latitude from an object
	return m_latitude;
}
/*
 * Getter Function for Longitude
 * @param void
 * @returnvalue double
 */
double CWaypoint::getLongitude() const
{
	// Function to get the Longitude from an object
	return m_longitude;
}
/*
 * Getter Function for name,longitude and latitude by reference
 * @param string& name -> to return by reference the value of name stored in an object
 * @param double& latitude -> to return by reference the value of latitude stored in an object
 * @param double& longitude -> to return by reference the value of longitude stored in an object
 * @returnvalue void
 */
void CWaypoint::getAllDataByReference(string& name, double& latitude,
		double& longitude) const
{
	// Function to get the all value from an object by using call by reference
	name = this->m_name;
	latitude = this->m_latitude;
	longitude = this->m_longitude;
	/* Since the values are sent as reference these will have the values stored
	 * in the object's member variable's and any changes will be reflected*/
}
/*
 * Function for Calculating Distance Between Two Points using const reference to object
 * @param const CWaypoint& wp	-> This variable is reference from which the distance needs
 * 									to be calculated.
 * @returnvalue double -> the distance between two waypoints
 */
double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	//double dist = R *(acos(sin(this->latitude))*(sin(wp.latitude))+(cos(this->latitude))*cos(wp.latitude)*cos(this->latitude - wp.latitude));
	double lati1 = (this->m_latitude)*(pi/180);
	double lati2 = (wp.m_latitude)*(pi/180);
	double longi1 = (this->m_longitude)*(pi/180);
	double longi2 = (wp.m_longitude)*(pi/180);
	double value1 = (sin(lati1))*(sin(lati2));
	double value2 = (cos(lati1))*(cos(lati2))*(cos(longi2 - longi1));
	double dist = Radius * acos(value1 + value2);
	return dist;
}
/*
 * Function for printing the values of Object of CWaypoint
 * @param int format -> this enters the value 1 or 2 :-
 * 1 for printing in degrees
 * 2 for printing in minutes and seconds
 * @returnvalue void
 */
void CWaypoint::print(int format)
{
	int deg,mm = 0;
	double ss = 0;
	// Function to print the details of an object using a specific format
	switch(format){
	case DEG:
		cout << getName() << " on "<<"Latitude = "<<getLatitude()<<" and Longitude = "<<getLongitude()<<endl;
		break;
	case MMSS:
		transformLatitude2degmmss(deg,mm,ss);
		cout << getName() << " on "<<"Latitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s";
		transformLongitude2degmmss(deg,mm,ss);
		cout<<" and Longitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s"<<endl;
		break;
	}
}
/*
 * Function used to convert the value of longitude from degree into minutes and seconds
 * @param  int& deg		-> sending degree as reference to this function (IN)
 * @param  int& mm		-> sending mm as reference to function (IN)
 * @param  double& ss	-> sending ss as reference to function (IN)
 * @returnvale void
 */
void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss) const
{
	// Function to transform Longitude to degrees, minutes and seconds
	transform2degmmss(deg,mm,ss,m_longitude);
}
/*
 * Function used to convert the value of latitude from degree into minutes and seconds
 * @param  int& deg		-> sending degree as reference to this function (IN)
 * @param  int& mm		-> sending mm as reference to function (IN)
 * @param  double& ss	-> sending ss as reference to function (IN)
 * @returnvalue void
 */
void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss) const
{
	// Function to transform Latitude to degrees, minutes and seconds
	transform2degmmss(deg,mm,ss,m_latitude);
}

void CWaypoint::transform2degmmss(int& deg, int& mm, double& ss,double whichValue) const{
	double intPart,fractPart,intPart1,fractPart1;
	fractPart = modf(whichValue,&intPart);
	deg = intPart;
	fractPart1 = modf(fractPart*60,&intPart1);
	mm = intPart1;
	ss = fractPart1*60;
}

ostream& operator<<(ostream& out,const CWaypoint& wp)
{
	//out << wp.getName() << " on "<<"Latitude = "<<wp.getLatitude()<<" and Longitude = "<<wp.getLongitude()<<endl;
	int deg,mm = 0;
	double ss = 0;
	wp.transformLatitude2degmmss(deg,mm,ss);
	out << wp.getName() << " on "<<"Latitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s";
	wp.transformLongitude2degmmss(deg,mm,ss);
	out<<" and Longitude = "<<deg<<"deg "<<mm<<"min "<<ss<<"s"<<endl;
	return out;
}

bool CWaypoint::operator ==(const CWaypoint& wp)
{
	bool checkEquality;
	if(this->m_name == wp.m_name && this->m_latitude == wp.m_latitude && this->m_longitude == wp.m_longitude){
		checkEquality = true;
	}
	else{
		checkEquality = false;
	}
	return checkEquality;
}
