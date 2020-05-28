/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
//preprocessor directive
//#define DEBUGCopy
//#define DEBUG
//Own Include Files
#include "CRoute.h"
#include "CWaypoint.h"
#include "CPoiDatabase.h"
//Method Implementations
/*
 * Constructor of class CRoute
 * @param void
 */
CRoute::CRoute(){
	m_pPoiDatabase = NULL;//CPoiDatabase();
	m_pWpDatabase = NULL;
}
/*
 * Copy Constructor which generates deep copy of an object CRoute
 * @param const CRoute& origin	-> The value of object which needs to be copied(IN)
 * */
CRoute::CRoute(const CRoute& origin){
	this->m_route = origin.m_route; // '=' operator creates a deep copy for list as shown by the below print statements
	this->m_itrRoute = origin.m_itrRoute;
	this->m_pPoiDatabase = origin.m_pPoiDatabase;
	this->m_pWpDatabase = origin.m_pWpDatabase;
#ifdef DEBUGCopy
	cout << "The location of first element of the list from which copy is made \t"<<&(*origin.m_route.begin())<<endl;
	cout << "The location of first element of the list into which copy is made \t"<<&(*this->m_route.begin())<<endl;
#endif
}
/*
 * Destructor which deletes the dynamic array created by the constructor
 */
CRoute::~CRoute(){

}
/**
 * This function allows the CRoute class to connect with the Wp Database we are working on
 * @param CWpDatabase* pWpDB	-> input variable for connecting to existing WP Database (IN)
 * @returnvalue void
 */
bool CRoute::connectToWpDatabase(APT::CDatabase<CWaypoint>* pWpDB)
{
	bool checkWpDb;
	if(pWpDB == NULL){
		checkWpDb = false;
		cout << "CRoute not connected to WpDatabase";
	}
	else{
		checkWpDb = true;
		m_pWpDatabase = pWpDB;
	}
	return checkWpDb;
#ifdef DEBUG
	if(m_pPoiDatabase != NULL){
		cout << "CRoute connected to WP Database";
	}
#endif
}

/*
 * This function allows the CRoute class to connect with the POI Database we are working on
 * @param CPoiDatabase* pPoiDB	-> input variable for connecting to existing POI Database (IN)
 * @returnvalue void
 */
bool CRoute::connectToPoiDatabase(APT::CDatabase<CPOI>* pPoiDB){
	bool checkPoiDb;
	if(pPoiDB == NULL){
		checkPoiDb = false;
		cout << "CRoute not connected to PoiDatabase";
		//return checkPoiDb;
	}
	else{
		m_pPoiDatabase = pPoiDB;
		checkPoiDb = true;
		//return checkPoiDb;
	}
	return checkPoiDb;
#ifdef DEBUG
	if(m_pPoiDatabase != NULL){
		cout << "CRoute connected to PoiDatabase";
	}
#endif
}
/*
 * This function allows us to add Waypoint to the route
 * @param string name -> It finds the pointer to waypoint from Waypoint database(IN)
 * @returnvalue void
 */
void CRoute::addWaypoint(string name){
	if(m_pWpDatabase != NULL){
		//if(m_pWpDatabase->getPointerToWaypoint(name) != NULL){
		if(m_pWpDatabase->getPointerToDbObj(name) != NULL){
			if(m_route.empty()){
				m_itrRoute = m_route.begin();
				//m_route.insert(m_itrRoute,m_pWpDatabase->getPointerToWaypoint(name));
				m_route.insert(m_itrRoute,m_pWpDatabase->getPointerToDbObj(name));
			}
			else{
				//m_route.push_back(m_pWpDatabase->getPointerToWaypoint(name));
				m_route.push_back(m_pWpDatabase->getPointerToDbObj(name));
			}
		}
		else{
			cout << name<<" Not found in WayPoint Database";
		}
	}
	else{
		cout << "Please connect to the WayPoint Database";
	}
}
/*
 * This function allows us to add POI to the route
 * @param string namePoi -> The namePoi which helps to find the pointer to CPOI from Database(IN)
 * @param string afterWp -> The afterWp after which the Poi needs to be added (IN)
 * @returnvalue void
 */
