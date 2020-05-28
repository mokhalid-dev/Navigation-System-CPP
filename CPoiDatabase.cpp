/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include<iostream>
#include<string.h>
using namespace std;
//Own Include Files
#include "CPoiDatabase.h"
#include "CPOI.h"
//preprocessor directive
//#define DEBUG
//Method Implementations
/*
 * Constructor of class CPoiDatabase
 * @param void
 * initializes member variables :-
 * m_POI[] to default values of constructor CPOI
 * m_noPoi to default values of zero
 */
CPoiDatabase::CPoiDatabase(){
	//m_itr = m_POI.begin();
}
/** This method adds POI to the Database
 * @param const CPOI& poi - poi object[IN]
 * @return void
 */
void CPoiDatabase::addPoi(const CPOI& poi){
	//CPOI POIObject(type,name,description,latitude,longitude);
	bool check = false;
	if(m_POI.find(poi.getName()) != m_POI.end()){
		check = true;
	}
	if(check == false){
		m_POI.insert(pair<string,CPOI>(poi.getName(),poi));
	}
	else{
		cout << "The value already exists and therefore can't allow to insert again for key value"
				<<" "<<poi.getName()<<endl;
	}
#ifdef DEBUG
	cout << "CPOI object created in the Database";
	cout << "\nThe map m_POI is : \n";
	cout << "\tKEY\tELEMENT\n";
	for(m_itr=m_POI.begin();m_itr != m_POI.end();m_itr++){
		cout << "\t" << m_itr->first
				<< "\t" << &(m_itr->second) << "\n";
	}
#endif
}
/*
 * This method is used to find the POI in the POI Database with the primary key as name
 * @param string name	- name value (IN)
 * @returnvalue CPOI* - pointer to found poi(OUT)
 */
CPOI* CPoiDatabase::getPointerToPoi(string name){
	map<string, CPOI>::iterator itr;
	if(m_POI.find(name) != m_POI.end()){
		itr = m_POI.find(name);
		return &(itr->second);
	}
	else{
		return NULL;
		cout << "The POI not present"<<endl;
	}
	/*for(m_itrPoi=m_POI.begin();m_itrPoi != m_POI.end();m_itrPoi++){
		if(m_itrPoi->first == name){
			return &(m_itrPoi->second);
		}
	}*/
	//cout << "The POI not present"<<endl;
	/*bool check1 = false;
	int arrLoc = 0;
	for(int arrCnt = 0;arrCnt<m_noPoi;arrCnt++){
		if(m_POI[arrCnt].getName() == name){
			arrLoc = arrCnt;
			check1 = true;
		}
	}
	if (check1 == true){
		return &m_POI[arrLoc];
#ifdef DEBUG
		cout << "Address of the POI found "<<m_POI[arrLoc];
#endif
	}
	else{
		cout << "Warning!! Value not found in the Database Therefore Returning the Null pointer";
		return NULL;
	}*/
}

/**
 * @param void
 * @returnvalue map<string, CPOI>
 * It returns the map containing data of the Database
 */
map<string, CPOI> CPoiDatabase::getMapOfPoi() const
{
	return m_POI;
}
/**
 * @param void
 * @returnvalue void
 * It deletes the data of PoiDatabase
 */
void CPoiDatabase::poiDelete()
{
	m_POI.clear();
}
/**
 * @param void
 * @returnvalue void
 * It prints the map of database
 */
void CPoiDatabase::print()
{
	cout << "\nThe map m_POI is : \n";
		cout << "\tKEY\tELEMENT\n";
		for(m_itrPoi=m_POI.begin();m_itrPoi != m_POI.end();m_itrPoi++){
			cout << "\t" << m_itrPoi->first<<"\t";
			m_itrPoi->second.print();
			cout<< endl;
		}
}
