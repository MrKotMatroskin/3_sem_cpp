#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string.h>

class Matrix {
    private:
        int** mat_;  // массив для хранения значений матрицы
        int size_;  // размер стороны матрицы
    public:
        Matrix(int arr[], size_t n_elements) {
            size_ = int(sqrt(n_elements));
            mat_ = (int**)calloc(size_, sizeof(int*));
            for (int i = 0; i < size_; ++i) {
                mat_[i] = (int*)calloc(size_, sizeof(int));
            }
            for (size_t i = 0, j = 0, k = 0; i < n_elements; ++i) {
                mat_[k][j] = arr[i];
                j++;
                k += j / size_;
                j %= size_;
            }
        }
        Matrix(int element, size_t n_elements) {
            size_ = int(sqrt(n_elements));
            mat_ = (int**)calloc(size_, sizeof(int*));
            for (int i = 0; i < size_; ++i) {
                mat_[i] = (int*)calloc(size_, sizeof(int));
            }
            for (size_t i = 0, j = 0, k = 0; i < n_elements; ++i) {
                mat_[k][j] = element;
                j++;
                k += j / size_;
                j %= size_;
            }
        }

        Matrix() {
            mat_ = (int**)calloc(1, sizeof(int*));
            mat_[0] = (int*)calloc(1, sizeof(int));
            mat_[0][0] = 1;
            size_ = 1;
        }

        Matrix(const Matrix& other) {
            mat_ = (int**)calloc(other.size_, sizeof(int*));
            for (int i = 0; i < other.size_; ++i) {
                mat_[i] = (int*)calloc(other.size_, sizeof(int));
            }
            for (int i = 0; i < other.size_; ++i) {
                for (int j = 0; j < other.size_; ++j)
                    mat_[i][j] = other.mat_[i][j];
            }
            size_ = other.size_;
        }

        void printMatrix() {
            for (int i = 0; i < size_; ++i) {
                for (int j = 0; j < size_; ++j)
                    std::cout << mat_[i][j] << " ";
                std::cout << "\n";
            }
        }

        double calcDeterminant() {
            int** cpy;
            cpy = (int**)calloc(size_, sizeof(int*));
            for (int i = 0; i < size_; ++i){
                cpy[i] = (int*)calloc(size_, sizeof(int));
                memcpy(cpy[i], mat_[i], size_*sizeof(int));
            }
            double determenant = 1, tmp = 0;
            for (int k = 0; k < size_ - 1; k++) {
                for (int i = k + 1; i < size_; i++) {
                    tmp = -cpy[i][k] / cpy[k][k];
                        for (int j = 0; j < size_; j++) {
                            cpy[i][j] += cpy[k][j] * tmp;
                        }
                }
            }
            for (int i = 0; i < size_; ++i) {
                determenant *= cpy[i][i];
            }
            for (int i = 0; i < size_; ++i){
                free(cpy[i]);
            }
            free(cpy);
            return determenant;
        }

        void calcSquare() {
            int** cpy = (int**)calloc(size_, sizeof(int*));
            for (int i = 0; i < size_; ++i) {
                cpy[i] = (int*)calloc(size_, sizeof(int));
            }
            for (int i = 0; i < size_; i++)
                for (int j = 0; j < size_; j++)
                    for (int k = 0; k < size_; k++)
                        cpy[i][j] += mat_[i][k] * mat_[k][j];
            for (int i = 0; i < size_; ++i){
                free(mat_[i]);
            }
            free(mat_);
            mat_ = cpy;
        }

        void matTranspose() {
            for (int i = 0; i < size_; ++i) {
                for (int j = i; j < size_; ++j) {
                    int tmp = mat_[i][j];
                    mat_[i][j] = mat_[j][i];
                    mat_[j][i] = tmp;
                }
            }
        }

        ~Matrix() {
            for (int i = 0; i < size_; ++i){
                free(mat_[i]);
            }
            free(mat_);
        }
};


int main() {
    int arr[] = {1,0,2,4};
    Matrix m(arr, 4);
    m.calcSquare();
    m.printMatrix();
    std::cout<<"\n";
    Matrix cpy(m);
    cpy.printMatrix();
    return 0;
}
