/*
 * CWpDatabase.cpp
 *
 *  Created on: Nov 22, 2018
 *      Author: swapnil
 */

#include "CWpDatabase.h"
#include <iostream>
using namespace std;
//#define DEBUG
CWpDatabase::CWpDatabase()
{
	// TODO Auto-generated constructor stub

}
/**
 * @param CWaypoint& wp
 * @returnvalue void
 * It adds the Waypoint to the Map of Waypoint and doesn't allow to override the values in the map
 */
void CWpDatabase::addWaypoint(const CWaypoint& wp)
{
	bool check = false;
	if(m_Wp.find(wp.getName()) != m_Wp.end()){
		check = true;
	}
	if(check == false){
		m_Wp.insert(pair<string,CWaypoint>(wp.getName(),wp));
	}
	else{
		cout << "The value already exists and therefore can't allow to insert again for key value"
				<<" "<<wp.getName()<<endl;
	}
#ifdef DEBUG
	cout << "CPOI object created in the Database";
	cout << "\nThe map m_POI is : \n";
	cout << "\tKEY\tELEMENT\n";
	for(m_itrWp=m_Wp.begin();m_itrWp != m_Wp.end();m_itrWp++){
		cout << "\t" << m_itrWp->first
				<< "\t" << &(m_itrWp->second) << "\n";
	}
#endif
}

/**
 * @param string name
 * @return CWypoint*
 * returns the Waypoint found in the map as a pointer
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	map<string, CWaypoint>::iterator itr;
	if(m_Wp.find(name) != m_Wp.end()){
		itr = m_Wp.find(name);
		return &(itr->second);
	}
	else{
		cout << "The POI not present"<<endl;
		return NULL;
	}

	/*for(m_itrWp=m_Wp.begin();m_itrWp != m_Wp.end();m_itrWp++){
		if(m_itrWp->first == name){
			return &(m_itrWp->second);
		}
	}*/
	//cout << "The POI not present"<<endl;
}

/**
 * @param void
 * @returnvalue map<string, CWaypoint>
 * It returns the map containing data of the Database
 */
map<string, CWaypoint> CWpDatabase::getMapOfWp() const
{
	return m_Wp;
}
/**
 * @param void
 * @returnvalue void
 * It deletes the data of the Waypoint Database
 */
void CWpDatabase::waypointDelete()
{
	m_Wp.clear();
}
/**
 * @param void
 * @returnvalue void
 * It prints the map of Wp
 */
void CWpDatabase::print()
{
	cout << "\nThe map m_WP is : \n";
	cout << "\tKEY\tELEMENT\n";
	for(m_itrWp=m_Wp.begin();m_itrWp != m_Wp.end();m_itrWp++){
		cout << "\t" << m_itrWp->first<<"\t";
		m_itrWp->second.print(MMSS);
		cout<< endl;
	}
}
