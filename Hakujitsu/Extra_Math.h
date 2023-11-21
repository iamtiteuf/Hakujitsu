#ifndef EXTRA_MATH_H
#define EXTRA_MATH_H
#include "Global_Variables.h"

namespace Extra_Math
{
	
	class math
	{
	public:
		static glm::vec2 ConvertToScreen(glm::vec3 worldPos);
		static std::vector<glm::vec2>ReadPixelsAlongLine(std::vector<glm::vec2>Line, int amt);
	};


};
#endif


