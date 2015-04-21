/******************************************************************************
* Filename      : Vec.hpp
* Source File(s): Vec.cpp
* Description   :
* Authors(s)    :
* Date Created  :
* Date Modified :
* Modifier(s)   :
*******************************************************************************/
#ifndef VEC_H
#define VEC_H

/*******************************************************************************
*  INCLUDES
********************************************************************************/
#include <string>
#include <vector>
#include <xmmintrin.h>
#include <malloc.h>
#include <math.h>
#include <float.h>

/*******************************************************************************
*  DEFINES
********************************************************************************/

/*******************************************************************************
*  MACROS
********************************************************************************/

/*******************************************************************************
*  DATA TYPES
********************************************************************************/
typedef struct rect {
   long left;
   long top;
   long right;
   long bottom;
} RECT;

/*******************************************************************************
*  EXTERNALS
********************************************************************************/

/*******************************************************************************
*  CLASS DEFINITIONS
********************************************************************************/
class Vec
{
    public:
        /* constructors */
        Vec ( void  );
        Vec ( unsigned int ysize = 1,
              unsigned int xsize = 1,
              int yoffset = 0,
              int xoffset = 0,
              const float* data = 0 );
        Vec ( const Vec& );
        Vec ( unsigned int, unsigned int, float );
        Vec ( const std::vector<double>& );
        Vec ( const std::vector< std::vector<double> >& );
        ~Vec ( void );
        /* operators */
        inline const Vec& operator= ( const Vec& );
        inline const Vec& operator= ( const float* );
        inline float& operator() ( int, int );
        inline float operator() ( int, int ) const;
        inline float& operator[] ( unsigned int );
        inline float operator[] ( unsigned int ) const;

        /* functions */
        void print ( void ) const;
        inline float get ( int, int ) const;
        void set ( float );
        void setrand ( void );
        bool copy(const Vec& v, int left = 0, int top = 0);

        inline const Vec& operator* ( const Vec& ) const;
        void add ( const Vec&, const Vec& );
        void sub ( const Vec&, const Vec& );
        void mul ( const Vec&, const Vec& );
        void mult ( const Vec&, const Vec& );
        void dist ( const Vec&, const Vec& );
        void div ( const Vec&, const Vec& );
        void mule ( const Vec&, const Vec& );
        void id_sub ( const Vec& );
        void rownormalize ( const Vec& );
        void add ( float );
        void sub ( float );
        void mul ( float );
        void div ( float );
        float sum ( int ) const;
        float rownorm ( int, int ) const;
        float prod ( void ) const;
        float det ( void ) const;
        void inter( const Vec&, Vec&, Vec& );

        //mat operations
        inline float mconv ( const float*, const float*, unsigned int) const;
        inline float edist ( const float*, const float*, unsigned int) const;
        void conv ( const Vec&, const Vec& );
        void conv ( const Vec&, const Vec&, const Vec& );
        void sim  ( const Vec&, double );
        void deg  ( const Vec& );
        void sqrdeg  ( const Vec& );

        void minmax ( float&, float& ) const;
        float maxval ( void ) const;
        float minval ( void ) const;
        void maxval ( float&, int&, int&, int, int, int, int ) const;

        void normalize ( float, float );
        void histeq ( Vec& );
        void fliplr ( void );
        Vec* repmat ( unsigned int, unsigned int );

        // invert
        Vec* invert ( bool );

        // eiganvalues
        void jacobi_eigenvalue ( int, Vec*, Vec* );

        int xfirst ( void ) const;
        int yfirst ( void ) const;
        int xlast ( void ) const;
        int ylast ( void ) const;
        unsigned int width ( void ) const;
        unsigned int height ( void ) const;
        unsigned int length ( void ) const;
        const float* data ( int, int ) const;

        /* variables */

    private:
        /* variables */
        unsigned int m_width;
        unsigned int m_height;
        int m_xoffset;
        int m_yoffset;
        int m_xlast;
        int m_ylast;

        float** m_data;

        /* functions */
        void init ( unsigned int, unsigned int, int yoffset = 0, int xoffset = 0 );
        void init ( const Vec& );
        void close ( void );
};

