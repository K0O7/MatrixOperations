#pragma once
#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex> 

static bool debug = true;

template<typename T>
class CMatrix
{
private:
	int iLines, iColumns;
	T** Matrix;
	bool bIsCreated = false;
	std::vector<std::string> vsTokenize(const std::string sString, const std::regex rPatern);
	std::vector<std::vector<std::string>>* vvsReadFromFile(std::string sFileName, bool* bErrors);
	void vSetValues(std::vector<std::vector<std::string>>* vvsMatrix);
public:
	CMatrix<T>();
	CMatrix<T>(int iVertical, int iDiagnal);
	CMatrix<T>(CMatrix<T> &cOther);
	CMatrix<T>( CMatrix<T> &&cOther);
	~CMatrix<T>();
	bool bCreate(int iVertical, int iDiagnal);
	bool bCreate(std::string sFileName);
	void vSetVal(int iVertical, int iDiagnal, T tValue);
	T GetVal(int iVertical, int iDiagnal);
	bool bAddition(CMatrix<T>& cOther);
	bool bSubtraction(CMatrix<T>& cOther);
	T** Multiplication(CMatrix<T>& cOther);
	bool bMultiplication(double dMul);
	bool bScalar(CMatrix<T>& cOther);
	T** Transposition();
	bool bVectorFromColumn(int iNumber);
	bool bVectorFromLine(int iNumber);
	bool bToIdentityM();
	void vPrintMat();
	void vPrintTMat();
};

template<typename T>
inline void CMatrix<T>::vSetVal(int iVertical, int iDiagnal, T tValue)
{
	std::cout << "CMatrix obsluguje tylko typy danych int, float, double";
}

template<>
inline void CMatrix<int>::vSetVal(int iVertical, int iDiagnal, int tValue)
{
	if (iLines <= iVertical && iColumns <= iDiagnal && bIsCreated)
		Matrix[iVertical][iDiagnal] = tValue;
}

template<>
inline void CMatrix<double>::vSetVal(int iVertical, int iDiagnal, double tValue)
{
	if (iLines <= iVertical && iColumns <= iDiagnal && bIsCreated)
		Matrix[iVertical][iDiagnal] = tValue;
}

template<>
inline void CMatrix<float>::vSetVal(int iVertical, int iDiagnal, float tValue)
{
	if (iLines <= iVertical && iColumns <= iDiagnal && bIsCreated)
		Matrix[iVertical][iDiagnal] = tValue;
}

template<typename T>
inline void CMatrix<T>::vSetValues(std::vector<std::vector<std::string>>* vvsMatrix)
{
	std::cout << "CMatrix obsluguje tylko typy danych int, float, double";
}

template<>
inline void CMatrix<int>::vSetValues(std::vector<std::vector<std::string>>* vvsMatrix) {
	for (int i = 0; i < iLines; i++)
		for (int j = 0; j < iColumns; j++)
			Matrix[i][j] = std::stoi(vvsMatrix->at(i).at(j));
}

template<>
inline void CMatrix<float>::vSetValues(std::vector<std::vector<std::string>>* vvsMatrix) {
	for (int i = 0; i < iLines; i++)
		for (int j = 0; j < iColumns; j++)
			Matrix[i][j] = std::stof(vvsMatrix->at(i).at(j));

}

template<>
inline void CMatrix<double>::vSetValues(std::vector<std::vector<std::string>>* vvsMatrix) {
	for (int i = 0; i < iLines; i++)
		for (int j = 0; j < iColumns; j++)
			Matrix[i][j] = std::stod(vvsMatrix->at(i).at(j));

}