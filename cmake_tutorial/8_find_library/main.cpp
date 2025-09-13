
#define GLEW_STATIC

#include  "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLuint const WIDTH = 800, HEIGHT = 600;

int main(int argc, char* argv[]) {
    GLFWwindow* window;
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Gears", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewExperimental = GL_TRUE;

    if(!glewInit() == GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    
    while(!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
        // Render    
		// Clear the colorbuffer    
		glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Draw a triangle */
		glBegin(GL_TRIANGLES);

		glColor3f(1.0, 0.0, 0.0);    // Red
		glVertex3f(0.0, 1.0, 0.0);

		glColor3f(0.0, 1.0, 0.0);    // Green
		glVertex3f(-1.0, -1.0, 0.0);

		glColor3f(0.0, 0.0, 1.0);    // Blue
		glVertex3f(1.0, -1.0, 0.0);

		glEnd();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    
    return EXIT_SUCCESS;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    std::cout << "key: " << key << std::endl;
    if(key == GLFW_KEY_ESCAPE || action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}