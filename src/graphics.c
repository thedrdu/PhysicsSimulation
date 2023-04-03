// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <glfw3.h>
// #include "main.h"

// void drawCircle(float x, float y, float radius, GLFWwindow* window) {
//     int i;
//     int triangleAmount = 50; // number of triangles used to draw circle
//     GLfloat twicePi = 2.0f * M_PI;
    
//     // Get the aspect ratio of the window
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     float aspect_ratio = (float)width / (float)height;

//     // Create vertex array
//     GLfloat vertices[(triangleAmount+2)*2];
//     vertices[0] = x / aspect_ratio;
//     vertices[1] = y;
//     for(i = 1; i <= triangleAmount+1; i++) {
//         vertices[i*2] = (x / aspect_ratio) + (radius * cos(i * twicePi / triangleAmount));
//         vertices[i*2+1] = y + (radius * sin(i * twicePi / triangleAmount));
//     }

//     // Create VBO and upload vertex data
//     GLuint vbo;
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // Bind VBO and specify vertex format
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
//     glEnableVertexAttribArray(0);

//     // Draw circle
//     glDrawArrays(GL_TRIANGLE_FAN, 0, triangleAmount+2);

//     // Cleanup
//     glDisableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glDeleteBuffers(1, &vbo);
// }