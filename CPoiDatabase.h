/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H
#include <map>
#include <iterator>
#include "t_poi.h"
#include "CPOI.h"
//class CPOI;
class CPoiDatabase {
private:
    /**
     * @link aggregationByValue 
     */
    map<string, CPOI> m_POI;
    map<string, CPOI>::iterator m_itrPoi;
public:

    CPoiDatabase();
    /** This method adds POI to the Database
     * @param const CPOI& poi - poi object[IN]
     * @return void
     */
    void addPoi(const CPOI & poi);
    /**
     * This method is used to find the POI in the POI Database with the primary key as name
     * @param string name	- name value (IN)
     * @returnvalue CPOI* - pointer to found poi(OUT)
     */
    CPOI* getPointerToPoi(string name);
    /**
     * @param void
     * @returnvalue map<string, CPOI>
     * It returns the map containing data of the Database
     */
    map<string, CPOI> getMapOfPoi() const;
    /**
     * @param void
     * @returnvalue void
     * It deletes the data of PoiDatabase
     */
    void poiDelete();
    /**
     * @param void
     * @returnvalue void
     * It prints the map of database
     */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
