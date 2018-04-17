#include "stdafx.h"		
#include "DaeCircle.h"
#include "utils.h"
#include <sstream>


DaeCircle::DaeCircle( const Point2f &center, float diameter, const Color4f &color, bool isFilled )
: DaeEllipse{center,diameter,diameter,color,isFilled}

{
}

std::string DaeCircle::ToString()
{
	std::stringstream result{};

	result << "<DaeCircle";
	result << "\n";
	result << DaeShape::PropertiesToString();
	result << "/>" << "\n" << "\n";

	return result.str();
}




