/*
 * CJsonPersistence.cpp
 *
 *  Created on: Jan 9, 2019
 *      Author: swapnil
 */

#include "CJsonPersistence.h"
#include <iostream>
#include "CJsonScanner.h"
void CJsonPersistence::setMediaName(std::string name)
{
	m_directory = name;
}

bool CJsonPersistence::writeData(const APT::CDatabase<CWaypoint>& waypointDb,
		const APT::CDatabase<CPOI>& poiDb)
{
	bool checkWp,checkPoi = false;
		map<string,CPOI> CPoi_Map = poiDb.getMapOfDbObj();
		map<string,CWaypoint> CWp_Map = waypointDb.getMapOfDbObj();
		string name;
		double longitude;
		double latitude;
		string description;
		t_poi type;
		map<string,CWaypoint>::iterator itrWp;
		map<string,CPOI>::iterator itrPoi;
		m_FileSystem.open((m_directory + "beta.json").c_str(),fstream::in|fstream::out|fstream::app);
		if ( ! m_FileSystem.is_open()) {
			cout <<" Failed to open Waypoint file" << endl;
		}
		else {
			checkWp = true;
			cout <<"Opened Waypoint file OK" << endl;
			m_FileSystem << "{"<<endl<<'\t'<<"\"waypoints\": ["<<endl;
			for(itrWp = CWp_Map.begin();itrWp != CWp_Map.end();){
				itrWp->second.getAllDataByReference(name,latitude,longitude);
				m_FileSystem << '\t'<< '\t'<<"{"<<endl;
				m_FileSystem << '\t'<< '\t'<<'\t'<<"\"name\":"<<"\""<<name <<"\""<< "," <<endl
						<<'\t'<< '\t'<<'\t'<<"\"latitude\":"<<latitude<<","<<endl
						<<'\t'<< '\t'<<'\t'<<"\"longitude\":"<<longitude<<endl;
				if(++itrWp == CWp_Map.end()){
					m_FileSystem << '\t'<< '\t'<<"}"<<endl;
				}
				else{
					m_FileSystem << '\t'<< '\t'<<"},"<<endl;
				}
	#ifdef DEBUG
		cout << name<<"\t"<<latitude<<"\t"<<longitude<<endl;
	#endif
			}
			m_FileSystem << "\t" << "],"<<endl;
			m_FileSystem.close();
		}
		m_FileSystem.open((m_directory+"beta.json").c_str(),fstream::in|fstream::out|fstream::app);
			if ( ! m_FileSystem.is_open()) {
				cout <<" Failed to open POI file" << endl;
			}
			else {
				cout <<"Opened POI file OK" << endl;
				checkPoi = true;
				m_FileSystem <<'\t'<<"\"pois\": ["<<endl;
				for(itrPoi = CPoi_Map.begin();itrPoi != CPoi_Map.end();){
					itrPoi->second.getAllDataByReference(name,latitude,longitude,type,description);
					m_FileSystem << '\t'<< '\t'<<"{"<<endl;
					switch(type){
					case RESTAURANT:
						m_FileSystem << '\t'<<'\t'<<'\t'<<"\"type\":"<<"\"RESTAURANT\""<< ","<<endl;
						break;
					case TOURISTIC:
						m_FileSystem << '\t'<<'\t'<<'\t'<<"\"type\":"<< "\"TOURISTIC\""<< ","<<endl;
						break;
					case GASSTATION:
						m_FileSystem << '\t'<<'\t'<<'\t'<<"\"type\":"<< "\"GASSTATION\""<< ","<<endl;
						break;
					case UNIVERSITY:
						m_FileSystem << '\t'<<'\t'<<'\t'<<"\"type\":"<< "\"UNIVERSITY\""<< ","<<endl;
						break;
					}
					m_FileSystem << '\t'<<'\t'<<'\t'<<"\"name\":"<<"\""<<name <<"\""<<","<<endl
							<< '\t'<<'\t'<<'\t'<<"\"description\":"<<"\""<<description<<"\""<<","<<endl
							<< '\t'<<'\t'<<'\t'<<"\"latitude\":"<<latitude<<","<<endl
							<< '\t'<<'\t'<<'\t'<<"\"longitude\":"<<longitude<<endl;
		#ifdef DEBUG
			cout << type<<"\t"<<name<<"\t"<<description<<"\t"<<latitude<<"\t"<<longitude<<endl;
		#endif
					if(++itrPoi == CPoi_Map.end()){
						m_FileSystem << '\t'<< '\t'<<"}"<<endl;
					}
					else{
						m_FileSystem << '\t'<< '\t'<<"},"<<endl;
					}
				}
				m_FileSystem << "\t" << "]"<<endl;
				m_FileSystem << "}";
				m_FileSystem.close();
			}
	return checkWp && checkPoi;
}

