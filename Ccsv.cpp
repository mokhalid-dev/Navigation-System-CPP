/*
 * Ccsv.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: swapnil
 */

#include "Ccsv.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
	/**
	* Set the name of the media to be used for persistent storage.
	* The exact interpretation of the name depends on the implementation
	* of the component.
	*
	* @param name the media to be used
	*/
void Ccsv::setMediaName(std::string name)
{
	m_directory = name;
}
	/**
	* Write the data to the persistent storage.
	*
	* @param waypointDb the data base with way points
	* @param poiDb the database with points of interest
	* @return true if the data could be saved successfully
	*/
bool Ccsv::writeData(const APT::CDatabase<CWaypoint>& waypointDb, const APT::CDatabase<CPOI>& poiDb)
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
	m_WpFileSystem.open((m_directory + "wp.txt").c_str(),fstream::in|fstream::out);
	if ( ! m_WpFileSystem.is_open()) {
		cout <<" Failed to open Waypoint file" << endl;
	}
	else {
		checkWp = true;
		cout <<"Opened Waypoint file OK" << endl;
		for(itrWp = CWp_Map.begin();itrWp != CWp_Map.end();itrWp++){
			itrWp->second.getAllDataByReference(name,latitude,longitude);
			m_WpFileSystem << name << "," <<latitude<<","<<longitude<<endl;
#ifdef DEBUG
	cout << name<<"\t"<<latitude<<"\t"<<longitude<<endl;
#endif
		}
		m_WpFileSystem.close();
	}

	m_PoiFileSystem.open((m_directory+"poi.txt").c_str(),fstream::in|fstream::out);
	if ( ! m_PoiFileSystem.is_open()) {
		cout <<" Failed to open POI file" << endl;
	}
	else {
		cout <<"Opened POI file OK" << endl;
		checkPoi = true;
		for(itrPoi = CPoi_Map.begin();itrPoi != CPoi_Map.end();itrPoi++){
			itrPoi->second.getAllDataByReference(name,latitude,longitude,type,description);
			switch(type){
			case RESTAURANT:
				m_PoiFileSystem << "RESTAURANT" << ","<<name <<","<<description<<","<<latitude<<","<<longitude<<endl;
				break;
			case TOURISTIC:
				m_PoiFileSystem << "TOURISTIC" << ","<<name <<","<<description<<","<<latitude<<","<<longitude<<endl;
				break;
			case GASSTATION:
				m_PoiFileSystem << "GASSTATION" << ","<<name <<","<<description<<","<<latitude<<","<<longitude<<endl;
				break;
			case UNIVERSITY:
				m_PoiFileSystem << "UNIVERSITY" << ","<<name <<","<<description<<","<<latitude<<","<<longitude<<endl;
				break;
			}
#ifdef DEBUG
	cout << type<<"\t"<<name<<"\t"<<description<<"\t"<<latitude<<"\t"<<longitude<<endl;
#endif
		}
		m_PoiFileSystem.close();
	}
	return checkWp && checkPoi;
}
	/**
	* Fill the databases with the data from persistent storage. If
	* merge mode is MERGE, the content in the persistent storage
	* will be merged with any content already existing in the data
	* bases. If merge mode is REPLACE, already existing content
	* will be removed before inserting the content from the persistent
	* storage.
	*
	* @param waypointDb the the data base with way points
	* @param poiDb the database with points of interest
	* @param mode the merge mode
	* @return true if the data could be read successfully
	*/
