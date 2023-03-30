#ifndef ROS2_lidar__POINT_OS_HPP_
#define ROS2_lidar__POINT_OS_HPP_

#define PCL_NO_PRECOMPILE
#include "pcl/point_types.h"
#include <Eigen/Eigen>

namespace point_os
{

/**
 * @struct point_os::PointOS
 * @brief The Point template for PCL to hold the information for
 * publishing in ROS2.
 */
struct EIGEN_ALIGN16 PointOS
{
  PCL_ADD_POINT4D;
  float intensity;
  uint32_t t;
  uint16_t reflectivity;
  uint8_t ring;
  uint16_t noise;
  uint32_t range;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  /**
   * @brief A factory to create the structure given a set of information
   * @param x position in m
   * @param y position in m
   * @param z position in m
   * @param intensity Intensity value from reading
   * @param t time in ns
   * @param reflectivity Reflectivity value from reading
   * @param ring The ring ID the measurement came from
   * @param column The column of the reading in the ring
   * @param noise Noise value from reading
   * @param range Range value from reading
   */
  static inline PointOS make(float x, float y, float z, float intensity,uint32_t t, uint16_t reflectivity, uint8_t ring, uint8_t col,uint16_t noise, uint32_t range)
  {
    return {x, y, z, 0.0, intensity, t, reflectivity, ring, noise, range};
  }
};

}  // namespace point_os

/* *INDENT-OFF* */
POINT_CLOUD_REGISTER_POINT_STRUCT(point_os::PointOS,
  (float, x, x)
  (float, y, y)
  (float, z, z)
  (float, intensity, intensity)
  (std::uint32_t, t, t)
  (std::uint16_t, reflectivity, reflectivity)
  (std::uint8_t, ring, ring)
  (std::uint16_t, noise, noise)
  (std::uint32_t, range, range)
)
/* *INDENT-ON* */

#endif  // ROS2_lidar__POINT_OS_HPP_
