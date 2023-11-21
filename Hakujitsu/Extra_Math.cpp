#include "Extra_Math.h"

namespace Extra_Math
{
	glm::vec2 math::ConvertToScreen(glm::vec3 worldPos)
	{
		// Transform the world position to clip space
		glm::vec4 clipPos = g_Projection * g_View * glm::vec4(worldPos, 1.0f);

		// Perform perspective divide
		glm::vec3 ndcPos = glm::vec3(clipPos) / clipPos.w;

		// Perform viewport transformation
		int windowWidth, windowHeight;
		glfwGetFramebufferSize(Main_Window, &windowWidth, &windowHeight);
		glm::vec2 screenPos;
		screenPos.x = (ndcPos.x + 1.0f) / 2.0f * windowWidth;
		screenPos.y = (1.0f - ndcPos.y) / 2.0f * windowHeight;

		return screenPos;
	}
	std::vector<glm::vec2> math::ReadPixelsAlongLine(std::vector<glm::vec2>Line,int amt)
	{
		std::vector<glm::vec2> points;
		
		float x1 = std::min(Line[0].x, Line[0].x);
		float x2 = std::max(Line[1].x, Line[1].x);
		float y1 = std::min(Line[0].y, Line[0].y);
		float y2 = std::max(Line[1].y, Line[1].y);
		float x_step = (x2 - x1)/amt;
		float y_step = (y2 - y1)/amt;

		int display_w, display_h;
		glfwGetFramebufferSize(Main_Window, &display_w, &display_h);

		for (int i = 0; i < amt; i++)
		{
			float x = ConvertToScreen(glm::vec3(x1 + x_step * i, y1 + y_step * i,1)).x;
			float y = ConvertToScreen(glm::vec3(x1 + x_step * i, y1 + y_step * i, 1)).y;
		
			unsigned char cixel[4];

			glPixelStorei(GL_PACK_ALIGNMENT, 4);
			glReadPixels((int)x, display_h - (int)y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &cixel);

			float val = 0.299f * cixel[0] + 0.587f * cixel[1] + 0.114f * cixel[2];;

			points.push_back(glm::vec2((x+y)/2, val));
		}
		return points;
	}
};

