#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory> 
#include "core/point.hpp"
#include "utils/common_utils.hpp"
#include "convex_hull/convex_hull_gift_wrapping.hpp"
#include "convex_hull/convex_hull_incremental.hpp"
#include "convex_hull/convex_hull_brute_force.hpp"
#include "convex_hull/convex_hull_solver.hpp"
#include "../includes/shaders/ConvexHullShader.h"

int main() {
    // Initialize GLFW (Graphics Library Framework)
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Create an OpenGL window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    //This sets the created OpenGL context as the current one for this thread.
    //Without this, OpenGL function calls will not work.
    glfwMakeContextCurrent(window);

    glewExperimental = true; // Enables the use of modern OpenGL features
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    ConvexHullShader shader("../includes/shaders/convex_hull_vertex_shader.glsl", "../includes/shaders/convex_hull_fragment_shader.glsl");

    auto points = utils::getRandomPoints(10, -0.95f, 0.95f, -0.95f, 0.95f, 1.0f, 1.0f, false);
    /*auto points = std::vector<Point3D<float>> {
        Point3D<float>(0.0f, 0.0f, 1.0f),
        Point3D<float>(0.1f, 0.3f, 1.0f),
        Point3D<float>(0.2f, 0.2f, 1.0f),
        Point3D<float>(0.3f, 0.3f, 1.0f),
        Point3D<float>(0.4f, 0.0f, 1.0f)
    };*/
    auto flattenedPoints = utils::flatten(points);
    auto convexHullSolver = algorithms::convex_hull::ConvexHullSolver<float>(std::make_unique<algorithms::convex_hull::ConvexHullGiftWrapping<float>>());
    auto hull = convexHullSolver.compute(points);
    auto flattenedHull = utils::flatten(hull);
    

    // Generate and bind VBO
    GLuint pointsVAO, pointsVBO;
    glGenVertexArrays(1, &pointsVAO);
    glGenBuffers(1, &pointsVBO);
    // Bind VAO
    glBindVertexArray(pointsVAO);
    // Bind and set VBO
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, flattenedPoints.size() * sizeof(float), flattenedPoints.data(), GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Generate and bind VBO
    GLuint linesVAO, linesVBO;
    glGenVertexArrays(1, &linesVAO);
    glGenBuffers(1, &linesVBO);
    // Bind VAO
    glBindVertexArray(linesVAO);
    // Bind and set VBO
    glBindBuffer(GL_ARRAY_BUFFER, linesVBO);
    glBufferData(GL_ARRAY_BUFFER, flattenedHull.size() * sizeof(float), flattenedHull.data(), GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set the clear color to black
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        shader.Use();
        glBindVertexArray(pointsVAO);
        glDrawArrays(GL_POINTS, 0, flattenedPoints.size() / 3);  // Draw all points

        glBindVertexArray(linesVAO);
        glDrawArrays(GL_LINE_LOOP, 0, flattenedHull.size() / 3);  // Draw all lines

        glfwSwapBuffers(window);  // Swap the front and back buffers
        glfwPollEvents();         // Process events (keyboard, mouse, etc.)
    }



    glfwTerminate();
    return 0;

}