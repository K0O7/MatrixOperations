#include "CMatrix.h"

template<typename T>
CMatrix<T>::CMatrix()
{
	Matrix = nullptr;
	iLines = 0;
	iColumns = 0;
	bIsCreated = false;
}

template<typename T>
CMatrix<T>::CMatrix(int iVertical, int iDiagnal)
{
	iLines = iVertical;
	iColumns = iDiagnal;

	Matrix =  new T*[iLines];
	for (int i = 0; i < iLines; i++)
		Matrix[i] = new T[iColumns];

	bIsCreated = true;

	if (debug) {
		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < iColumns; j++)
				Matrix[i][j] = 0;

	}
}

template<typename T>
CMatrix<T>::CMatrix(CMatrix<T>& cOther)
{
}

template<typename T>
CMatrix<T>::CMatrix(CMatrix<T>&& cOther)
{
}

template<typename T>
CMatrix<T>::~CMatrix()
{
	if (bIsCreated) {
		for (int i = 0; i < iLines; i++)
			delete[] Matrix[i];
		delete[] Matrix;
	}
}

template<typename T>
bool CMatrix<T>::bCreate(int iVertical, int iDiagnal)
{
	if (!bIsCreated) {
		iLines = iVertical;
		iColumns = iDiagnal;

		Matrix = new T * [iLines];
		for (int i = 0; i < iLines; i++)
			Matrix[i] = new T[iColumns];

		bIsCreated = true;
		return true;
	}
	return false;
}

template<typename T>
bool CMatrix<T>::bCreate(std::string sFileName)
{
	if (!bIsCreated) {
		bool* err = new bool(false);
		std::vector<std::vector<std::string>>* matr = vvsReadFromFile(sFileName, err);
		if (!(*err)) {

			Matrix = new T * [iLines];
			for (int i = 0; i < iLines; i++)
				Matrix[i] = new T[iColumns];

			vSetValues(matr);
			bIsCreated = true;
			delete err;
			return true;
		}
		delete err;
	}
	return false;
}

template<typename T>
T CMatrix<T>::GetVal(int iVertical, int iDiagnal)
{
	if(iLines <= iVertical && iColumns <= iDiagnal && bIsCreated)
		return Matrix[iVertical][iDiagnal];
	return;
}

template<typename T>
bool CMatrix<T>::bAddition(CMatrix<T>& cOther)
{
	if (bIsCreated && cOther.bIsCreated && iLines == cOther.iLines && iColumns == cOther.iColumns) {
		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < iColumns; j++)
				Matrix[i][j] += cOther.Matrix[i][j];

		return true;
	}
	return false;
}

template<typename T>
bool CMatrix<T>::bSubtraction(CMatrix<T>& cOther)
{
	if (bIsCreated && cOther.bIsCreated && iLines == cOther.iLines && iColumns == cOther.iColumns) {
		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < iColumns; j++)
				Matrix[i][j] -= cOther.Matrix[i][j];

		return true;
	}
	return false;
}

template<typename T>
T** CMatrix<T>::Multiplication(CMatrix<T>& cOther)
{
	if (bIsCreated && cOther.bIsCreated && iColumns == cOther.iLines) {
		T** wynik = new T * [iLines];
		int temp;
		for (int i = 0; i < iLines; i++)
			wynik[i] = new T[cOther.iColumns];

		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < cOther.iColumns; j++){
				temp = 0;
				for (int k = 0; k < iColumns; k++)
					temp += Matrix[i][k] * cOther.Matrix[k][j];
				wynik[i][j] = temp;
			}

		return wynik;
	}
	return nullptr;
}

template<typename T>
bool CMatrix<T>::bMultiplication(double dMul)
{
	if (bIsCreated) {
		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < iColumns; j++)
				Matrix[i][j] *= dMul;
		return true;
	}
	return false;
}

template<typename T>
bool CMatrix<T>::bScalar(CMatrix<T>& cOther)
{
}

template<typename T>
T** CMatrix<T>::Transposition()
{
	T** Tmatrix = new T * [iColumns];
	for (int i = 0; i < iColumns; i++)
		Matrix[i] = new T[iLines];

	for (int i = 0; i < iLines; i++)
		for (int j = 0; j < iColumns; j++)
			Tmatrix[j][i] = Matrix[i][j];

	return Tmatrix;
}


template<typename T>
std::vector<std::vector<std::string>>* CMatrix<T>::vvsReadFromFile(std::string sFileName, bool* bErrors)
{
	std::vector<std::vector<std::string>>* mat = new std::vector<std::vector<std::string>>;
	std::ifstream infile(sFileName);
	if (infile.is_open()) {
		std::string line;
		std::regex token(R"(\s)");
		std::regex check(R"([^\s\d.])");
		int cols = 0;
		while (std::getline(infile, line)) {
			iLines++;
			if (vsTokenize(line, check).size() > 1) {
				*bErrors = true;
			}
			std::vector<std::string> tokenized = vsTokenize(line, token);
			cols = tokenized.size();
			mat->push_back(tokenized);
			if (iColumns == 0)
				iColumns = cols;
			if (cols != iColumns)
				*bErrors = true;
		}
	}
	else
		*bErrors = true;
	return mat;
}

template<typename T>
bool CMatrix<T>::bVectorFromColumn(int iNumber)
{
}

template<typename T>
bool CMatrix<T>::bVectorFromLine(int iNumber)
{
}

template<typename T>
bool CMatrix<T>::bToIdentityM()
{
	if (iColumns == iLines && bIsCreated) {
		for (int i = 0; i < iLines; i++)
			for (int j = 0; j < iColumns; j++)
				if(i == j)
					Matrix[i][j] = 1;
				else
					Matrix[i][j] = 0;

		return true;
	}
	return false;
}

template<typename T>
void CMatrix<T>::vPrintMat() {
	if (bIsCreated) {
		for (int i = 0; i < iLines; i++) {
			for (int j = 0; j < iColumns; j++)
				std::cout << Matrix[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

template<typename T>
void CMatrix<T>::vPrintTMat() {
	if (bIsCreated) {
		for (int i = 0; i < iColumns; i++) {
			for (int j = 0; j < iLines; j++)
				std::cout << Matrix[j][i] << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

template<typename T>
std::vector<std::string> CMatrix<T>::vsTokenize(const std::string sString, const std::regex rPatern)
{
	std::sregex_token_iterator it{ sString.begin(), sString.end(), rPatern, -1 };
	std::vector<std::string> tokenized{ it, {} };

	return tokenized;
}