/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline int Vec::xfirst ( void ) const
{
    return m_xoffset;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline int Vec::yfirst ( void ) const
{
    return m_yoffset;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline int Vec::xlast ( void ) const
{
    return m_xlast;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline int Vec::ylast ( void ) const
{
    return m_ylast;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline unsigned int Vec::width ( void ) const
{
    return m_width;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline unsigned int Vec::height ( void ) const
{
    return m_height;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline unsigned int Vec::length ( void ) const
{
    return m_width*m_height;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline const Vec& Vec::operator=( const float * pf )
{
    Vec& v = *this;
    for ( int y = v.yfirst(); y <= v.ylast(); y++ )
    {
        for ( int x = v.xfirst(); x <= v.xlast(); x++ )
        {
            v(y, x) = *pf++;
        }
    }

    return *this;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline const Vec& Vec::operator=(const Vec & v)
{
    if (this == &v)
    {
        return *this;
    }
    else if ( m_width == v.width() && m_height == v.height() )
    {  //equal size arrays?
        if (m_xoffset != v.xfirst() || m_yoffset != v.yfirst())
        {   //equal offsets? correct them if not
            m_data += m_yoffset;
            for ( unsigned int j = 0; j < m_height; j++ )
            {
                m_data[j] = m_data[j] + m_xoffset - v.xfirst();
            }
            m_data -= v.yfirst();

            m_xoffset = v.xfirst();
            m_yoffset = v.yfirst();
        }
        init(v);
    }
    else
    {  //create a complete copy from v
        close();
        init(v.height(), v.width(), v.yfirst(), v.xfirst());
        init(v);
    }
    return *this;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float& Vec::operator() ( int y, int x )
{
    return m_data[y][x];
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float Vec::operator() ( int y, int x ) const
{
    return m_data[y][x];
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float& Vec::operator[] ( unsigned int i )
{
    return m_data[i%m_height][i/m_height];     //m_height - MATLAB order operator v[:]
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float Vec::operator[] ( unsigned int i ) const
{
    return m_data[i%m_height][i/m_height];
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float Vec::get ( int y, int x ) const
{
    if ( x < xfirst() )
    {
        x = xfirst() + (xfirst() - x);
    }
    else if ( x > xlast() )
    {
        x = xlast() - (x - xlast());
    }

    if ( y < yfirst() )
    {
        y = yfirst() + (yfirst() - y);
    }
    else if ( y > ylast() )
    {
        y = ylast() - (y - ylast());
    }

    return m_data[y][x];
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      : c = a*b -> C = this*B
********************************************************************************/
inline const Vec& Vec::operator* ( const Vec& b ) const
{
    const Vec& a = *this;

    if (a.xfirst() != 0 || a.yfirst() != 0)
    {
        return a;
    }

    Vec * pc = new Vec(a.height(), b.width());
    Vec& c = *pc;

    for ( unsigned int y = 0; y < c.height(); y++ )
    {
        for ( unsigned int x = 0; x < c.width(); x++ )
        {
            for ( unsigned int i = 0; i < a.width(); i++ )
            {
                c(y, x) += a(y, i) * b(i, x);
            }
        }
    }

    return c;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline const float* Vec::data ( int y, int x ) const
{
    return m_data[y] + x;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float Vec::mconv ( const float* a, const float* b, unsigned int _size ) const
{
    float z = 0.0f, fres = 0.0f;
    __attribute__((aligned(16))) float ftmp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    __m128 mres;

    if ((_size / 4) != 0)
    {
        mres = _mm_load_ss(&z);

        for (unsigned int i = 0; i < _size / 4; i++)
        {
            mres = _mm_add_ps(mres, _mm_mul_ps(_mm_load_ps(&a[4*i]), _mm_load_ps(&b[4*i])));
        }

        //mres = a,b,c,d
        __m128 mv1 = _mm_movelh_ps(mres, mres);     //a,b,a,b
        __m128 mv2 = _mm_movehl_ps(mres, mres);     //c,d,c,d
        mres = _mm_add_ps(mv1, mv2);                //res[0],res[1]

        _mm_store_ps(ftmp, mres);

        fres = ftmp[0] + ftmp[1];
    }

    if ((_size % 4) != 0)
    {
        for ( unsigned int i = _size - _size % 4; i < _size; i++ )
        {
            fres += a[i] * b[i];
        }
    }

    return fres;
}
/*******************************************************************************
* Function     :
* Description  :
* Arguments    :
* Returns      :
* Remarks      :
********************************************************************************/
inline float Vec::edist ( const float* a, const float* b, unsigned int _size ) const
{
    float value = 0.0;
    for ( unsigned int i = 0; i < _size; i++ )
    {
        value += pow(a[i] - b[i], 2);
    }
    return sqrt(value);
}
#endif