void CRoute::addPoi(string namePoi,string afterWp){
	if(m_pPoiDatabase != NULL){
		if(m_pWpDatabase != NULL){
			if(m_route.size() != 0)
				//if(m_pWpDatabase->getPointerToWaypoint(afterWp) != NULL){
				if(m_pWpDatabase->getPointerToDbObj(afterWp) != NULL){
					list <CWaypoint*>::iterator itr;
					for(m_itrRoute = m_route.begin();m_itrRoute != m_route.end();m_itrRoute++){
						if((*m_itrRoute)->getName() == afterWp){
							itr = m_itrRoute;
						}
					}
					//if(m_pPoiDatabase->getPointerToPoi(namePoi) != NULL){
					if(m_pPoiDatabase->getPointerToDbObj(namePoi) != NULL){
						if(itr != m_route.end()){
							//m_route.insert(++itr,m_pPoiDatabase->getPointerToPoi(namePoi));
							m_route.insert(++itr,m_pPoiDatabase->getPointerToDbObj(namePoi));
						}
						else{
							//m_route.push_back(m_pPoiDatabase->getPointerToPoi(namePoi));
							m_route.push_back(m_pPoiDatabase->getPointerToDbObj(namePoi));
						}
					}
					else{
						cout<<"POI not present in the POI Database"<<endl;
					}

					/*bool check = false;
					unsigned int index = 0;
					unsigned int soughtIndex = 0;
					for(m_itrRoute = m_route.begin();m_itrRoute != m_route.end();m_itrRoute++,index++){
						if((*m_itrRoute)->getName() == afterWp){
							check = true;
							soughtIndex = index;
						}
					}
					//m_itrRoute = find (m_route.begin(),m_route.end(),afterWp);
					if(check && soughtIndex == (m_route.size()-1)){
						if(m_pPoiDatabase->getPointerToPoi(namePoi) != NULL){
							m_route.push_back(m_pPoiDatabase->getPointerToPoi(namePoi));
						}
						else{
							cout<<"POI not present in the POI Database"<<endl;
						}
					}
					else{
						cout<< "The WayPoint "<<afterWp<<" is not present at the last"<<endl;
					}*/
				}
				else{
					cout << "The last Waypoint entered is not present in the WpDatabase"<<endl;
					cout << "Therefore adding POI at the end"<<endl;
					//if(m_pPoiDatabase->getPointerToPoi(namePoi) != NULL){
					if(m_pPoiDatabase->getPointerToDbObj(namePoi) != NULL){
						//m_route.push_back(m_pPoiDatabase->getPointerToPoi(namePoi));
						m_route.push_back(m_pPoiDatabase->getPointerToDbObj(namePoi));
					}
					else{
						cout<<"POI not present in the POI Database"<<endl;
					}
				}
			else{
				cout<<"Since the route is empty,"<<endl;
				cout << "Therefore adding POI at the end"<<endl;
				//if(m_pPoiDatabase->getPointerToPoi(namePoi) != NULL){
				if(m_pPoiDatabase->getPointerToDbObj(namePoi) != NULL){
					//m_route.push_back(m_pPoiDatabase->getPointerToPoi(namePoi));
					m_route.push_back(m_pPoiDatabase->getPointerToDbObj(namePoi));
				}
				else{
					cout<<"POI not present in the POI Database"<<endl;
				}
			}
		}
		else{
			cout << "Please connect to the WayPoint Database"<<endl;
		}
	}
	else{
		cout << "Please connect to the CPOI Database"<<endl;
	}
}
/*
 * This function returns the min distance between gps point and returns value of the poi as reference
 * @param CWaypoint& wp	-> The value of the GPS point as CWaypoint object
 * @param CPOI& poi		-> The empty poi object used to return nearest poi by reference
 * @returnvalue double	-> The distance between gps point and the nearest poi
 */
/*double CRoute::getDistanceNextPoi(CWaypoint& wp, CPOI& poi){
	double refDistance = 0;
	double minDistance = 0;
	for(unsigned int arrCounter = 0; arrCounter<m_maxPoi; arrCounter++){
		refDistance = m_pPoi[arrCounter]->calculateDistance(wp);
		if(arrCounter == 0){
			minDistance = refDistance;
			poi = *m_pPoi[arrCounter];
		}
		if(refDistance < minDistance){
			minDistance = refDistance;
			poi = *m_pPoi[arrCounter];
		}
	}
	return minDistance;
}*/
/*
 * This function prints the No. of Waypoints and POI's in the route
 * @param void
 * @returnvalue void
 */
void CRoute::print(){
	/**
	 * case 1)
	 * Here if we use (*m_itrRoute)->print(MMSS)
	 * Then it only prints name, longitude and latitude for waypoint or Poi
	 * since the object for linker is only of type waypoint
	 * case 2)
	 * Here if we use cout<<(**m_itrRoute)<<endl;
	 * Then it only prints name, longitude and latitude for waypoint or Poi
	 * since the object for linker is only of type waypoint
	 */
	for(m_itrRoute = m_route.begin();m_itrRoute != m_route.end();m_itrRoute++){
		if(dynamic_cast<CPOI*>(*m_itrRoute) != NULL){
			cout << (*dynamic_cast<CPOI*>(*m_itrRoute))<<endl;
		}
		else{
			cout<<(**m_itrRoute)<<endl;
		}
	}


	/*cout << "Our Route has "<<m_nextWp<<" Waypoints and "<<m_nextPoi<<" Point of Interest"<<endl;
	for(unsigned int arrCounter = 0; arrCounter<m_nextWp; arrCounter++){
		if(m_pWaypoint != NULL){
			m_pWaypoint[arrCounter].print(MMSS);
		}
		else{
			cout<<"waypoint array doesn't exist";
		}

	}
	for(unsigned int arrCounter = 0; arrCounter<m_nextPoi; arrCounter++){
		if(m_pPoi[arrCounter] != NULL && m_pPoiDatabase != NULL){
			m_pPoi[arrCounter]->print();
		}
		else{
			cout<<"POI at : "<<arrCounter<<" Doesn't exist Or The Database is not connected";
		}
	}*/
}
/**
 * @param const CRoute& cr - object of route class[IN]
 * @return CRoute	- object of route class[OUT]
 * This operator adds up the two routes
 */
