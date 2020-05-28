/*
 * Ccsv.h
 *
 *  Created on: Dec 3, 2018
 *      Author: swapnil
 */

#ifndef CCSV_H_
#define CCSV_H_
#include <fstream>
#include <vector>
#include "CPersistentStorage.h"
class Ccsv :public CPersistentStorage
{
private:
	std::string m_directory;
	std::fstream m_WpFileSystem;
	std::fstream m_PoiFileSystem;
public:
	void setMediaName(std::string name);
	bool writeData (const APT::CDatabase<CWaypoint>& waypointDb,const APT::CDatabase<CPOI>& poiDb);
	bool readData (APT::CDatabase<CWaypoint>& waypointDb, APT::CDatabase<CPOI>& poiDb,MergeMode mode);
private:
	bool checkName(string name);
	bool checkDigit(string name);
	bool retParseStringWp(string line,string& name,double& latitude,double& longitude);
	bool retParseStringPoi(string line,string& type1,string& name,string &description,
			double& latitude,double& longitude);
};

#endif /* CCSV_H_ */
