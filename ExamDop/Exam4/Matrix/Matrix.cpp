#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
/**
     * Constructor for matrix
     * @param n contains count of rows and colums
     */
Matrix::Matrix(unsigned int n)
{
    this->n = n;

    std::vector<long long int> temp;
    for(int j = 0; j<n; j++)
        temp.push_back(0);
    for(int i = 0; i<n; i++)
        arr.push_back(temp);
}
/**
     * Function to creating random matrix
     */
void Matrix::random()
{
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            arr[i][j] = rand()%1000 - 500;
}
/**
     * function to return n
     * @return count of rows and colums
     */
unsigned int Matrix::getN()
{
    return n;
}
/**
     * function to creating matrix from console
     */
void Matrix::create()
{
    std::cout<<"Enter "<<n*n<<" elements:"<<std::endl;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            std::cin>>arr[i][j];
}
/**
     * function to print matrix in console
     */
void Matrix::display()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout<<arr[i][j]<<" ";
        std::cout<<std::endl;
    }
}


/**
     * function to multiply matrix, if temp==-1 standart multiply, else multiply 1/maxThread of matrix
     * @param A first matrix
     * @param B second matrix
     * @param temp contains info about which thread is used
     * @return execution time
     */
long long int Matrix::multiply(Matrix A, Matrix B, int* min,  int temp)
{
    if ((A.getN() == B.getN()) && (A.getN() == n))
    {
        auto b2 = std::chrono::steady_clock::now();
        if (temp == -1)
        {
            for (int i=0; i<n; i++)
                for (int j=0; j<n; j++)
                {
                    this->arr[i][j] = 0;
                    for (int k=0; k<n; k++)
                        this->arr[i][j] += A.arr[i][k] * B.arr[k][j];
                }
        }
        else
        {
            int i = temp;
            while (i<n)
            {
                for (int j=0; j<n; j++)
                {
                    this->arr[i][j] = 0;
                    for (int k=0; k<n; k++)
                        this->arr[i][j] += A.arr[i][k] * B.arr[k][j];
                }
                i += maxThread;
            }
        }
        *min = arr[0][0];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (arr[i][j] < *min) *min = arr[i][j];
        auto e2 = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(e2 - b2).count();
    }
    else
        std::cout<<"Error"<<std::endl;
    return 0;
}

/**
     * fuction to ctart parralel multiplying
     * @param A first matrix
     * @param B second matrix
     * @return execution time
     */
long long int Matrix::multiplyParallel(Matrix A, Matrix B)
{
    if ((A.getN() == B.getN()) && (A.getN() == n))
    {
        auto b1 = std::chrono::steady_clock::now();

        std::thread threads[maxThread];
        for (int i = 0; i < maxThread; i++)
            threads[i] = std::thread(&Matrix::multiply, this, A, B, i);
        for (int i = 0; i < maxThread; i++)
            threads[i].join();

        auto e1 = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(e1 - b1).count();
    }
    else
        std::cout<<"Error"<<std::endl;
    return 0;
}