bool Ccsv::readData(APT::CDatabase<CWaypoint>& waypointDb, APT::CDatabase<CPOI>& poiDb,MergeMode mode)
{
	bool checkWpOpen = false;
	bool checkPoiOpen = false;
	bool checkWp;
	bool checkPoi;
	string line;
	string name;
	string latitude1;
	string longitude1;
	string type1;
	double latitude;
	double longitude;
	t_poi type;
	string description;
	if(mode == REPLACE){
		waypointDb.DbobjDelete();
		poiDb.DbobjDelete();
	}
	m_WpFileSystem.open((m_directory + "wp.txt").c_str(),fstream::in|fstream::out|fstream::app);
	if ( ! m_WpFileSystem.is_open()) {
		cout <<" Failed to open Waypoint file" << endl;
	}
	else {
		cout <<"Opened Waypoint file OK" << endl;
		checkWpOpen = true;
		int lineCounter = 1;
		//while(getline(m_WpFileSystem,name,',') && getline(m_WpFileSystem,latitude1,',') &&
		//		getline(m_WpFileSystem,longitude1)){
		while(getline(m_WpFileSystem,line)){
			//latitude = atof(latitude1.c_str());
			//longitude = atof(longitude1.c_str());
			//cout << name<<endl;
			//CWaypoint(name,latitude,longitude).print(MMSS);
			checkWp = retParseStringWp(line,name,latitude,longitude);
			if(!checkWp && checkName(name)){
				switch(mode){
					case MERGE:
						waypointDb.add(CWaypoint(name,latitude,longitude));
						break;
					case REPLACE:
						waypointDb.add(CWaypoint(name,latitude,longitude));
						break;
				}
			}
			else{
				cout << "Problem in line : "<<lineCounter<<" :\t"<<name
						<<"\t"<<latitude<<"\t"<<longitude<<endl;
			}
			//name=longitude1=latitude1 ="";
			lineCounter++;
			//name=latitude1=longitude1="";
		}
		m_WpFileSystem.close();
	}

	m_PoiFileSystem.open((m_directory+"poi.txt").c_str(),fstream::in|fstream::out|fstream::app);
	if ( ! m_PoiFileSystem.is_open()) {
		cout <<" Failed to open POI file" << endl;
	}
	else {
		cout <<"Opened POI file OK" << endl;
		checkPoiOpen = true;
		int lineCounter = 1;
		/*while(getline(m_PoiFileSystem,type1,',') && getline(m_PoiFileSystem,name,',') &&
				getline(m_PoiFileSystem,description,',') && getline(m_PoiFileSystem,latitude1,',') &&
				getline(m_PoiFileSystem,longitude1)){*/
		while(getline(m_PoiFileSystem,line)){
			//getline(m_PoiFileSystem,type1,',');
			//getline(m_PoiFileSystem,name,',');
			//getline(m_PoiFileSystem,description,',');
			//getline(m_PoiFileSystem,latitude1,',');
			//getline(m_PoiFileSystem,longitude1,'\n');
			//latitude = atof(latitude1.c_str());
			//longitude = atof(longitude1.c_str());
			checkPoi = retParseStringPoi(line,type1,name,description,latitude,longitude);
			bool checkType = true;
			if(type1 == "RESTAURANT"){
				type = RESTAURANT;
			}
			else if(type1 == "TOURISTIC"){
				type = TOURISTIC;
			}
			else if(type1 == "GASSTATION"){
				type = GASSTATION;
			}
			else if(type1 == "UNIVERSITY"){
				type = UNIVERSITY;
			}
			else{
				cout << "Problem : Type of Poi Irrelevant ";
				checkType = false;
			}
			//cout << name<<endl;
			//CPOI(type,name,description,latitude,longitude).print();
			if(!checkPoi && checkType && checkName(name) && checkName(description)){
				switch(mode){
				case MERGE:
					poiDb.add(CPOI(type,name,description,latitude,longitude));
					break;
				case REPLACE:
					poiDb.add(CPOI(type,name,description,latitude,longitude));
					break;
				}
			}
			else{
				cout << "Problem in line : "<<lineCounter<<" :\t"<<type<<"\t"
						<<name<<"\t"<<description<<"\t"<<latitude<<"\t"<<longitude<<endl;
			}
			lineCounter++;
			//name=longitude1=latitude1 =type1 = description ="";
		}
		m_PoiFileSystem.close();
	}
	return checkWpOpen && checkPoiOpen;
}
	/**
	 * @param string name [IN]
	 * @return bool [OUT]
	 * This function checks whether a string is a pure string or not
	 */
