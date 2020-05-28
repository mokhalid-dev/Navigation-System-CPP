/*
 * CWaypoint.h
 *
 *  Created on: Oct 22, 2018
 *      Author: swapnil
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_
#include <string>
#define DEG 1
#define MMSS 2
using namespace std;
class CWaypoint
{
	friend ostream& operator<<(ostream& out, const CWaypoint& wp);
protected:
	string m_name;
	double m_latitude;
	double m_longitude;
public:
	// default Constructor
	//CWaypoint();
	CWaypoint(string name="Random",double latitude=0,double longitude=0);
	// Destructor
	virtual ~CWaypoint(); // virtual because the dynamic cast requires to destruct the object
	// Function to set the Values for an object
	void set(string name,double latitude,double longitude);
	// Function to get the name from an object
	string getName() const;
	// Function to get the Latitude from an object
	double getLatitude() const;
	// Function to get the Longitude from an object
	double getLongitude() const;
	// Function to get the all value from an object by using call by reference
	void getAllDataByReference(string& name,double& latitude, double& longitude) const;
	// Function for Calculating Distance Between Two Points using const reference to object
	double calculateDistance(const CWaypoint& wp);
	// Function to print the details of an object using a specific format
	void print(int format);
	// Function to transform Longitude to degrees, minutes and seconds
	void transformLongitude2degmmss(int& deg,int& mm,double& ss) const;
	// Function to transform Latitude to degrees, minutes and seconds
	void transformLatitude2degmmss(int& deg,int& mm,double& ss) const;
	bool operator == (const CWaypoint& wp);
	// Function to transform values to degrees, minutes and seconds
private:
	void transform2degmmss(int& deg, int& mm, double& ss, double whichValue) const;
};

#endif /* CWAYPOINT_H_ */
