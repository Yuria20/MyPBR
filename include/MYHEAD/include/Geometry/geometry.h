#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader/shader.h>
#include <bits/stdc++.h>

using namespace std;
using namespace glm;

const float PI = 3.141597;

void Draw_Circle(Shader& shader, float radius)
{
    vector<vec3>circle;
    circle.push_back(vec3(0.0, 0.0, 0.0));

    for (int i = 0; i < 361; ++i) {
        circle.push_back(radius * vec3(cos(PI / 180 * i), sin(PI / 180 * i), 0.0));
    }

    vector<unsigned int>indices;

    for (int i = 0; i < 360; ++i) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, circle.size() * sizeof(vec3), circle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Draw_Ellipse(Shader& shader, float X_value, float Y_value)
{
    vector<vec3>circle;
    circle.push_back(vec3(0.0, 0.0, 0.0));

    for (int i = 0; i < 361; ++i) {
        circle.push_back(vec3(X_value * cos(PI / 180 * i), Y_value*sin(PI / 180 * i), 0.0));
    }

    vector<unsigned int>indices;

    for (int i = 0; i < 360; ++i) {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, circle.size() * sizeof(vec3), circle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Draw_Star(Shader &shader,float size)
{
    using namespace glm;
    
    mat4 rotation = mat4(1.0f);
    rotation = rotate(rotation, radians(72.0f), vec3(0.0,0.0,1.0f));

    glm::vec4 s1 = size*glm::vec4(cos(PI/2),sin(PI/2),0.0,1.0f);
    vec4 s2 = rotation*s1;
    vec4 s3 = rotation*s2; 
    vec4 s4 = rotation*s3; 
    vec4 s5 = rotation*s4; 
    float r = size*sin(9.0f/10*PI)/sin(radians(54.0f));
    vec4 t1 = vec4(0.0,-r*1.0f,0.0,1.0);
    vec4 t2 = rotation*t1;
    vec4 t3 = rotation*t2;
    vec4 t4 = rotation*t3;
    vec4 t5 = rotation*t4;

    std::vector<vec3>vertices;
    vertices.push_back(vec3(s1));
    vertices.push_back(vec3(s2));
    vertices.push_back(vec3(s3));
    vertices.push_back(vec3(s4));
    vertices.push_back(vec3(s5));
    vertices.push_back(vec3(t1));
    vertices.push_back(vec3(t2));
    vertices.push_back(vec3(t3));
    vertices.push_back(vec3(t4));
    vertices.push_back(vec3(t5));

    std::vector<unsigned int> indices = {
        0,9,6,
        1,5,7,
        2,6,8,
        3,7,9,
        4,5,8
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
}
#endif