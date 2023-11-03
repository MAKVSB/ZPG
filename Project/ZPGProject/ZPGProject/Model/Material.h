#pragma once
#include "GlobalInclude.h"

// WARNING -> ORDER of element DOES matter
// This class must respect STD140 layout.
// "Each member of a uniform block is aligned to the base alignment for its type"
// In order to not implement uploading of each value separately but as a struct i chose to respect this layout here.
// Which in shortcut means that vec3 (12bytes) will be aligned to 16 bytes. Which is the same as vec4.
// The 4th value is not used inside shaders and can be used as metadata holder.

class Material
{
public:
	glm::vec4 r_a = glm::vec4(1);
	glm::vec4 r_d = glm::vec4(1);
	glm::vec4 r_s = glm::vec4(1);
	glm::vec4 objectColor = glm::vec4(0.285, 0.647, 0.812, 1);
};

