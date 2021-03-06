/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GTCMatrix.cpp
 * Author: XIM33
 * 
 * Created on March 16, 2016, 12:51 PM
 */
#include <math.h>

#include "TDIMatrix.h"
#include "GTMatrix.h"

using namespace std;

#include <algorithm>    // std::find
#include <vector>
#include <fstream> 
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>

#include "GTCMatrix.h"


GTCMatrix::GTCMatrix() {

   
}
GTCMatrix::GTCMatrix(string fileName) 
{
    this->load(fileName);
    calcGlobalAlphaPriors();
}


GTCMatrix::~GTCMatrix(){
   
}





/**
 * Load GT with cancel type data from raw data (CSV file).
 * The last columns are cancel types which are loaded into canTypes vector
 * @param fileName Filepath for a CSV file representing a GTC matrix.
 */
void GTCMatrix::load(string fileName){
    std::stringstream ss;
    std::string line;
    ifstream inFileStream;   
    vector<int*> matrixAsVec;
    int nCol = 0, nRow = 0;

    try{
        inFileStream.open(fileName.c_str());
        if ( (inFileStream.rdstate() & std::ifstream::failbit ) != 0 )
        {
            std::cerr << "Error opening file when loading GTMC matrix, quit.\n File Name: " << fileName;
            inFileStream.close();
            exit(EXIT_FAILURE);
        }
    }
    catch (...) { //std::ifstream::failure e
        cerr << "Fail to open file " << fileName;
        
    } 
            
    // read in first line to figure out the number of columns and column Names;
    getline(inFileStream, line);
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    
    string tmp;
    stringstream firstSS (line);

    bool firstColFlag = true;
    geneNames.push_back("A0"); 
    while (getline(firstSS, tmp, ',' )){
        if(firstColFlag)
        {
                firstColFlag = false;
                continue;
        }
        geneNames.push_back(tmp);
       
        //geneIndxMap.insert(std::pair<string, int>(tmp, nCol));
        nCol ++;
    }

    //last column is cancel type not gene name, so popback, nCol minus 1
    geneNames.pop_back();
    nCol--;
    
    while (getline(inFileStream, line)){
        firstColFlag = true; 

        stringstream anotherss (line);
        string tmp;
        int curCol = 0;
        while (getline(anotherss, tmp, ',')){
                if(firstColFlag)
                {
                    firstColFlag = false;
                    tumorNames.push_back(tmp);
                    matrixAsVec.push_back(new int[nCol]);
                    continue;
                }
                if(curCol != nCol)
                {
                    matrixAsVec[nRow][curCol] = atoi(tmp.c_str());
                    curCol++;
                }
                else
                {
                    canTypes.push_back(atoi(tmp.c_str())) ;
                }
        }
        nRow++;     
    }
    inFileStream.close();            
    

    
    // transform the vector of inter arrays to a consecutive array so that 
    // computation can be done efficiently
    int indx = 0;
    mat = new int[(nCol+1) * nRow ];
    for (int i = 0; i < nRow; i++)
    {
        mat[indx++] = 1;
    }
    
    for (int g = 0; g < nCol; g++){
        for (int t = 0; t < nRow; t++){
            mat[indx++] = matrixAsVec[t][g];
        }
    }
    
    nTumors = tumorNames.size();
    nGenes = geneNames.size();
    
    // free temporary matrix
    for (int i = 0; i < matrixAsVec.size(); i++) 
        delete[] matrixAsVec[i];
}

