 /***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H
#include "CPoiDatabase.h"
#include "CPOI.h"
#include "CWpDatabase.h"
#include <list>
#include <vector>
#include <iterator>
#include "CDatabase.h"
class CWaypoint;

class CRoute {
private:
	/*
	 * m_pPoiDatabase-> pointer to CPoiDatabase object
	 * m_pWpDatabase-> pointer to CWpDatabase object
	 */
    /*CWaypoint* m_pWaypoint;
    unsigned int m_maxWp;
    unsigned int m_nextWp;
    CPOI ** m_pPoi;
    unsigned int m_maxPoi;
    unsigned int m_nextPoi;*/
	list <CWaypoint*> m_route; //This could point to both CWaypoint and CPOI object since CPOI is a derived class of CWaypoint
    list <CWaypoint*>::iterator m_itrRoute;
	//CPoiDatabase* m_pPoiDatabase;
	APT::CDatabase<CPOI>* m_pPoiDatabase;
	APT::CDatabase<CWaypoint>* m_pWpDatabase;
    //CWpDatabase* m_pWpDatabase;
public:
    /*
     * Constructor of class CRoute
     * @param void
     */
    CRoute();
    /*
     * Copy Constructor which generates deep copy of an object CRoute
     * @param const CRoute& origin	-> The value of object which needs to be copied(IN)
     * */
    CRoute(const CRoute& origin);

    ~CRoute();
    /*
     * This function allows the CRoute class to connect with the POI Database we are working on
     * @param CPoiDatabase* pPoiDB	-> input variable for connecting to existing POI Database (IN)
     * @returnvalue void
     */
    bool connectToPoiDatabase(APT::CDatabase<CPOI>* pPoiDB);
    /**
     * This function allows the CRoute class to connect with the Wp Database we are working on
     * @param CWpDatabase* pWpDB	-> input variable for connecting to existing WP Database (IN)
     * @returnvalue void
     */
    bool connectToWpDatabase(APT::CDatabase<CWaypoint>* pWpDB);
    /*
     * This function allows us to add Waypoint to the route
     * @param string name -> It finds the pointer to waypoint from Waypoint database(IN)
     * @returnvalue void
     */
    void addWaypoint(string name);
    /*
     * This function allows us to add POI to the route
     * @param string namePoi -> The namePoi which helps to find the pointer to CPOI from Database(IN)
     * @param string afterWp -> The afterWp after which the Poi needs to be added (IN)
     * @returnvalue void
     */
    void addPoi(string namePoi,string afterWp);
    /**
     *	This function returns the vector of the route which contains
     *	all the waypoints and Poi as they occured in the route
     *	@param void
     *	@returntype const vector<const CWaypoint*>
     */
    const vector<const CWaypoint*> getRoute();
    APT::CDatabase<CPOI>* getPoiDb(){
    	return m_pPoiDatabase;
    }
    APT::CDatabase<CWaypoint>* getWpDb(){
    	return m_pWpDatabase;
    }
    //double getDistanceNextPoi(CWaypoint& wp, CPOI& poi);
    /*
     * This function prints the No. of Waypoints and POI's in the route
     * @param void
     * @returnvalue void
     */
    void print();
    /**
     * @param const CRoute& cr - object of route class[IN]
     * @return CRoute	- object of route class[OUT]
     * This operator adds up the two routes
     */
    CRoute operator+ (const CRoute& cr);
    /**
     * @param const CRoute& cr - object of route class[IN]
     * @return CRoute	- object of route class[OUT]
     * This operator assigns deep copy of the route from one object to other
     */
    CRoute& operator = (const CRoute& cr);
    /**
     * @param const CRoute& cr - object of route class[IN]
     * @return CRoute	- object of route class[OUT]
     * This operator adds Waypoint or poi at the end of the route
     */
    CRoute& operator+= (string name);
    bool operator==(CRoute& cr);
};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