bool CJsonPersistence::readData(APT::CDatabase<CWaypoint>& waypointDb, APT::CDatabase<CPOI>& poiDb,
		MergeMode mode)
{
	bool checkOpen = false;
	string attribute; // value of attribute belongs to {"name","type","description","latitude","longitude"}
	string name; // stores value of name for each WP or POI object
	string type;
	string description;
	double latitude;
	double longitude;
	t_poi type1;
	if(mode == REPLACE){
			waypointDb.DbobjDelete();
			poiDb.DbobjDelete();
	}
	m_FileSystem.open((m_directory + "beta.json").c_str(),fstream::in|fstream::out|fstream::app);
		if ( ! m_FileSystem.is_open()) {
			cout <<" Failed to open Waypoint file" << endl;
		}
		else{
			checkOpen = true;
			cout << "Opened File OK" << endl;
			APT::CJsonScanner jsonScanner(m_FileSystem);
			APT::CJsonToken* scannerToken;
			int faultLine;
			int faultCounter;
			int objectCounter;
			int valSepCounter;
			m_state = IDLE;
			while(1){
				scannerToken = jsonScanner.nextToken();
				string dBName; // value of dbName belongs to {"waypoints","pois"}
				bool checkDb; // true for waypoints and false for pois
				/*
				 * This if statement below does two things :-
				 * 1) detects end of file
				 * 2) detects wrong tokens i.e. tokens apart from JSON grammar
				 * 		and in either case terminates the programme
				 * */
				if(scannerToken == 0){
					break;
				}
				switch(m_state){
				case IDLE:
					if(scannerToken->getType() == scannerToken->BEGIN_OBJECT){
						m_state = DB_BEGIN;
					}
					if(scannerToken->getType() != scannerToken->BEGIN_OBJECT){
						m_state = IDLE;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
								<<"\" in line : "<<jsonScanner.scannedLine()
								<<" Starting token for a JSON file should be { "<<endl;
					}
					break;
				case DB_BEGIN:
					if(scannerToken->getType() == scannerToken->STRING){
						dBName = dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue();
						if(dBName == "waypoints"){
							m_state = WP_DB_BEGIN;
							checkDb = true;
						}
						else if(dBName == "pois"){
							m_state = POI_DB_BEGIN;
							checkDb = false;
						}
						else{
							m_state = DB_BEGIN;
							cout << "Attribute Of the token \""<<dBName<<" \"doesn't match any of the given DB names at line "
									<<jsonScanner.scannedLine()<<endl;
						}
					}
					if(scannerToken->getType() != scannerToken->STRING){
						m_state = DB_BEGIN;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
								<<"\" in line : "<<jsonScanner.scannedLine()
								<<" Only String type token are allowed here "<<endl;
					}
					break;
				case WP_DB_BEGIN:
					//cout << " I'm in WP_BEGIN state "<<endl;
					if(scannerToken->getType() == scannerToken->NAME_SEPARATOR){
						m_state = WP_DB_BEGIN;
					}
					if(scannerToken->getType() == scannerToken->BEGIN_ARRAY){
						m_state = WAITING_ARRAY_END;
					}
					if(scannerToken->getType() == scannerToken->VALUE_SEPARATOR){
						m_state = DB_BEGIN;
					}
					if(scannerToken->getType() == scannerToken->END_OBJECT){
						m_state = IDLE;
					}
					if(scannerToken->getType() != scannerToken->NAME_SEPARATOR &&
							scannerToken->getType() != scannerToken->BEGIN_ARRAY &&
							scannerToken->getType() != scannerToken->VALUE_SEPARATOR &&
							scannerToken->getType() != scannerToken->END_OBJECT){
						m_state = WP_DB_BEGIN;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
									<<"\" in line : "<<jsonScanner.scannedLine()
									<<" This type not allowed here "<<endl;
					}
					break;
				case POI_DB_BEGIN:
					if(scannerToken->getType() == scannerToken->NAME_SEPARATOR){
						m_state = POI_DB_BEGIN;
					}
					if(scannerToken->getType() == scannerToken->BEGIN_ARRAY){
						m_state = WAITING_ARRAY_END;
					}
					if(scannerToken->getType() == scannerToken->VALUE_SEPARATOR){
						m_state = DB_BEGIN;
					}
					if(scannerToken->getType() == scannerToken->END_OBJECT){
						m_state = IDLE;
					}
					if(scannerToken->getType() != scannerToken->NAME_SEPARATOR &&
						scannerToken->getType() != scannerToken->BEGIN_ARRAY &&
						scannerToken->getType() != scannerToken->VALUE_SEPARATOR &&
						scannerToken->getType() != scannerToken->END_OBJECT){
						m_state = POI_DB_BEGIN;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
									<<"\" in line : "<<jsonScanner.scannedLine()
									<<" This type not allowed here "<<endl;
					}
					break;
				case WAITING_ARRAY_END:
					if(scannerToken->getType() == scannerToken->BEGIN_OBJECT){
						faultCounter = 0;
						objectCounter = 0;
						valSepCounter = 0;
						m_state = WAITING_OBJECT_END;
					}
					if(scannerToken->getType() == scannerToken->VALUE_SEPARATOR){
						m_state = WAITING_ARRAY_END;
						if(checkDb == true){
							if(name!=""&&faultCounter == 0 && objectCounter == 3 && valSepCounter == 2){
								cout<<name<<"\t"<<latitude<<"\t"<<longitude<<endl;
								waypointDb.add(CWaypoint(name,latitude,longitude));
							}
							else{
								if(faultLine != 0){
									cout<<"Spelling of one of the keywords is wrong "
										<< " at line : " << faultLine
										<<" ALL Attribute Of An Object Not Found Error"<<endl;
								}
								else{
									cout << "Object Not Found Error at line : "
											<< jsonScanner.scannedLine()<<endl;
								}
							}
						}
						else{
							if(type != "" && faultCounter == 0 && objectCounter == 5){
								cout<<type<<"\t"<<name<<"\t"<<description<<"\t"
									<<latitude<<"\t"<<longitude<<endl;
								type1 = retPoiType(type);
								poiDb.add(CPOI(type1,name,description,latitude,longitude));}
							else{
								if(faultLine != 0){
									cout<<"Spelling of one of the keywords is wrong "
										<< " at line : " << faultLine
										<<" ALL Attribute Of An Object Not Found Error"<<endl;
								}
								else{
									cout << "Object Not Found Error at line : "
											<< jsonScanner.scannedLine()<<endl;
								}
							}
						}
					}
					if(scannerToken->getType() == scannerToken->END_ARRAY){
						if(checkDb == true){
							m_state = WP_DB_BEGIN;
							if(name != "" && faultCounter == 0 && objectCounter == 3){
								cout<<name<<"\t"<<latitude<<"\t"<<longitude<<endl;
								waypointDb.add(CWaypoint(name,latitude,longitude));}
							else{
								cout<<"No object found in the array of object\""
										<<"\" in line : "<<jsonScanner.scannedLine()
										<<" Array IS Empty Or spelling of attribute is wrong"<<endl;
							}
						}
						else{
							m_state = POI_DB_BEGIN;
							if(type != "" && faultCounter == 0 && objectCounter == 5){
								cout<<type<<"\t"<<name<<"\t"<<description<<"\t"
									<<latitude<<"\t"<<longitude<<endl;
								type1 = retPoiType(type);
								poiDb.add(CPOI(type1,name,description,latitude,longitude));}
							else{
								cout<<"No object found in the array of object\""
									<<"\" in line : "<<jsonScanner.scannedLine()
									<<" Array IS Empty Or spelling of attribute is wrong"<<endl;
							}
						}
					}

					if(scannerToken->getType() != scannerToken->BEGIN_OBJECT
							&& scannerToken->getType() != scannerToken->VALUE_SEPARATOR
							&& scannerToken->getType() != scannerToken->END_ARRAY){
						m_state = WAITING_ARRAY_END;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
								<<"\" in line : "<<jsonScanner.scannedLine()
								<<" This type not allowed here "<<endl;
					}
					break;
				case WAITING_OBJECT_END:
					if(scannerToken->getType() == scannerToken->STRING){
						attribute = dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue();
						m_state = WAITING_FOR_ATTRIBUTE;
					}
					if(scannerToken->getType() == scannerToken->VALUE_SEPARATOR){
						m_state = WAITING_OBJECT_END;
					}
					if(scannerToken->getType() != scannerToken->VALUE_SEPARATOR
							&& scannerToken->getType() != scannerToken->STRING){
						m_state = WAITING_OBJECT_END;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
								<<"\" in line : "<<jsonScanner.scannedLine()
								<<" This type not allowed here "<<endl;
					}
					break;
				case WAITING_FOR_ATTRIBUTE:
					//cout << objectCounter<<endl;
					if(attribute == "name"){
						if(scannerToken->getType() == scannerToken->STRING){
							name = dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue();
							//cout << name<<endl;
							//cout<<scannerToken->str()<<endl;
							m_state = WAITING_FOR_ATTRIBUTE;
							objectCounter++;
							//cout << objectCounter<<endl;
						}
						//m_state = WAITING_ATTRIBUTE_NAME;
					}
					else if(attribute == "latitude"){
						if(scannerToken->getType() == scannerToken->NUMBER){
							latitude = dynamic_cast<APT::CJsonNumberToken*>(scannerToken)->getValue();
							//cout << name<<endl;
							//cout<<scannerToken->str()<<endl;
							m_state = WAITING_FOR_ATTRIBUTE;
							objectCounter++;
							//cout << objectCounter<<endl;
						}
						//m_state = WAITING_ATTRIBUTE_LATITUDE;
					}
					else if(attribute == "longitude"){
						if(scannerToken->getType() == scannerToken->NUMBER){
							longitude = dynamic_cast<APT::CJsonNumberToken*>(scannerToken)->getValue();
							//cout << name<<endl;
							//cout<<scannerToken->str()<<endl;
							m_state = WAITING_FOR_ATTRIBUTE;
							objectCounter++;
							//cout << objectCounter<<endl;
						}

						//m_state = WAITING_ATTRIBUTE_LONGITUDE;
					}
					else if(attribute == "type"){
						if(scannerToken->getType() == scannerToken->STRING){
							type = dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue();
							//cout << name<<endl;
							//cout<<scannerToken->str()<<endl;
							m_state = WAITING_FOR_ATTRIBUTE;
							objectCounter++;
							//cout << objectCounter<<endl;
						}
						//m_state = WAITING_ATTRIBUTE_TYPE;
					}
					else if(attribute == "description"){
						if(scannerToken->getType() == scannerToken->STRING){
							description = dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue();
							//cout << name<<endl;
							//cout<<scannerToken->str()<<endl;
							m_state = WAITING_FOR_ATTRIBUTE;
							objectCounter++;
							//cout << objectCounter<<endl;
						}
						//m_state = WAITING_ATTRIBUTE_DESCRIPTION;
					}
					else{
						m_state = WAITING_FOR_ATTRIBUTE;
						//name = "CODERED";
						//cout<<"Error in Line : "<<jsonScanner.scannedLine()<<endl;
						faultCounter++;
						faultLine = jsonScanner.scannedLine();
					}
					if(scannerToken->getType() == scannerToken->NAME_SEPARATOR){
						m_state = WAITING_FOR_ATTRIBUTE;
					}
					if(scannerToken->getType() == scannerToken->VALUE_SEPARATOR){
						m_state = WAITING_OBJECT_END;
						valSepCounter++;
					}
					if(scannerToken->getType() == scannerToken->END_OBJECT){
						m_state = WAITING_ARRAY_END;
					}
					if(scannerToken->getType() != scannerToken->VALUE_SEPARATOR
							&& scannerToken->getType() != scannerToken->STRING
							&& scannerToken->getType() != scannerToken->NUMBER
							&& scannerToken->getType() != scannerToken->NAME_SEPARATOR
							&& scannerToken->getType() != scannerToken->END_OBJECT){
						m_state = WAITING_FOR_ATTRIBUTE;
						cout<<"Not a valid token \""<<retTokenType(scannerToken->getType())
							<<"\" in line : "<<jsonScanner.scannedLine()
							<<" This type not allowed here "<<endl;
					}
					break;
				}
			}
			/*while(1){
				scannerToken = jsonScanner.nextToken();
				if(scannerToken == 0){
					break;
				}
				if(scannerToken->getType() == scannerToken->STRING){
					cout<<dynamic_cast<APT::CJsonStringToken*>(scannerToken)->getValue()<<endl;
				}
			}*/
		}
	return checkOpen;
}

t_poi CJsonPersistence::retPoiType(string typo)
{
	if(typo == "RESTAURANT"){
		return RESTAURANT;
	}
	else if(typo == "GASSTATION"){
		return GASSTATION;
	}
	else if(typo == "TOURISTIC"){
		return TOURISTIC;
	}
	else{
		return UNIVERSITY;
	}

}

string CJsonPersistence::retTokenType(APT::CJsonToken::TokenType type)
{
	switch(type){
	case APT::CJsonToken::BEGIN_OBJECT:
		return "{";
		break;
	case APT::CJsonToken::END_OBJECT:
		return "}";
		break;
	case APT::CJsonToken::BEGIN_ARRAY:
		return "[";
		break;
	case APT::CJsonToken::END_ARRAY:
		return "]";
		break;
	case APT::CJsonToken::NAME_SEPARATOR:
		return ":";
		break;
	case APT::CJsonToken::VALUE_SEPARATOR:
		return ",";
		break;
	case APT::CJsonToken::STRING:
		return "String";
		break;
	case APT::CJsonToken::NUMBER:
		return "Number";
		break;
	case APT::CJsonToken::BOOL:
		return "[";
		break;
	default:
		return "NULL";
		break;
	}
}

