// Example of:
// - More than one object (loaded from OBJ file)
// - Keyboard events (press A to start/stop animation)
// - Mouse events
// - Orthographic camera projection
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define GLM_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/loaders/FileLoader.h>

#include "src/objects/Mesh.h"
#include "src/camera/Arcball.h"
#include "src/objects/Terrain.h"
#include "src/objects/MainCharacter.h"
#include "src/camera/ThirdPersonCamera.h"
#include "src/shaders/StaticShader.hpp"
#include "src/engine/MasterRenderer.hpp"
#include "src/wrappers/MeshWrapper.hpp"
#include "src/managers/InputManager.hpp"
#include "src/objects/OtherCharacter.hpp"
#include "src/objects/Scene.hpp"
#include "src/gui/GuiRenderer.hpp"
#include "src/gui/Healthbar.hpp"
#include "src/objects/StreetLamp.hpp"
#include "src/skybox/SkyboxRenderer.hpp"
#include "src/managers/SceneManager.hpp"

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;

int keys[1024];
GLfloat fov = 45.0f;

ThirdPersonCamera *personCam = NULL;//nsThirdPersonCamera::ThirdPersonCamera(NULL, NULL);
std::list<Mesh> meshes;
InputManager *inputManager = NULL;

std::vector<MovableCharacter *> movableCharacters;
SceneManager *sceneManager;
int movableCharacterIndex = 0;
bool poll = true;
float lastFrameTime;
float delta;

Healthbar *healthbar;

void InitializeGeometry(GLuint program_id) {
    // Generate a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Setup geometry
    std::vector<GLfloat> vertex_buffer {
            // x, y
            1.0f, 1.0f,
            -1.0f, 1.0f,
            1.0f, -1.0f,
            -1.0f, -1.0f
    };

    // Generate a vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Setup vertex array lookup
    auto position_attrib = glGetAttribLocation(program_id, "Position");
    glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_attrib);

    // Generate another vertex buffer object for texture coordinates
    std::vector<GLfloat> texcoord_buffer {
            // u, v
            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat), texcoord_buffer.data(), GL_STATIC_DRAW);

    auto texcoord_attrib = glGetAttribLocation(program_id, "TexCoord");
    glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texcoord_attrib);
}


GLuint ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file) {
    // Create shaders
    auto vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    auto fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    auto result = GL_FALSE;
    auto info_length = 0;

    // Load shader code
    std::ifstream vertex_shader_stream(vertex_shader_file);
    std::string vertex_shader_code((std::istreambuf_iterator<char>(vertex_shader_stream)), std::istreambuf_iterator<char>());

    std::ifstream fragment_shader_stream(fragment_shader_file);
    std::string fragment_shader_code((std::istreambuf_iterator<char>(fragment_shader_stream)), std::istreambuf_iterator<char>());

    // Compile vertex shader
    std::cout << "Compiling Vertex Shader ..." << std::endl;
    auto vertex_shader_code_ptr = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &vertex_shader_code_ptr, NULL);
    glCompileShader(vertex_shader_id);

    // Check vertex shader log
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string vertex_shader_log((unsigned int)info_length, ' ');
        glGetShaderInfoLog(vertex_shader_id, info_length, NULL, &vertex_shader_log[0]);
        std::cout << vertex_shader_log << std::endl;
    }

    // Compile fragment shader
    std::cout << "Compiling Fragment Shader ..." << std::endl;
    auto fragment_shader_code_ptr = fragment_shader_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_shader_code_ptr, NULL);
    glCompileShader(fragment_shader_id);

    // Check fragment shader log
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string fragment_shader_log((unsigned long)info_length, ' ');
        glGetShaderInfoLog(fragment_shader_id, info_length, NULL, &fragment_shader_log[0]);
        std::cout << fragment_shader_log << std::endl;
    }

    // Create and link the program
    std::cout << "Linking Shader Program ..." << std::endl;
    auto program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glBindFragDataLocation(program_id, 0, "FragmentColor");
    glLinkProgram(program_id);

    // Check program log
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string program_log((unsigned long)info_length, ' ');
        glGetProgramInfoLog(program_id, info_length, NULL, &program_log[0]);
        std::cout << program_log << std::endl;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}

void UpdateProjection(GLuint program_id, bool is_perspective, glm::mat4 camera) {
    glUseProgram(program_id);

    // Create projection matrix
    glm::mat4 Projection;
    if (is_perspective) {
        // Perspective projection matrix (field of view, aspect ratio, near plane distance, far plane distance)
        Projection = glm::perspective(fov, GLfloat(SCREEN_WIDTH) / GLfloat(SCREEN_HEIGHT), 0.1f, 10000.0f);
    } else {
        // Orthographic projection matrix (left, right, bottom, top, near plane distance, far plane distance)
        Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1000.0f, 1000.0f);
    }

    // Send projection matrix value to program
    auto projection_uniform = glGetUniformLocation(program_id, "ProjectionMatrix");
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(Projection));

    // Send view matrix value to program
    auto view_uniform = glGetUniformLocation(program_id, "ViewMatrix");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(camera));
}

