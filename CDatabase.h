/*
 * CDatabase.h
 *
 *  Created on: Jan 11, 2019
 *      Author: swapnil
 */

#ifndef CDATABASE_H_
#define CDATABASE_H_
#include <map>
#include <iterator>
#include <string>
#include <iostream>
namespace APT{
template<class T>
class CDatabase
{
	std::map<std::string,T> m_Db;
public:
	void add(const T& obj);
	T* getPointerToDbObj(std::string name);
	void DbobjDelete();
	std::map<std::string,T> getMapOfDbObj() const;
	void print();
};
} // namespace APT

template<class T>
inline void APT::CDatabase<T>::add(const T& obj)
{
	bool check = false;
	if(m_Db.find(obj.getName()) != m_Db.end()){
		check = true;
	}
	if(check == false){
		m_Db.insert(std::pair<std::string,T>(obj.getName(),obj));
	}
	else{
		std::cout << "The value already exists and therefore can't allow to insert again for key value"
				<<" "<<obj.getName()<<std::endl;
	}
}

template<class T>
inline T* APT::CDatabase<T>::getPointerToDbObj(std::string name)
{
	typename std::map<std::string,T>::iterator itr;//typename writes iterator for non-constant objects
	if(m_Db.find(name) != m_Db.end()){
		itr = m_Db.find(name);
		return &(itr->second);
	}
	else{
		std::cout << "The POI not present"<<std::endl;
		return NULL;
	}
}

template<class T>
inline void APT::CDatabase<T>::DbobjDelete()
{
	m_Db.clear();
}

template<class T>
inline std::map<std::string, T> APT::CDatabase<T>::getMapOfDbObj() const
{
	return m_Db;
}

template<class T>
inline void APT::CDatabase<T>::print()
{
	typename std::map<std::string,T>::iterator itr;
	std::cout << "\nThe map m_WP is : \n";
		std::cout << "\tKEY\tELEMENT\n";
		for(itr=m_Db.begin();itr != m_Db.end();itr++){
			std::cout << "\t" << itr->first<<"\t";
			//itr->second.print(MMSS);
			std::cout << itr->second<<endl;
			std::cout<< endl;
		}
}

#endif /* CDATABASE_H_ */
