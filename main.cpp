#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <bits/stdc++.h>
#include <Shader/shader.h>
#include <Geometry/geometry.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <Camera/carena.h>
#include <Model/model.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//lightPos
glm::vec3 lightPos = 2.0f*glm::vec3(1.0,1.2,2.0);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("C:/Users/user/CLionProjects/opengl/resources/VertexShader.vert",
                     "C:/Users/user/CLionProjects/opengl/resources/FragmentShader.frag");

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 텍스처 wrapping/filtering 옵션 설정(현재 바인딩된 텍스처 객체에 대해)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 텍스처 로드 및 생성
    int width, height, nrChannels;
    unsigned char *data = stbi_load("C:/Users/user/CLionProjects/opengl/resources/Tile2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    float plane[] = {
            1.0,0.0,1.0,  0.0,1.0,0.0,  100.0f,100.0f,
            1.0,0.0,-1.0,  0.0,1.0,0.0,  100.0f,0.0f,
            -1.0,0.0,-1.0,  0.0,1.0,0.0,  0.0f,0.0f,
            -1.0,0.0,1.0,  0.0,1.0,0.0,  0.0f,100.0f
    };

    unsigned int indices[] = {
            0,1,3,
            1,2,3
    };

    unsigned int planeVAO;
    unsigned int VBO,EBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) , indices, GL_STATIC_DRAW);


    vector<vec3>sphere;

    for (int j=0; j<181; ++j) {
        for (int i=0; i<361; ++i) {
            //position
            sphere.push_back(
                    vec3(
                            sin(PI / 180.0 * j) * cos(PI / 180.0 * i),
                            sin(PI / 180.0 * j) * sin(PI / 180.0 * i),
                            cos(PI / 180.0 * j)
                    )
            );
            //normal
            sphere.push_back(
                    vec3(
                            sin(PI / 180.0 * j) * cos(PI / 180.0 * i),
                            sin(PI / 180.0 * j) * sin(PI / 180.0 * i),
                            cos(PI / 180.0 * j)
                    )
            );
        }
    }

    vector<unsigned int>indices2;
    for (int j=0; j<181; ++j) {
        for (int i=0; i<361; ++i) {
            indices2.push_back(i+360*j);
            indices2.push_back(i+360*j+1);
            indices2.push_back(i+360*(j+1));
            indices2.push_back(i+360*(j+1));
            indices2.push_back(i+360*j+1);
            indices2.push_back(i+360*(j+1)+1);
        }
    }

    unsigned int  objectVAO,objectVBO,objectEBO;
    glGenVertexArrays(1, &objectVAO);
    glGenBuffers(1, &objectVBO);
    glGenBuffers(1, &objectEBO);

    glBindVertexArray(objectVAO);

    glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
    glBufferData(GL_ARRAY_BUFFER, sphere.size() * sizeof(vec3), sphere.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(vec3), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*sizeof(vec3), (void*)(sizeof(vec3)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices2.size() * sizeof(unsigned int), indices2.data(), GL_STATIC_DRAW);




    //Model ourModel("C:/Users/user/Desktop/backpack/BackPack.obj");
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    //ourShader.setInt("ourTexture", 0);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(500.0f, 1.0f, 500.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);


        glBindTexture(GL_TEXTURE_2D, texture);
        ourShader.use();
        glBindVertexArray(planeVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(2.0,-0.999,2.0));
        ourShader.setMat4("model",model);
        glBindVertexArray(objectVAO);
        glDrawElements(GL_TRIANGLES, indices2.size(), GL_UNSIGNED_INT, 0);

        //Draw_Sphere(ourShader,1.0);
        //Draw_Sphere(ourShader,1.0f);
        //Draw_Ellipsoid(ourShader, 1.0f,0.8,1.5);
        //Draw_Torus(ourShader,0.2,0.5);
        //ourModel.Draw(ourShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
