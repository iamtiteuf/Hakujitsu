#include "Shaders.h"
void Shaders::Create_Shaders(const char* vert, const char* frag)
{
    std::ifstream vshaderfile(vert);
    if (!vshaderfile.is_open()) {
        std::cerr << "Failed to open vertex shader file: " << vert << "\n";
        return;
    }
    std::stringstream vshaderstream;
    vshaderstream << vshaderfile.rdbuf();
    vshaderfile.close();
    std::string vertexSource = vshaderstream.str();
    const GLchar* vertexSourceCode = vertexSource.c_str();

    std::ifstream fshaderfile(frag);
    if (!fshaderfile.is_open()) {
        std::cerr << "Failed to open fragment shader file: " << frag << "\n";
        return;
    }
    std::stringstream fshaderstream;
    fshaderstream << fshaderfile.rdbuf();
    fshaderfile.close();
    std::string fragmentSource = fshaderstream.str();
    const GLchar* fragmentSourceCode = fragmentSource.c_str();

    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vertexSourceCode, nullptr);
    glCompileShader(vertexshader);

    GLint success;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(vertexshader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile vertex shader: " << infoLog << "\n";
        return;
    }

    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &fragmentSourceCode, nullptr);
    glCompileShader(fragmentshader);

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(fragmentshader, 512, nullptr, infoLog);
        std::cerr << "Failed to compile fragment shader: " << infoLog << "\n";
        return;
    }

    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);
    glLinkProgram(shaderprogram);

    glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderprogram, 512, nullptr, infoLog);
        std::cerr << "Failed to link shader program: " << infoLog << "\n";
        return;
    }

    if (shaderprogram != 0) {
        std::cout << "Program created\n";
    }
    else {
        std::cout << "Program not created\n";
    }

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
}
Shaders::~Shaders()
{
	glDeleteProgram(shaderprogram);
}