/*
 * CJsonPersistence.h
 *
 *  Created on: Jan 9, 2019
 *      Author: swapnil
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_
#include <string>
#include <fstream>
#include "CPersistentStorage.h"
#include "CJsonToken.h"
class CJsonPersistence : public CPersistentStorage
{
private:
	/**
	 * directory name for json
	 */
	std::string m_directory;
	/**
	 * filesystem variable for json
	 */
	std::fstream m_FileSystem;
	/**
	 * enum of states
	 */
	enum states{
		IDLE,
		DB_BEGIN,
		WP_DB_BEGIN,
		POI_DB_BEGIN,
		WAITING_ARRAY_END,
		WAITING_OBJECT_END,
		WAITING_FOR_ATTRIBUTE,
	};
	states m_state;
	//Method which returns type of poi
	t_poi retPoiType(string typo);
	//Method which returns type of token in form of string
	string retTokenType(APT::CJsonToken::TokenType type);
public:
	void setMediaName(std::string name);
	bool writeData (const APT::CDatabase<CWaypoint>& waypointDb,const APT::CDatabase<CPOI>& poiDb);
	bool readData (APT::CDatabase<CWaypoint>& waypointDb, APT::CDatabase<CPOI>& poiDb,MergeMode mode);
};

#endif /* CJSONPERSISTENCE_H_ */
