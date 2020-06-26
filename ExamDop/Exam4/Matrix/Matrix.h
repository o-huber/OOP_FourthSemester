#ifndef INC_2_LAB_GROUP_H
#define INC_2_LAB_GROUP_H

#include <string>
#include <vector>

/**
 * Class to store information of matrix
 */
class Matrix {
private:
    unsigned int n = 0;
public:
    std::vector<std::vector<long long int>> arr;

    /**
     * Constructor for matrix
     * @param n contains count of rows and colums
     */
    Matrix(unsigned int n);
    /**
     * Function to creating random matrix
     */
    void random();
    /**
     * function to get matrix from file
     * @param name contains file path
     */

    unsigned int getN();
    /**
     * function to creating matrix from console
     */
    void create();
    /**
     * function to print matrix in console
     */
    void display();
    /**
     * function to multiply matrix, if temp==-1 standart multiply, else multiply 1/maxThread of matrix
     * @param A first matrix
     * @param B second matrix
     * @param temp contains info about which thread is used
     * @return execution time
     */
    long long int multiply(Matrix A, Matrix B, int* = nullptr, int temp = -1);
    /**
     * fuction to ctart parralel multiplying
     * @param A first matrix
     * @param B second matrix
     * @return execution time
     */
    long long int multiplyParallel(Matrix A, Matrix B, int*);

};
extern unsigned int maxThread;
#endif //INC_2_LAB_GROUP_H
