/*
MIT License

Copyright (c) 2023 MrSung82

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CM_BASEMATHFUNC_H
#define CM_BASEMATHFUNC_H

#include <cmath>
#include <limits>

const float kCmDefaultToleranceF = 1e-6f;
const double kCmDefaultToleranceD = 1e-10;

template <typename T>
inline void CmSwap(T& a, T& b)
{
    T t{a};
    a = b;
    b = t;
}

template <typename T>
inline T CmAbs(T x)
{
    return (x < 0) ? -x : x;
}

template <>
inline double CmAbs(double x)
{
    return std::fabs(x);
}

template <>
inline float CmAbs(float x)
{
    return static_cast<float>(std::fabs(x));
}

template<typename T>
inline T CmDefaultTolerance();

template <>
inline float CmDefaultTolerance()
{
    return kCmDefaultToleranceF;
}

template <>
inline double CmDefaultTolerance()
{
    return kCmDefaultToleranceD;
}

template <typename T>
inline bool CmEquals(T x1, T x2, T tol = CmDefaultTolerance<T>())
{
    return CmAbs(x1 - x2) <= tol;
}

template <typename T>
inline bool CmEqualsPerByte(T x1, T x2, T tol = CmDefaultTolerance<T>())
{
    CmUInt8* pBytes1 = reinterpret_cast<CmUInt8*>(&x1);
    CmUInt8* pBytes2 = reinterpret_cast<CmUInt8*>(&x2);
    for (CmUInt32 i = 0; i < sizeof(T); ++i)
    {
        if (pBytes1[i] != pBytes2[i])
            return false;
    }
    return true;
}

template <typename T>
bool CmLess(T x1, T x2, T tol = CmDefaultTolerance(T()))
{
    return x1 < (x2 - tol);
}

template <typename T>
bool CmLessOrEqual(T x1, T x2, T tol = CmDefaultTolerance(T()))
{
    return x1 <= (x2 + tol);
}

template <typename T>
bool CmGreater(T x1, T x2, T tol = CmDefaultTolerance(T()))
{
    return x1 > (x2 + tol);
}

template <typename T>
bool CmGreaterOrEqual(T x1, T x2, T tol = CmDefaultTolerance(T()))
{
    return x1 >= (x2 - tol);
}

template <typename T>
bool CmIsZero(T x, T tol = CmDefaultTolerance(T()))
{
    return x >= (-tol) && x <= tol;
}

template <typename T>
inline T CmSqrt(T x)
{
    double dX = static_cast<double>(x);
    T retVal = static_cast<T>(sqrt(x));
    return retVal;
}

template <typename T>
inline double CmLengthSq(T* p, CmUInt32 n)
{
    double l{};
    for (int i = 0; i < n; ++i)
    {
        l += double(p[i]) * double(p[i]);
    }
    return l;
}

template <typename T>
inline T CmLength(T* p, CmUInt32 n)
{
    double lSq{CmLengthSq(p, n)};
    return static_cast<T>(sqrt(lSq));
}

inline T CmNormalize(T* p, CmUInt32 n)
{
    T l{CmLength(p, n)};
    T maxValue{std::numeric_limits<T>::max()};
    T tol = T(10) / maxValue;
    if (CmLess(tol, CmDefaultTolerance<T>()))
        tol = CmDefaultTolerance<T>();
    if (CmIsZero(l, tol))
    {
        p[0] = T(1);
        for (int i = 1; i < n; ++i)
        {
            p[i] = T(0);
        }
    }
    else
    {
        T invL{T(1) / l};
        for (int i = 0; i < n; ++i)
        {
            p[i] *= invL;
        }
    }
    return l;
}
#endif // CM_BASEMATHFUNC_H

