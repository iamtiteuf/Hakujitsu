#ifndef SCRIPTING_AREA_H
#define SCRIPTING_AREA_H
#include <Python.h>

#include "gui/imgui.h"
#include "gui/imgui_impl_glfw.h"
#include "gui/imgui_impl_opengl3.h"
#include "gui/imgui_stdlib.h"
#include "gui/imgui_internal.h"
#include "glm/glm.hpp"
#include "gui/TextEditor.h"




class Script_Editor
{
public:
	void OpenWindow();
    void ForceEditor();
	bool Text_init = false;
	glm::vec3 Force;
    TextEditor editor;
    TextEditor::LanguageDefinition lang = TextEditor::LanguageDefinition::CPlusPlus();

 
private:
    std::string Vector_Class = R"(
class vec3: 
    def __init__(self, x, y, z): 
        self.x = x
        self.y = y 
        self.z = z 
    def __add__(self, other) :
        if isinstance(other, vec3) :
            return vec3(self.x + other.x, self.y + other.y, self.z + other.z) 
        else :
            raise TypeError("Unsupported operand type.The operand should be a Vector3 object.")
    def __sub__(self, other) :
        if isinstance(other, vec3) :
            return vec3(self.x - other.x, self.y - other.y, self.z - other.z)
    def __mul__(self, other) :
        if isinstance(other, vec3) :
            return self.x * other.x + self.y * other.y + self.z * other.z
        elif isinstance(other, float) | isinstance(other, int) :
            return vec3(self.x * other, self.y * other, self.z * other)
        else :
            raise TypeError("Unsupported operand type.The operand should be a Vector3 object.")
    def __rmul__(self, other) :
        if isinstance(other, vec3) :
            return self.x * other.x + self.y * other.y + self.z * other.z
        elif isinstance(other, float) | isinstance(other, int) :
            return vec3(self.x * other, self.y * other, self.z * other)
        else :
            raise TypeError("Unsupported operand type. The operand should be a Vector3 object.")
    def mag(self) :
        return pow((self.x * self.x + self.y * self.y + self.z * self.z), 0.5)
    def normalize(self) :
        a = pow((self.x * self.x + self.y * self.y + self.z * self.z), 0.5)
        return vec3(self.x / a, self.y / a, self.z / a)
    def __truediv__(self, other) :
        if isinstance(other, float) | isinstance(other, int) :
           return vec3(self.x / other, self.y / other, self.z / other)
        else :
           return TypeError("Unsupported operand type. The operand should be a Vector3 object.")
)";
    std::string Code_Int = R"(
a = vec3(2,0,0) 
b = vec3(1,1,1)
c = a*b

print(c) 
)";
   
    std::string Force_str = Vector_Class + Code_Int;
   

   
        


};
#endif

