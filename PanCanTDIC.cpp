/* 
 * File:   PanCanTDIC.cpp
 *
 * 
 * 
 */

#include "TDIC.h"
#include "PanCanTDIC.h"
#include "TDIMatrix.h"
#include "GTMatrix.h"
#include "PanCanGTMatrix.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <float.h>

using namespace std;
/**
 * This function performs tumor-specific driver identification.  It calculate the causal score for all 
 * GT-vs-GE pairs observed in a given tumor, populate a GT-by-GE score matrix and output to file.  
 * @param gtMatrix     An TDIMatrix reference, in which SGA data of a collection of tumors are stored
 *                              in a tumor-by-gene matrix
 * @param geMatrix        An TDIMatrix reference, in which DEG data of a collection of tumors are stored
 *                              in a tumor-by-gene matrix
 * @param mapGlobDrivers        A reference to a dictionary of global drivers of DEGs in the "geMatrix",
                                Each entry is keyed by the DEG gene name, and the value is a reference of a 
                                vector<string> containing the two 2 global driver.  
 * @param tumorID               The tumor to be process
 */
void PanCanTDIC(GTMatrix& gtMatrix, TDIMatrix& geMatrix, map<string, 
        string>& mapGlobDrivers, const int tumorID, const string outPath, const float v0){
    // initializations 
 
   
}

