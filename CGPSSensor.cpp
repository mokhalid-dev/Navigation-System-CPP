/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;
//Own Include Files
#include "CGPSSensor.h"
#include "CWaypoint.h"
//pre-processor directives
//#define DEBUG
//Method Implementations
/*
 * Constructor of CGPSSensor class
 * Non-Parameterized constructor
 */
CGPSSensor::CGPSSensor(){
	//getCurrentPosition();
}

/*
 * Member Function of Class CGPSSensor - getCurrentPosition
 * it doesn't have any parameters
 * It asks for user inputs for latitude and longitudes
 * @returnvalue object of type CWaypoint
 *
 */
CWaypoint CGPSSensor::getCurrentPosition(){
	cout << "GPS Sensor"<<endl;
	double latitude,longitude;
	do {
		cout<<"Enter Latitude: ";
		cin>>latitude;
		while(cin.fail()){
			cin.clear();
			cin.ignore(256,'\n');
			cout << "Bad Entry please enter a number";
			cin >> latitude;
		}
		if (latitude >= -90 && latitude <= 90){
			break;
		}
		else{
			cout << "Warning!! Latitude Values could be between -90 to +90 only. Again..... "<< endl;
			continue;
		}
	}while(true);
	do {
		cout<<"Enter Longitude: ";
		cin>>longitude;
		while(cin.fail()){
			cin.clear();
			cin.ignore(256,'\n');
			cout << "Bad Entry please enter a number";
			cin >> longitude;
		}
		if (longitude >= -180 && longitude <= 180){
			break;
		}
		else{
			cout << "Warning!! Longitude Values could be between -180 to +180 only. Again..... "<< endl;
			continue;
		}
	}while(true);
	CWaypoint wp;
	wp.set("GPSPoint",latitude,longitude);
#ifdef DEBUG
	cout<<wp.getName()<<"\t"<<wp.getLatitude()<<"\t"<<wp.getLongitude();
#endif
	return wp;
}