void InitializeGLState() {
    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

glm::vec3 toScreenCoord( double x, double y ) {
    glm::vec3 coord(0.0f);

    coord.x = (float) (2.0f * x - (float)SCREEN_HEIGHT) / (float)SCREEN_WIDTH;

    coord.y = (float) -(2.0f * y - (float)SCREEN_HEIGHT) / (float)SCREEN_WIDTH;

    /* Clamp it to border of the windows, comment these codes to allow rotation when cursor is not over window */
    coord.x = glm::clamp( coord.x, -1.0f, 1.0f );
    coord.y = glm::clamp( coord.y, -1.0f, 1.0f );

    float length_squared = coord.x * coord.x + coord.y * coord.y;
    if( length_squared <= 1.0 )
        coord.z = sqrt( 1.0f - length_squared );
    else
        coord = glm::normalize( coord );

    return coord;
}

int health = 100;
float oneHealthPortion = -1;
void OnKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    inputManager->onKeyPress(window, key, scancode, action, mods);

    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        sceneManager->changeScene(SceneType::BATTLE_SCEEN);
        poll = false;
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS && sceneManager->currentScene->sceneType == SceneType::BATTLE_SCEEN) {
        sceneManager->changeScene(SceneType::MAIN_SCEEN);
    }
}

// Mouse move event handler
void OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
    inputManager->cursorCallback(window, xpos, ypos);
}

void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
    inputManager->wheelCallBack(window, xoffset, yoffset);
}

void OnMouseButtonClick(GLFWwindow* window, int button, int action, int mods) {
    inputManager->mouseButtonCallback(window, button, action, mods);
}

float getCurrentTime() {
    return (float) (glfwGetTime() * 1000.0f);
}

void createLoadingScreen(const std::string &file_name, GLFWwindow *window) {

    auto program_id = ShaderProgram("src/shaders/vert_texture.glsl", "src/shaders/frag_texture.glsl");
    glUseProgram(program_id);
    InitializeGeometry(program_id);

    FileLoader::TGAFILE_t tgafile;
    FileLoader::LoadTGAFile(file_name.c_str(), &tgafile);

    std::vector<char> buffer(tgafile.imageData, tgafile.imageData + tgafile.imageWidth * tgafile.imageHeight * (tgafile.bitCount / 8));

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1500, 843, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    auto texture_attrib = glGetUniformLocation(program_id, "Texture");
    glUniform1i(texture_attrib, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glClearColor(.5f,.5f,.5f,0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw triangles using the program
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glfwSwapBuffers(window);
    //glfwPollEvents();
}

GLint loadTexture(const std::string &file) {
// Create new texture object
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

// Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    FileLoader::TGAFILE_t tgafile;
    FileLoader::LoadTGAFile(file.c_str(), &tgafile);

    std::vector<char> buffer(tgafile.imageData,
                             tgafile.imageData + tgafile.imageWidth * tgafile.imageHeight * (tgafile.bitCount / 8));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tgafile.imageWidth, tgafile.imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 buffer.data());

    return texture_id;
}

int main() {
    srand(time(NULL));

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }

    // Setup OpenGL context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Try to create a window
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pokemon 3D", glfwGetPrimaryMonitor(), NULL);
    if (window == NULL) {
        std::cerr << "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // get size of maximazed window
    glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Finalize window setup
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    if (!glewIsSupported("GL_VERSION_3_3")) {
        std::cerr << "Failed to initialize GLEW with OpenGL 3.3!" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    inputManager = new InputManager(SCREEN_WIDTH, SCREEN_HEIGHT);
    createLoadingScreen("models/textures/LoadingScreen.tga", window);
    sceneManager = new SceneManager(window, inputManager);

    // Add keyboard and mouse handlers
    glfwSetKeyCallback(window, OnKeyPress);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetScrollCallback(window, OnMouseScroll);
    glfwSetMouseButtonCallback(window, OnMouseButtonClick);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Hide mouse cursor

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        sceneManager->animate(delta);
        sceneManager->render();
        // Display result
        glfwSwapBuffers(window);

        float currentFrameTime = getCurrentTime();
        delta = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
    }

    // Clean up
    sceneManager->clean();
    glfwTerminate();

    return EXIT_SUCCESS;
}
