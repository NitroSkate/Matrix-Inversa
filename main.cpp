#include <iostream>
#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

//Se utilizaron las funciones proporcionadas por el instructor

typedef vector<float> Vector;
typedef vector<Vector> Matrix;


void zeroes(Matrix &M, int n) {
    for(int i=0;i<n;i++){
        vector<float> row(n,0.0);
        M.push_back(row);
    }
}

void copyMatrix(Matrix A, Matrix &copy){
    zeroes(copy,A.size());
    for(int i=0;i<A.size();i++)
        for(int j=0;j<A.at(0).size();j++)
            copy.at(i).at(j) = A.at(i).at(j);
}


void getMinor(Matrix &M,int i, int j){
    M.erase(M.begin()+i);
    for(int i=0;i<M.size();i++)
        M.at(i).erase(M.at(i).begin()+j);
}

float determinant(Matrix M){
    if(M.size() == 1) return M.at(0).at(0);
    else{
        float det=0.0;
        for(int i=0;i<M.at(0).size();i++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}



void cofactors(Matrix M, Matrix &Cof){
    zeroes(Cof,M.size());
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

void transpose(Matrix M, Matrix &T){
    zeroes(T,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            T.at(j).at(i) = M.at(i).at(j);
}


void showMatrix(Matrix K){
    for(int i=0;i<K.at(0).size();i++){
        cout << "[\t";
        for(int j=0;j<K.size();j++){
            cout << K.at(i).at(j) << "\t";
        }
        cout << "]\n";
    }
}

void MatrixAdjunta(Matrix &K, float det){
    for(int i=0;i<K.at(0).size();i++){
        for(int j=0;j<K.size();j++){
            K.at(i).at(j) = K.at(i).at(j)/det;
        }
    }
}


void SacarInversa(Matrix original, Matrix &inversa){
    float Determinant_MO;
    Matrix transpuesta;

    transpose(original,transpuesta);
    //showMatrix(matriz_transpuesta);
    cofactors(transpuesta,inversa);
    //showMatrix(matriz_inversa);
    if(determinant(original)==0){
        EXIT_FAILURE;
    } else {
        Determinant_MO = determinant(original);
        //cout << "Determinant: " <<  Determinant_MO;
        MatrixAdjunta(inversa, Determinant_MO);


        //Mostrando matriz inversa
        showMatrix(inversa);
    }
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    Matrix matriz_original, matriz_transpuesta, matriz_inversa;
    //float Determinant_MO;

    zeroes(matriz_original, 3);

    matriz_original.at(0).at(0) = 2; matriz_original.at(0).at(1) = 2; matriz_original.at(0).at(2) = 3;
    matriz_original.at(1).at(0) = 4; matriz_original.at(1).at(1) = 5; matriz_original.at(1).at(2) = 6;
    matriz_original.at(2).at(0) = 7; matriz_original.at(2).at(1) = 8; matriz_original.at(2).at(2) = 9;

    SacarInversa(matriz_original,matriz_inversa);




    return 0;
}
