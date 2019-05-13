#include <iostream>
#include <Eigen/Geometry>
#include <Eigen/Dense>
/**
Euler angle defination: zyx
Rotation matrix: C_body2ned
**/
Eigen::Quaterniond euler2quaternion(Eigen::Vector3d euler)
{
  double cr = cos(euler(0)/2);
  double sr = sin(euler(0)/2);
  double cp = cos(euler(1)/2);
  double sp = sin(euler(1)/2);
  double cy = cos(euler(2)/2);
  double sy = sin(euler(2)/2);
  Eigen::Quaterniond q;
  q.w() = cr*cp*cy + sr*sp*sy;
  q.x() = sr*cp*cy - cr*sp*sy;
  q.y() = cr*sp*cy + sr*cp*sy;
  q.z() = cr*cp*sy - sr*sp*cy;
  return q; 
}


Eigen::Matrix3d quaternion2mat(Eigen::Quaterniond q)
{
  Eigen::Matrix3d m;
  double a = q.w(), b = q.x(), c = q.y(), d = q.z();
  m << a*a + b*b - c*c - d*d, 2*(b*c - a*d), 2*(b*d+a*c),
       2*(b*c+a*d), a*a - b*b + c*c - d*d, 2*(c*d - a*b),
       2*(b*d - a*c), 2*(c*d+a*b), a*a-b*b - c*c + d*d;
  return m;
}

Eigen::Vector3d mat2euler(Eigen::Matrix3d m)
{ 
  double r = atan2(m(2, 1), m(2, 2));
  double p = asin(-m(2, 0));
  double y = atan2(m(1, 0), m(0, 0));
  Eigen::Vector3d rpy(r, p, y);
  return rpy;
}

Eigen::Quaterniond mat2quaternion(Eigen::Matrix3d m)
{
  //return euler2quaternion(mat2euler(m));
  Eigen::Quaterniond q;
  double a, b, c, d;
  a = sqrt(1 + m(0, 0) + m(1, 1) + m(2, 2))/2;
  b = (m(2, 1) - m(1, 2))/(4*a);
  c = (m(0, 2) - m(2, 0))/(4*a);
  d = (m(1, 0) - m(0, 1))/(4*a);
  q.w() = a; q.x() = b; q.y() = c; q.z() = d;
  return q;
}

Eigen::Matrix3d euler2mat(Eigen::Vector3d euler)
{
  double cr = cos(euler(0));
  double sr = sin(euler(0));
  double cp = cos(euler(1));
  double sp = sin(euler(1));
  double cy = cos(euler(2));
  double sy = sin(euler(2));
  Eigen::Matrix3d m;
  m << cp*cy,  -cr*sy + sr*sp*cy, sr*sy + cr*sp*cy, 
       cp*sy,  cr*cy + sr*sp*sy,  -sr*cy + cr*sp*sy, 
       -sp,    sr*cp,             cr*cp;
  return m;
}

Eigen::Vector3d quaternion2euler(Eigen::Quaterniond q)
{
  return mat2euler(quaternion2mat(q));
}