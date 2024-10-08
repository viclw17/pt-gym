#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"

#define _USE_MATH_DEFINES
#include <math.h> // M_PI

inline float deg2rad(float deg) {
  return deg / 180 * M_PI;
}


class Camera {
  public:
    Vec3 camPos;
    Vec3 camForward;
    Vec3 camRight;
    Vec3 camUp;

    Camera(const Vec3& _camPos, const Vec3& _camForward) : camPos(_camPos), camForward(normalize(_camForward)) {
      camRight = cross(camForward, Vec3(0, 1, 0));
      camUp = cross(camRight, camForward);

      std::cout << "camPos: " << camPos << std::endl;
      std::cout << "camForward: " << camForward << std::endl;
      std::cout << "camRight: " << camRight << std::endl;
      std::cout << "camUp: " << camUp << std::endl;
    };

    virtual Ray getRay(float u, float v) const = 0;
};


class PinholeCamera : public Camera {
  public:
    float fov;
    float f;

    PinholeCamera(const Vec3& _camPos, const Vec3& _camForward, float _fov) : Camera(_camPos, _camForward), fov(deg2rad(_fov)) {
      f = 1 / std::tan(fov/2);
    };

    Ray getRay(float u, float v) const {
      Vec3 pinholePos = camPos + f*camForward;
      Vec3 sensorPos = camPos + u*camRight + v*camUp;
      return Ray(sensorPos, normalize(pinholePos - sensorPos));
    };
};
#endif
