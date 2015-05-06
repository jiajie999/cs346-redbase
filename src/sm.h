//
// sm.h
//   Data Manager Component Interface
//

#ifndef SM_H
#define SM_H

// Please do not include any other files than the ones below in this file.

#include <stdlib.h>
#include <string.h>
#include "redbase.h"  // Please don't change these lines
#include "parser.h"
#include "rm.h"
#include "ix.h"

// Data structures

// SM_RelcatRecord - Records stored in the relcat relation
/* Stores the follwing:
    1) relName - name of the relation - char*
    2) tupleLength - length of the tuples - integer
    3) attrCount - number of attributes - integer
    4) indexCount - number of indexes - integer
*/
struct SM_RelcatRecord {
    char relName[MAXNAME];
    int tupleLength;
    int attrCount;
    int indexCount;
};

// SM_AttrcatRecord - Records stored in the attrcat relation
/* Stores the follwing:
    1) relName - name of the relation - char*
    2) attrName - name of the attribute - char*
    3) offset - offset of the attrbiute - integer
    4) attrType - type of the attribute - AttrType
    5) attrLength - length of the attribute - integer
    6) indexNo - number of the index - integer
*/
struct SM_AttrcatRecord {
    char relName[MAXNAME];
    char attrName[MAXNAME];
    int offset;
    AttrType attrType;
    int attrLength;
    int indexNo;
};

//
// SM_Manager: provides data management
//
class SM_Manager {
    friend class QL_Manager;
public:
    SM_Manager    (IX_Manager &ixm, RM_Manager &rmm);
    ~SM_Manager   ();                             // Destructor

    RC OpenDb     (const char *dbName);           // Open the database
    RC CloseDb    ();                             // close the database

    RC CreateTable(const char *relName,           // create relation relName
                   int        attrCount,          //   number of attributes
                   AttrInfo   *attributes);       //   attribute data
    RC CreateIndex(const char *relName,           // create an index for
                   const char *attrName);         //   relName.attrName
    RC DropTable  (const char *relName);          // destroy a relation

    RC DropIndex  (const char *relName,           // destroy index on
                   const char *attrName);         //   relName.attrName
    RC Load       (const char *relName,           // load relName from
                   const char *fileName);         //   fileName
    RC Help       ();                             // Print relations in db
    RC Help       (const char *relName);          // print schema of relName

    RC Print      (const char *relName);          // print relName contents

    RC Set        (const char *paramName,         // set parameter to
                   const char *value);            //   value

private:
    RM_Manager* rmManager;           // RM_Manager object
    IX_Manager* ixManager;           // IX_Manager object
};

//
// Print-error function
//
void SM_PrintError(RC rc);


// Warnings
#define SM_INVALID_DATABASE                 (START_SM_WARN + 0) // Database does not exist
#define SM_LASTWARN                         SM_INVALID_DATABASE

// Errors
#define SM_INVALID_DATABASE_NAME            (START_SM_ERR - 0) // Invalid database file name

// Error in UNIX system call or library routine
#define SM_UNIX                 (START_SM_ERR - 1) // Unix error
#define SM_LASTERROR            SM_UNIX

#endif