bool Ccsv::checkName(string name)
{
	unsigned int counter = 0;
	for (unsigned int pos=0;pos<name.length();pos++){
		// To check whether the string is correct or not
		if(isalpha(name[pos]) || isspace(name[pos])){
			counter++;
			}
		}
		// To check the length of the string name matches the counter variable
		if (counter == name.length()){
			return true;
		}
		else{
			return false;
		}
}
/**
 * @param string line -> string of one line from file[IN]
 * @param string& name -> string extracted from the 'line'[OUT]
 * @param double& latitude -> double value extracted from the 'line'[OUT]
 * @param double& longitude -> double value extracted from the 'line'[OUT]
 * @return bool
 * This function returns the parsed values from csv as required for waypoint to be created
 * This also returns bool to specify whether the 'line' is of csv format or not,
 * and checks wrong attributes of a string
 */
bool Ccsv::retParseStringWp(string line, string& name, double& latitude,
		double& longitude)
{
	bool checkProb1 = false;
	bool checkProb2 = false;
	bool checkProb3 = false;
	bool checkProb4 = false;
	//char token;
	string name1,longitude1,latitude1 = "";
	vector<size_t> index;
	size_t i =0;
	vector<char> tokenizer;
	tokenizer.push_back(',');
	tokenizer.push_back(';');
	tokenizer.push_back('~');
	//create a vector of char for delimeters
	//loop through the vector and find out index of delimeter present in line
	//if more then one index found then choose the first one
	//use the index found as token[index] in while loop below
	/*if(line.find(',') != string::npos && line.find(';') != string::npos){
		token = ';';
	}
	else if(line.find(';') != string::npos){
		token = ';';
	}
	else if(line.find(',') != string::npos){
		token = ',';
	}
	else{
		cout << "Problem : Not a csv format";
		checkProb3 = true;
	}*/
	int tokenIndex = 0;
	for(unsigned int i=0,j=1;i<tokenizer.size();i++){
		//cout<<tokenizer[i]<<endl;
		if(line.find(tokenizer[i]) != string::npos){
			tokenIndex = i;
		}
		else if(tokenizer[i]!=',' && line.find(tokenizer[i]) != string::npos && line.find(',')){
			tokenIndex = i;
		}
		else{
			if(j==tokenizer.size()){
				cout << "Problem : not a valid csv format";
				checkProb3 = true;
			}
			j++;
		}
	}
			//run through the string
	while(i < line.size() - 1 ){
		//check what is the position of ',' or token
		i = line.find(tokenizer[tokenIndex],i);
		if(i != string::npos){
			index.push_back(i);
		}
		else{
			break;
		}
		//slice string into substring using above position
		//increment counter by 1
		i++;
	}
		//cout << index.size()<<endl;
		/*vector<size_t>::iterator itr;
		for(itr=index.begin();itr!=index.end();itr++){
			cout << (*itr) <<endl;
		}
		cout << index[0]<<endl;
		*/
		//cout << index[1]<<endl;
	if(index.size() == 2){
		name = line.substr(0,index[0]-0);
		latitude1 = line.substr(index[0]+1,index[1]-index[0]-1);
		longitude1 = line.substr(index[1]+1,line.size());
		if(longitude1.find(',')!= string::npos || latitude1.find(',')!= string::npos){
			cout << "Problem : Please enter the latitude and longitude in decimal format"<<endl;
			checkProb2 = true;
		}
		if(!checkDigit(latitude1) || !checkDigit(longitude1)){
			cout << "Problem : Values of long and lati not correct"<<endl;
			checkProb4 = true;
		}
		longitude = atof(longitude1.c_str());
		latitude = atof(latitude1.c_str());
	}
	else{
		cout << "Problem : Insufficient entries";
		checkProb1 = true;
	}
	return checkProb1 || checkProb2 || checkProb3 || checkProb4;
		//cout << latitude1<<endl;
		//cout << longitude1<<endl;
}
/**
 * @param string line -> string of one line from file[IN]
 * @param string type1 -> string extracted from the 'line'[OUT]
 * @param string& name -> string extracted from the 'line'[OUT]
 * @param string& description -> string extracted from the 'line'[OUT]
 * @param double& latitude -> double value extracted from the 'line'[OUT]
 * @param double& longitude -> double value extracted from the 'line'[OUT]
 * @return bool
 * This function returns the parsed values from csv as required for POI to be created
 * This also returns bool to specify whether the 'line' is of csv format or not,
 * and checks wrong attributes of a string
 */
