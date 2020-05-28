/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "Ccsv.h"
#include "CDatabase.h"
#include "CJsonPersistence.h"
class CNavigationSystem {
/*
 * member variables:-
 * m_GPSSensor	->	Object of GPSSensor
 * m_Route		->	Object of class CRoute
 * m_PoiDatabase	->	Object of the class CPoiDatabase
 * m_WpDatabase		-> Object of the class CWpDatabase
 * m_csv			-> Object of the class Ccsv
 */
private:
    CGPSSensor m_GPSSensor;
    CRoute m_Route;
    APT::CDatabase<CPOI> m_PoiDatabase;
    APT::CDatabase<CWaypoint> m_WpDatabase;
    Ccsv m_csv;
    CJsonPersistence m_Json;
public:

    CNavigationSystem();
    /**
     * This is the main function which will call other functions of the class since they are private
     * @param void
     * @returnvalue void
     * The main functionality of the code is to connect to PoiDatabase
     * Always remeber to write the method connectToPoiDatabase
     */
    void run();

private:
    /*
     * This is the function which allows the user to enter the Waypoints and POI's to it's route
     * @param void
     * @returnvalue void
     */
    void enterRoute();
    /**
     * This is the function which prints the entire Route
     * @param void
     * @returnvalue void
     */
    void printRoute();
    /*
     * This is the function which prints distance to nearest POI
     * @param void
     * @returnvalue void
     */
    void printDistanceCurPosNextPoi();
    /**
     * This is the function which helps to create databases
     * @param void
     * @returnvalue void
     */
    void createDatabases();
    /**
     * This function is used to write data from DB to a file
     * @param void
     * @returnvalue void
     */
    void writeToFile();
    /**
     * This function is used to read data from file and write it to a DB
     * @param void
     * @returnvalue void
     */
    void readFromFile();
};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
