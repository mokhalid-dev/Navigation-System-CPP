/*
 * CWpDatabase.h
 *
 *  Created on: Nov 22, 2018
 *      Author: swapnil
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_
#include<map>
#include<iterator>
#include"CWaypoint.h"
class CWpDatabase
{
	map<string, CWaypoint> m_Wp;
	map<string, CWaypoint>::iterator m_itrWp;
public:
	CWpDatabase();
	/**
	 * @param CWaypoint& wp
	 * @returnvalue void
	 * It adds the Waypoint to the Map of Waypoint and doesn't allow to override the values in the map
	 */
	void addWaypoint(const CWaypoint& wp);
	/**
	 * @param string name
	 * @return CWypoint*
	 * returns the Waypoint found in the map as a pointer
	 */
	CWaypoint* getPointerToWaypoint(string name);
	/**
	 * @param void
	 * @returnvalue map<string, CWaypoint>
	 * It returns the map containing data of the Database
	 */
	map<string,CWaypoint> getMapOfWp() const;
	/**
	 * @param void
	 * @returnvalue void
	 * It deletes the data of the Waypoint Database
	 */
	void waypointDelete ();
	/**
	 * @param void
	 * @returnvalue void
	 * It prints the map of Wp
	 */
	void print();
};

#endif /* CWPDATABASE_H_ */
