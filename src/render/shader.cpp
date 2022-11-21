#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../../usrs.h"



shader::shader(const char* vertex_path, const char* fragment_path) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertex_path);
        fShaderFile.open(fragment_path);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. 编译着色器
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // 顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // 打印编译错误（如果有的话）
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 片段着色器也类似
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // 打印编译错误（如果有的话）
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // 着色器程序
    index = glCreateProgram();
    glAttachShader(index, vertex);
    glAttachShader(index, fragment);
    glLinkProgram(index);
    // 打印连接错误（如果有的话）
    glGetProgramiv(index, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(index, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void shader::enable() {
    glUseProgram(index);
}

void shader::setUniform(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(index, name.c_str()), (int)value);
}
void shader::setUniform(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(index, name.c_str()), value);
}
void shader::setUniform(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(index, name.c_str()), value);
}
void shader::setUniform(const std::string& name, float value1, float value2, float value3) const
{
    glUniform3f(glGetUniformLocation(index, name.c_str()), value1, value2, value3);
}
void shader::setUniform(const std::string& name, float value1, float value2, float value3, float value4) const
{
    glUniform4f(glGetUniformLocation(index, name.c_str()), value1, value2, value3, value4);
}
void shader::setUniform(const std::string& name, GLfloat* ptr) const
{
    glUniformMatrix4fv(glGetUniformLocation(index, name.c_str()), 1, GL_FALSE, ptr);
}



shader::operator GLuint() {
    return this->index;
}

void vabo::render(unsigned int textureID) {
    if (vaoid == 0 || vboid == 0 || vtx == -1) {
        return;
    }
    renderShader->enable();
    //glUseProgram(*renderShader);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(vaoid);
    if (eboid == 0)
        glDrawArrays(graphUnit, 0, vtx);
    else {
        glDrawElements(graphUnit, rtx, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}

// vbo mode
vabo::vabo(float vertices[], int vtcsize, int vtxnum, shader* shad, unsigned int vboMode, unsigned int gut, int propernum) {
    //usrlib->logPrint("Create vabo ");
    eboid = 0;
    renderShader = shad;
    vtx = vtxnum;
    rtx = 0;
    graphUnit = gut;
    glGenVertexArrays(1, &vaoid);
    glGenBuffers(1, &vboid);
    usrlib->windowh->delvao.push_back(this->vaoid);
    usrlib->windowh->delvbo.push_back(this->vboid);

    glBindVertexArray(vaoid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glBufferData(GL_ARRAY_BUFFER, vtcsize, vertices, vboMode);
    for (re i = 0; i < propernum; i++) {
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3 * propernum * sizeof(float), (void*)(i * 3 * sizeof(float)));
        glEnableVertexAttribArray(i);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
// ebo mode
vabo::vabo(float vertices[], int vtcsize, unsigned int indices[], int indsize, int vtxnum, shader* shad, unsigned int vboMode, unsigned int gut, int propernum) {
    renderShader = shad;
    rtx = indsize / sizeof(unsigned int);
    vtx = vtxnum;
    graphUnit = gut;
    glGenVertexArrays(1, &vaoid);
    glGenBuffers(1, &vboid);
    glGenBuffers(1, &eboid);
    usrlib->windowh->delvao.push_back(vaoid);
    usrlib->windowh->delvbo.push_back(vboid);
    usrlib->windowh->delvbo.push_back(eboid);
    glBindVertexArray(vaoid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glBufferData(GL_ARRAY_BUFFER, vtcsize, vertices, vboMode);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsize, indices, vboMode);
    for (re i = 0; i < propernum; i++) {
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3 * propernum * sizeof(float), (void*)(i * 3 * sizeof(float)));
        glEnableVertexAttribArray(i);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// copy constructor
vabo::vabo(vabo& from) {
    this->vtx = from.vtx;
    this->vaoid = from.vaoid;
    this->vboid = from.vboid;
    this->graphUnit = from.graphUnit;
    this->renderShader = from.renderShader;
    this->eboid = from.eboid;
}

void vabo::updateBuffer(float vertices[], int vtcsize, unsigned int vboMode) {
    if (vtx == -1) {
        return;
   }
    glBindVertexArray(vaoid);
    glBindBuffer(GL_ARRAY_BUFFER, vboid);
    glBufferData(GL_ARRAY_BUFFER, vtcsize, vertices, vboMode);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}