bool Ccsv::retParseStringPoi(string line,string& type1,string& name,string &description,double& latitude,double& longitude){

	//int counter = 0;
	bool checkProb1 = false;
	bool checkProb2 = false;
	bool checkProb3 = false;
	bool checkProb4 = false;
	//char token;
	string longitude1,latitude1= "";
	vector<size_t> index;
	size_t i =0;
	vector<char> tokenizer;
	tokenizer.push_back(',');
	tokenizer.push_back(';');
	tokenizer.push_back('~');
	/*if(line.find(',') != string::npos && line.find(';') != string::npos){
		token = ';';
	}
	else if(line.find(';') != string::npos){
		token = ';';
	}
	else if(line.find(',') != string::npos){
		token = ',';
	}
	else{
		cout << "Problem : Not a csv format";
		checkProb3 = true;
	}*/
	int tokenIndex = 0;
	//loop through the vector and find out index of delimeter present in line
	for(unsigned int i=0,j=1;i<tokenizer.size();i++){
		//cout<<tokenizer[i]<<endl;
		if(line.find(tokenizer[i]) != string::npos){
			tokenIndex = i;
		}
		else if(tokenizer[i]!=',' && line.find(tokenizer[i]) != string::npos && line.find(',')){
			tokenIndex = i;
		}
		else{
			if(j==tokenizer.size()){
				cout << "Problem : not a valid csv format";
			}
			j++;
		}
	}
		//run through the string
	while(i < line.size() - 1 ){
		//check what is the position of ',' or token
		i = line.find(tokenizer[tokenIndex],i);
		if(i != string::npos){
			index.push_back(i);
		}
		else{

			break;
		}
		//slice string into substring using above position
		//increment counter by 1
		i++;
	}
	//cout << index.size()<<endl;
	/*vector<size_t>::iterator itr;
	for(itr=index.begin();itr!=index.end();itr++){
		cout << (*itr) <<endl;
	}
	cout << index[0]<<endl;
	*/
	//cout << index[1]<<endl;
	if(index.size() == 4){
		type1 = line.substr(0,index[0]-0);
		name = line.substr(index[0]+1,index[1]-index[0]-1);
		description = line.substr(index[1]+1,index[2]-index[1]-1);
		latitude1 = line.substr(index[2]+1,index[3]-index[2]-1);
		longitude1 = line.substr(index[3]+1,line.size());
		if(longitude1.find(',')!= string::npos || latitude1.find(',')!= string::npos){
			cout << "Problem : Please enter the latitude and longitude in decimal format"<<endl;
			checkProb2 = true;
		}
		if(!checkDigit(latitude1) || !checkDigit(longitude1)){
			cout << "Problem : Values of long and lati not correct"<<endl;
			checkProb4 = true;
		}
		longitude = atof(longitude1.c_str());
		latitude = atof(latitude1.c_str());
	}
	else{
		cout << "Problem : Insufficient entries";
		checkProb1 = true;
	}
	return checkProb1 || checkProb2 || checkProb3 || checkProb4;
	//cout << latitude1<<endl;
	//cout << longitude1<<endl;
}
/**
 * @param string name
 * @returnvalue bool
 * This function checks whether a string has only digits and decimal points
 */
bool Ccsv::checkDigit(string name)
{
	unsigned int counter = 0;
	for (unsigned int pos=0;pos<name.length();pos++){
	// To check whether the string is correct or not
		if(isdigit(name[pos]) || name[pos] == '.'){
			counter++;
		}
	}
	// To check the length of the string name matches the counter variable
	if (counter == name.length()){
		return true;
	}
	else{
		return false;
	}
}
