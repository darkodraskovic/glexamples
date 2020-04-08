#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

// Options for camera movement. An abstraction to stay away from window-system specific input methods
enum CameraMovement { CAM_FORWARD, CAM_BACKWARD, CAM_LEFT, CAM_RIGHT, CAM_UP, CAM_DOWN };

// Default camera values
namespace CameraDefaults
{
    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float SPEED       =  5.0f;
    const float SENSITIVITY =  0.1f;
    const float ZOOM        =  45.0f;
}

using namespace glm;
using namespace CameraDefaults;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
           vec3 up = vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix(int scrWidth, int scrHeight);
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    // Camera Attributes
    vec3 position_;
    vec3 front_;
    vec3 up_;
    vec3 right_;
    vec3 worldUp_;
    // Euler Angles
    float yaw_;
    float pitch_;
    // Camera options
    float movementSpeed_;
    float mouseSensitivity_;
    float zoom_;
    
private:
    void updateCameraVectors();
};
#endif
