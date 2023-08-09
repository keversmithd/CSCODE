#ifndef GEMat_H_D
#define GEMAT_H_D
#include <initializer_list>
#include <memory>
#include <exception>
#include <math.h>
#include <limits>
#include <iomanip>




struct KDVec
{
    float* data;
    bool copy;
    int VECTOR_DIMENSION_X;
    int MATRIX_END_INDEX;
    int MATRIX_SIZE;

    KDVec() : data(nullptr), copy(true), VECTOR_DIMENSION_X(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0)
    {

    }

    KDVec(int x) : data(nullptr), VECTOR_DIMENSION_X(0), MATRIX_END_INDEX(0), MATRIX_SIZE(0), copy(false)
    {
        MATRIX_SIZE = x;
        data = new float[MATRIX_SIZE];
        VECTOR_DIMENSION_X = x;
        MATRIX_END_INDEX = MATRIX_SIZE-1;
    }

    KDVec(float* p_data, int p_size) : data(p_data), copy(true), VECTOR_DIMENSION_X(p_size), MATRIX_END_INDEX(p_size-1), MATRIX_SIZE(p_size)
    {

    }

    KDVec(const KDVec &c) : data(c.data), VECTOR_DIMENSION_X(c.VECTOR_DIMENSION_X), MATRIX_END_INDEX(c.MATRIX_END_INDEX), MATRIX_SIZE(c.MATRIX_SIZE), copy(true)
    {

    }

    float& operator[](const int index)
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }

    const float c(const int index) const
    {
        if(index < 0 || index > MATRIX_END_INDEX)
        {
            return data[0];
        }

        return data[index];
    }


    void operator=(std::initializer_list<float> L)
    {
        for(int i = 0; i < L.size(); i++)
        {
            data[i] = *(L.begin() + i);
        }
    }


    void display()
    {
        printf("\n");
        printf("|");
        for(int j = 0; j < VECTOR_DIMENSION_X; j++)
        {
            printf("%.3e ", data[j]);
        }
        printf("|\n");

    }

    KDVec operator *(const KDVec other)
    {
        
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        KDVec r(VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            r[i] = data[i] * other.c(i);
        }

        return r;

    }

   void operator*=(const KDVec other)
   {
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        KDVec r(other.VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            data[i] *= other.c(i);
        }

   }

   
    KDVec operator +(const KDVec other)
    {
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        KDVec r(VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            r[i] = data[i] + other.c(i);
        }

        return r;

    }
    void operator +=(const KDVec other)
    {
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            data[i] += other.c(i);
        }
    }

    KDVec operator+(const float c)
    {
        KDVec r(VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            r[i] = data[i] + c;
        }

        return r;
    }
    void operator +=(const KDVec other)
    {
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            data[i] -= other.c(i);
        }
    }

    void operator+=(const float c)
    {

        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            data[i] += c;
        }

    }
    KDVec operator -(const KDVec other)
    {
        if(VECTOR_DIMENSION_X > other.VECTOR_DIMENSION_X)
        {
            throw std::out_of_range("dimension mismatch multiplication");
        }

        KDVec r(VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            r[i] = data[i] - other.c(i);
        }

        return r;

    }
    KDVec operator-(const float c)
    {
        KDVec r(VECTOR_DIMENSION_X);
  
        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            r[i] = data[i] - c;
        }

        return r;
    }

    bool operator !=(const KDVec a)
    {

        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            if(a.c(i) != data[i])
            {
                return true;
            }
        }

        return false;

    }

    bool operator ==(const KDVec a)
    {

        for(int i = 0; i < VECTOR_DIMENSION_X; i++)
        {
            if(a.c(i) != data[i])
            {
                return false;
            }
        }

        return true;

    }

    ~KDVec()
    {
        // if(data != nullptr && copy == false)
        // {
        //     delete[] data;
        //     data = nullptr;
        // }
    
    }

};








#endif