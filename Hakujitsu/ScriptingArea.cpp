#include "ScriptingArea.h"


#include <iostream>
void Script_Editor::OpenWindow()
{
	
	ImGui::Begin("Force Script");
	ImGui::SetWindowPos(ImVec2(0, 24),0);

	ForceEditor();
	
	ImGui::End();
}
 void Script_Editor::ForceEditor()
{
	
	
	 ImGui::SetWindowFontScale(0.9f); // Increase font size by 50%
	
	 if (Text_init == false)
	 {
		 editor.SetText(Force_str);
		 Text_init = true;
	 }
	
	
	TextEditor::LanguageDefinition lang = TextEditor::LanguageDefinition::CPlusPlus();
	//ImGui::InputTextMultiline("script", &Force_str, ImVec2(0, 0), 0, NULL, NULL);
	editor.SetReadOnly(false);
	editor.SetPalette(TextEditor::GetDarkPalette());
	editor.SetReadOnly(false);
	TextEditor::Palette palette;
	
	/*palette[(unsigned)TextEditor::PaletteIndex::Keyword] = ImColor(255, 255, 255);
	editor.SetPalette(palette);*/

	
	lang.mKeywords.insert("Force");
	lang.mKeywords.insert("class");
	lang.mKeywords.insert("def");
	lang.mKeywords.insert("elif");
	lang.mKeywords.insert("vec3");

	editor.SetLanguageDefinition(lang);

	Force_str = editor.GetText();




	editor.Render("MyTextEditor");
	

	

	//ImGui::SetWindowFontScale(1.0f); // Increase font size by 50%
	
	

	if (ImGui::Button("Run"))
	{
		
			// Initialize the Python interpreter (should be done only once)
	  Py_Initialize();

	  // Get a handle to the module object
	  PyObject* module = PyImport_AddModule("__main__");

	  // Get the value of the variable
	  const char* Force_c_str = Force_str.c_str();

	  PyRun_SimpleString(Force_c_str);

	  PyObject* p_var = PyObject_GetAttrString(module, "Force");

	  // Convert the Python object to a C integer
	  float x = PyFloat_AsDouble(PyObject_GetAttrString(p_var, "x"));
	  float y = PyFloat_AsDouble(PyObject_GetAttrString(p_var, "y"));
	  float z = PyFloat_AsDouble(PyObject_GetAttrString(p_var, "z"));

	  Force = glm::vec3(x, y, z);
	  std::cout << "x : " << Force.x << "\n";
	  std::cout << "y : " << Force.y << "\n";
	  std::cout << "z : " << Force.z << "\n";

	  // Decrement the reference count of the Python object
	  Py_DECREF(p_var);
			
	 

	  Py_Finalize();

		
		
    
	}
	
}