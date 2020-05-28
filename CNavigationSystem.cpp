/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>
using namespace std;
//Own Include Files
#include "CNavigationSystem.h"
//Method Implementations
/*
 * Constructor of class CNavigationSystem
 * @param void
 */
CNavigationSystem::CNavigationSystem(){

}
/**
 * This is the main function which will call other functions of the class since they are private
 * @param void
 * @returnvalue void
 * The main functionality of the code is to connect to PoiDatabase
 * Always remeber to write the method connectToPoiDatabase
 */
void CNavigationSystem::run(){
	m_Route.connectToPoiDatabase(&m_PoiDatabase);
	m_Route.connectToWpDatabase(&m_WpDatabase);
	createDatabases();
	enterRoute();
	printRoute();
	writeToFile();
}
/*
 * This is the function which allows the user to enter the Waypoints and POI's to it's route
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::enterRoute(){
	m_Route.addWaypoint("Darmstadt");
	m_Route.addWaypoint("Berlin");
	m_Route.addWaypoint("Dresden");
	m_Route.addWaypoint("Bamberg");
	m_Route.addWaypoint("Darmstadt");
	m_Route.addWaypoint("Amsterdam");
	m_Route.addPoi("Mensa HDA","Darmstadt");
	m_Route.addPoi("ARAL","Darmstadt");
	m_Route.addPoi("A Mano","Berlin");
	m_Route.addPoi("Berlin Wall","Berlin");
	m_Route.addPoi("Elements Deli","Dresden");
	m_Route.addPoi("Zwinger Palace","Dresden");
	m_Route.addPoi("Ichi san","Bamberg");
	m_Route.addPoi("University Bamberg","Bamberg");
	m_Route.addPoi("Anne Frank Museum","Amsterdam");
	m_Route.addPoi("In de Waag","Amsterdam");
}
/*
 * This is the function which prints the entire Route
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::printRoute(){
	m_Route.print();
}
/*
 * This is the function which prints distance to nearest POI
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::printDistanceCurPosNextPoi(){
	CWaypoint GPSPoint = m_GPSSensor.getCurrentPosition();
	CPOI poi;
	//double distance = m_route.getDistanceNextPoi(GPSPoint,poi);
	//cout << "Distance to next POI "<<distance<<endl;
	poi.print();
}
/**
 * This is the function which helps to create databases
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::createDatabases()
{
	m_WpDatabase.add(CWaypoint("Berlin",52.5166,13.4));
	m_WpDatabase.add(CWaypoint("Darmstadt",49.8728,8.6512));
	m_WpDatabase.add(CWaypoint("Amsterdam",52.3680,4.9036));
	m_WpDatabase.add(CWaypoint("Dresden",51.0504,13.7373));
	m_WpDatabase.add(CWaypoint("Bamberg",49.8988,10.9028));
	m_WpDatabase.add(CWaypoint("Tokio",35.6895,139.6917));
	m_PoiDatabase.add(CPOI(RESTAURANT,"Mensa HDA","The best mensa in the world",10,20)); //Darmstadt
	m_PoiDatabase.add(CPOI(GASSTATION,"ARAL","The nearest Gas Station",49.8723,8.6509)); //Darmstadt
	m_PoiDatabase.add(CPOI(RESTAURANT,"A Mano","Best rated cafe in berlin",52.5194,13.4274));//Berlin
	m_PoiDatabase.add(CPOI(TOURISTIC,"Berlin Wall","It has a great history",52.5097,13.3728));//Berlin
	m_PoiDatabase.add(CPOI(RESTAURANT,"Elements Deli","Fine Dining Restaurant",51.1014,13.9393));//Dresden
	m_PoiDatabase.add(CPOI(TOURISTIC,"Zwinger Palace","A palace in Dresden",51.0530,13.7339));//Dresden
	m_PoiDatabase.add(CPOI(RESTAURANT,"Ichi san","Sushi restaurant in bamberg",49.9031,11.0332));//Bamberg
	m_PoiDatabase.add(CPOI(UNIVERSITY,"University Bamberg","University of Science",49.92,10.7829));//Bamberg
	m_PoiDatabase.add(CPOI(TOURISTIC,"Anne Frank Museum","Museum of art",52.3752,4.8840));//Amsterdam
	m_PoiDatabase.add(CPOI(RESTAURANT,"In de Waag","Best Restaurant in Amsterdam",52.3728,4.9003));//Amsterdam
	readFromFile();
}
/**
 * This function is used to write data from DB to a file
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::writeToFile()
{
	m_csv.setMediaName("F:/Masters_EIT_HDA/SEM1/APT/APT-L/workspacetest/Submission-Lab-2.zip_expanded/MandatoryExercise2/writeDirectory/");
	if(m_csv.writeData(m_WpDatabase,m_PoiDatabase)){
		cout << "Writting to the write directory successful"<<endl;
	}
	m_Json.setMediaName("F:/Masters_EIT_HDA/SEM1/APT/APT-L/workspacetest/Submission-Lab-2.zip_expanded/MandatoryExercise2/writeDirectory/");
	m_Json.writeData(m_WpDatabase,m_PoiDatabase);
}
/**
 * This function is used to read data from file and write it to a DB
 * @param void
 * @returnvalue void
 */
void CNavigationSystem::readFromFile()
{
	m_csv.setMediaName("F:/Masters_EIT_HDA/SEM1/APT/APT-L/workspacetest/Submission-Lab-2.zip_expanded/MandatoryExercise2/readDirectory/");
	if(m_csv.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::REPLACE)){
		cout << "Reading from the read directory successful"<<endl;
	}
	m_Json.setMediaName("F:/Masters_EIT_HDA/SEM1/APT/APT-L/workspacetest/Submission-Lab-2.zip_expanded/MandatoryExercise2/readDirectory/");
	m_Json.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::MERGE);
}
