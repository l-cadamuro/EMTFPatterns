#ifndef GEOMETRYUTILS_H
#define GEOMETRYUTILS_H

#include <utility>
#include <vector>

namespace GeometryUtils
{
    // --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - 
    float degToRad(float x)
        return x/180.*TMath::Pi();

    float radToDeg(float x)
        return x/TMath::Pi()*180.;

    // --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - 

    void to_mpi_pi( float angle ) 
    {
        while ( angle < -180 ) angle += 360;
        while ( angle >  180 ) angle -= 360;
        return angle;
    }

    // --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - --- - 

    // note: gives false if testAngle == a or b
    bool isWithinRange( float testAngle, float a, float b )
    {
        a -= testAngle;
        b -= testAngle;
        a = normalize( a );
        b = normalize( b );
        if ( a * b >= 0 )
            return false;
        return fabs( a - b ) < 180;
    }

    bool isWithinRange( float testAngle, std::pair<float,float> bounds)
        return isWithinRange(testAngle, bounds.first, bounds.second);


}

#endif