#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Options for camera movement. An abstraction to stay away from window-system specific input methods
enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

// Default camera values
namespace cameraDefaults
{
    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float SPEED       =  5.0f;
    const float SENSITIVITY =  0.1f;
    const float ZOOM        =  45.0f;
}

using namespace glm;
using namespace cameraDefaults;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
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

    // Constructor with vectors

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
           vec3 up = vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) :
        front_(vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed_(SPEED),
        mouseSensitivity_(SENSITIVITY),
        zoom_(ZOOM)
        {
            position_ = position;
            worldUp_ = up;
            yaw_ = yaw;
            pitch_ = pitch;
            updateCameraVectors();
        }
    
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw, float pitch) :
        front_(vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed_(SPEED),
        mouseSensitivity_(SENSITIVITY),
        zoom_(ZOOM)
        {
            position_ = vec3(posX, posY, posZ);
            worldUp_ = vec3(upX, upY, upZ);
            yaw_ = yaw;
            pitch_ = pitch;
            updateCameraVectors();
        }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    mat4 GetViewMatrix()
        {
            return lookAt(position_, position_ + front_, up_);
        }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    mat4 GetProjectionMatrix(int scrWidth, int scrHeight)
        {
            return perspective(
                radians(zoom_),
                (float)scrWidth/(float)scrHeight, 0.1f, 100.0f);
        }
    
    // Processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraMovement direction, float deltaTime)
        {
            float velocity = movementSpeed_ * deltaTime;
            if (direction == FORWARD)
                position_ += front_ * velocity;
            if (direction == BACKWARD)
                position_ -= front_ * velocity;
            if (direction == LEFT)
                position_ -= right_ * velocity;
            if (direction == RIGHT)
                position_ += right_ * velocity;
            if (direction == UP)
                position_ += up_ * velocity;
            if (direction == DOWN)
                position_ -= up_ * velocity;
        }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
        {
            xoffset *= mouseSensitivity_;
            yoffset *= mouseSensitivity_;

            yaw_   += xoffset;
            pitch_ -= yoffset;

            // Make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch)
            {
                pitch_ = clamp(pitch_, -89.0f, 89.0f);
            }

            // Update front_, right_ and up_ Vectors using the updated Euler angles
            updateCameraVectors();
        }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
        {
            zoom_ -= yoffset;
            zoom_ = clamp(zoom_, 1.0f, 45.0f);
        }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
        {
            // Calculate the new front_ vector
            vec3 front;
            front.x = cos(radians(yaw_)) * cos(radians(pitch_));
            front.y = sin(radians(pitch_));
            front.z = sin(radians(yaw_)) * cos(radians(pitch_));
            front_ = normalize(front);
            // Also re-calculate the right_ and up_ vector
            right_ = normalize(cross(front_, worldUp_));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            up_    = normalize(cross(right_, front_));
        }
};
#endif