CRoute CRoute::operator +(const CRoute& cr)
{
	bool check = false;
	list<CWaypoint*>::iterator itr;
	if(this->m_pPoiDatabase == cr.m_pPoiDatabase){
		if(this->m_pWpDatabase == cr.m_pWpDatabase){
			check = true;
			this->m_route.insert(this->m_route.end(), cr.m_route.begin(), cr.m_route.end());
		}
		else{
			cout << "WPDatabase of both the object are not same"<<endl;
		}
	}
	else{
		cout << "PoiDatabase of both the object are not same"<<endl;
	}
	if(check == true){
		return(*this);
	}
	else{
		return(*this);
	}
}
/**
 * @param const CRoute& cr - object of route class[IN]
 * @return CRoute	- object of route class[OUT]
 * This operator assigns deep copy of the route from one object to other
 */
CRoute& CRoute::operator =(const CRoute& cr)
{
	this->m_route = cr.m_route; // '=' operator creates a deep copy for list as shown by the below print statements
	this->m_itrRoute = cr.m_itrRoute;
	this->m_pPoiDatabase = cr.m_pPoiDatabase;
	this->m_pWpDatabase = cr.m_pWpDatabase;
	return (*this);
}
/**
 * @param const CRoute& cr - object of route class[IN]
 * @return CRoute	- object of route class[OUT]
 * This operator adds Waypoint or poi at the end of the route
 */
CRoute& CRoute::operator +=(string name)
{
	if(m_pWpDatabase != NULL && m_pPoiDatabase != NULL){
		//bool checkWpDb = (this->m_pWpDatabase->getPointerToWaypoint(name) != NULL) ? true:false;
		bool checkWpDb = (this->m_pWpDatabase->getPointerToDbObj(name) != NULL) ? true:false;
		//bool checkPoiDb = (this->m_pPoiDatabase->getPointerToPoi(name) != NULL) ? true:false;
		bool checkPoiDb = (this->m_pPoiDatabase->getPointerToDbObj(name) != NULL) ? true:false;
		//cout << checkWpDb <<"\t"<<checkPoiDb<<"\t";
		if(checkWpDb && checkPoiDb){
			this->addWaypoint(name);
			this->addPoi(name,name);
		}
		else if(checkWpDb && !checkPoiDb){
			this->addWaypoint(name);
		}
		else if(checkPoiDb && !checkWpDb){
			this->m_route.push_back(m_pPoiDatabase->getPointerToDbObj(name));
		}
		else{
			cout << "The name "<< name <<" is neither present in PoiDatabase nor WpDatabase"<<endl;
		}
	}
	else{
		cout << "The Wp & Poi Database are not connected"<<endl;
	}
	return (*this);
}

const vector<const CWaypoint*> CRoute::getRoute()
{
	vector<const CWaypoint*> localVector;
	for(m_itrRoute = m_route.begin();m_itrRoute != m_route.end();m_itrRoute++){
		localVector.push_back((*m_itrRoute));
	}
	return localVector;
}

/*bool CRoute::operator ==(CRoute& cr)
{
	unsigned int checkCounter;
	bool checkEquality;
	list <CWaypoint*>::iterator itr1 = this->m_route.begin();
	list <CWaypoint*>::iterator itr2 = cr.m_route.begin();
	for(itr1,itr2;itr1 != this->m_route.end() && itr2 != cr.m_route.end();itr1++,itr2++){
		if(dynamic_cast<CPOI*>(*m_itrRoute) != NULL){
			if((*dynamic_cast<CPOI*>(*(itr1))) == (*dynamic_cast<CPOI*>(*(itr2)))){
				checkCounter++;
			}
		}
		else{
			if((**(itr1)) == (**(itr2))){
				checkCounter++;
			}

		}
	}
	if(checkCounter == cr.m_route.size()){
		checkEquality = true;
	}
	else{
		checkEquality = false;
	}
	return checkEquality;
}*/
