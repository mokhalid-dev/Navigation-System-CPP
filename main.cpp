// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include <math.h>
#include "CWaypoint.h"
#include "CNavigationSystem.h"
#include "CGPSSensor.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CRoute.h"
#include "CWpDatabase.h"
#include "CPersistentStorage.h"
#include "Ccsv.h"
#include "CJsonPersistence.h"
#include "CDatabase.h"
//#define DEGREE 1
//#define MMSS 2
//#define CWaypointImpl
//#define OldCase
//#define TESTCASEPoiDB
//#define TESTCASEWpDB
//#define TESTCASERoute
//#define TestCasePersistance
//#define TestCasePersistanceJson
//#define TestCaseTemplateDb
// TODO: Fügen Sie hier weitere benötigte Header-Dateien der
// Standard-Bibliothek ein z.B.
// #include <string>

using namespace std;	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.
// #include "CFraction.h"


// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main (void)
{
#ifdef CWaypointImpl
	string name;
	double longitude;
	double latitude;
    // TODO: Fügen Sie ab hier Ihren Programmcode ein
	cout << "MadatoryExercise1 gestarted." << endl << endl;
	cout << "Constructor"<<endl<<"================"<<endl;
	CWaypoint berlin("Berlin",52.5166,13.4);
	CWaypoint darmstadt("Darmstadt",49.8728,8.6512);
	CWaypoint amsterdam("Amsterdam",52.3680,4.9036);
	CWaypoint tokio("Tokio",35.6895,139.6917);
	CWaypoint myWayPoint;
	cout << "Print"<<endl<<"================"<<endl;
	berlin.print(DEG);
	berlin.print(MMSS);
	cout << "Name as return Value : ";
	cout << berlin.getName()<<endl;
	cout << "Latitude as return Value : ";
	cout<<berlin.getLatitude()<<endl;
	cout << "Longitude as return Value : ";
	cout<<berlin.getLongitude()<<endl;
	berlin.getAllDataByReference(name,latitude,longitude);
	cout << name <<"\t"<< latitude << "\t"<<longitude<<endl;
	cout << "Name as return Value : ";
	cout << amsterdam.getName()<<endl;
	cout << "and a first real method "<<endl<<"================="<<endl;
	cout<<"Distance between "<<amsterdam.getName()<<" and "<<berlin.getName()<<" is : "<<ceil(berlin.calculateDistance(amsterdam))<<" approx"<<endl;
	cout<<"Distance between "<<amsterdam.getName()<<" and "<<tokio.getName()<<" is : "<<ceil(berlin.calculateDistance(tokio))<<" approx"<<endl;
	//cout<<berlin;
	//CPOI Mensa_HDA(RESTAURANT,"Mensa HDA","The best mensa in the world",10,20);
	//cout<<Mensa_HDA;
#endif

#ifdef TestCase
	CGPSSensor cg;
	myWayPoint = cg.getCurrentPosition();
	//CNavigationSystem cns;
	//cns.run();
	//CPOI cp;
	//cp.print();
	CPoiDatabase cpDB;
	cpDB.addPoi(RESTAURANT,"Mensa HDA","The best mensa in the world",10,20);
	cpDB.addPoi(RESTAURANT,"Sitte","More Expensive but also good",11,22);
	CPOI* cp = cpDB.getPointerToPoi("Mensa HDA");
	CPOI cp1;
	cout<<cp<<endl;
	cp->print();
	CRoute cr(3,2);
	cr.connectToPoiDatabase(&cpDB);
	cr.addWaypoint(berlin);
	cr.addWaypoint(amsterdam);
	cr.addWaypoint(darmstadt);
	cr.addPoi("Mensa HDA");
	cr.addPoi("Sit");
	cr.print();
	double dist = cr.getDistanceNextPoi(myWayPoint,cp1);
	cout << dist<<endl;
	cp1.print();
#endif
	//CNavigationSystem cns;
	//cns.run();
#ifdef TESTCASEPoiDB
	CPoiDatabase cpDB;
	CPOI Mensa_HDA(RESTAURANT,"Mensa HDA","The best mensa in the world",10,20);
	CPOI Sitte(RESTAURANT,"Sitte","More Expensive but also good",11,22);
	CPOI Mensa_HDA1(RESTAURANT,"Mensa HDA","The best mensa in the world",10,20);
	CPOI TU(UNIVERSITY,"TU Darmstadt","University of Science",49.8748,8.6563);
	CPOI HOCHZeitsturm(TOURISTIC,"Hochzeitsturm","The wedding Tower",49.8771,8.6673);
	CPOI ARAL(GASSTATION,"ARAL","The neares Gas Station",49.8723,8.6509);
	CPOI amste(TOURISTIC,"Amsterdam","Nearest city",52.3680,4.9036);
	cpDB.addPoi(Mensa_HDA);
	cpDB.addPoi(Sitte);
	cpDB.addPoi(Mensa_HDA1); //testcase for repetative addition
	cpDB.addPoi(TU);
	cpDB.addPoi(HOCHZeitsturm);
	cpDB.addPoi(ARAL);
	cpDB.addPoi(amste);
	cpDB.getPointerToPoi("Mensa HDA")->print();
	cpDB.getPointerToPoi("Sitte")->print();
	cpDB.getPointerToPoi("TU Darmstadt")->print();
	cpDB.getPointerToPoi("Hochzeitsturm")->print();
	cpDB.getPointerToPoi("ARAL")->print();
	//cpDB.getPointerToPoi("alpha")->print(); //It crashes the program since null is returned and print() is called
#endif

#ifdef TESTCASEWpDB
	CWpDatabase cwpDB;
	cwpDB.addWaypoint(berlin);
	cwpDB.addWaypoint(darmstadt);
	cwpDB.addWaypoint(amsterdam);
	cwpDB.addWaypoint(tokio);
	cwpDB.addWaypoint(berlin); //testcase for repetative addition
	cwpDB.getPointerToWaypoint("Berlin")->print(MMSS);
	cwpDB.getPointerToWaypoint("Darmstadt")->print(MMSS);
	cwpDB.getPointerToWaypoint("Amsterdam")->print(MMSS);
	cwpDB.getPointerToWaypoint("Tokio")->print(MMSS);
	//cwpDB.print();
#endif

#ifdef TESTCASERoute
	CRoute ct;
	ct.connectToPoiDatabase(&cpDB);
	ct.connectToWpDatabase(&cwpDB);
	ct.addWaypoint("Berlin");
	ct.addWaypoint("Darmstadt");
	ct.addWaypoint("Berlin");
	ct.addPoi("TU Darmstadt","Darmstadt");
	ct.addPoi("Mensa HDA","Darmstadt");
	CRoute ct1(ct);
	CRoute ct2;
	CRoute ct3;
	ct2 = ct;
	ct.print();
	cout << "================================Copy Of a list With copy Constructor==============================================="<<endl;
	ct1.print();
	cout << "================================Copy Of a list With assignment operator==============================================="<<endl;
	ct2.print();
	/*
	ct1 + ct3; // this gives a statement on Console as "PoiDatabase of both the object are not same"
	cout << "================================Check for + Operator==============================================="<<endl;
	ct1.print();
	ct1 + ct2;
	cout << "================================Check for + Operator==============================================="<<endl;
	ct1.print();*/
	ct1 += "Amsterdam";
	ct1 += "ARAL";
	ct1 += "alpha";
	cout << "================================Check for += Operator==============================================="<<endl;
	ct1.print();
#endif

#ifdef TestCasePersistance
	Ccsv alpha;
	alpha.setMediaName("C:/Users/swapnil/Desktop/");
	alpha.writeData(cwpDB,cpDB);
	alpha.readData(cwpDB,cpDB,CPersistentStorage::REPLACE);
	cwpDB.print();
	cpDB.print();
#endif

#ifdef TestCasePersistanceJson
	CJsonPersistence alpha;
	alpha.setMediaName("C:/Users/swapnil/Desktop/writeJson/");
	alpha.writeData(cwpDB,cpDB);
	alpha.setMediaName("C:/Users/swapnil/Desktop/readJson/");
	alpha.readData(cwpDB,cpDB,CPersistentStorage::REPLACE);
#endif

#ifdef TestCaseTemplateDb
	APT::CDatabase<CWaypoint> cwpDb;
	APT::CDatabase<CPOI> cpoiDb;
	cwpDb.add(berlin);
	cwpDb.add(berlin);
	cwpDb.getPointerToDbObj("Berlin")->print(MMSS);
	cpoiDb.add(Sitte);
	cpoiDb.add(Sitte);
	cpoiDb.getPointerToDbObj("Sitte")->print();
	cwpDb.print();
	cpoiDb.print();
	cwpDb.DbobjDelete();
	cpoiDb.DbobjDelete();
#endif
	CNavigationSystem ns;
	ns.run();
}
