#include "point_plane.hpp"

#include <ipc/utils/eigen_ext.hpp>
#include <Eigen/Geometry>

namespace ipc {

double point_plane_distance(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& origin,
    const Eigen::Ref<const Eigen::Vector3d>& normal)
{
    const double point_to_plane = (p - origin).dot(normal);
    return point_to_plane * point_to_plane / normal.squaredNorm();
}

double point_plane_distance(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& t0,
    const Eigen::Ref<const Eigen::Vector3d>& t1,
    const Eigen::Ref<const Eigen::Vector3d>& t2)
{
    return point_plane_distance(p, t0, (t1 - t0).cross(t2 - t0));
}

Eigen::Vector3d point_plane_distance_gradient(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& origin,
    const Eigen::Ref<const Eigen::Vector3d>& normal)
{
    return (2 / normal.squaredNorm()) * (p - origin).dot(normal) * normal;
}

Vector12d point_plane_distance_gradient(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& t0,
    const Eigen::Ref<const Eigen::Vector3d>& t1,
    const Eigen::Ref<const Eigen::Vector3d>& t2)
{
    Vector12d grad;
    autogen::point_plane_distance_gradient(
        p[0], p[1], p[2], t0[0], t0[1], t0[2], t1[0], t1[1], t1[2], t2[0],
        t2[1], t2[2], grad.data());
    return grad;
}

Eigen::Matrix3d point_plane_distance_hessian(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& origin,
    const Eigen::Ref<const Eigen::Vector3d>& normal)
{
    return 2 / normal.squaredNorm() * normal * normal.transpose();
}

Matrix12d point_plane_distance_hessian(
    const Eigen::Ref<const Eigen::Vector3d>& p,
    const Eigen::Ref<const Eigen::Vector3d>& t0,
    const Eigen::Ref<const Eigen::Vector3d>& t1,
    const Eigen::Ref<const Eigen::Vector3d>& t2)
{
    Matrix12d hess;
    autogen::point_plane_distance_hessian(
        p[0], p[1], p[2], t0[0], t0[1], t0[2], t1[0], t1[1], t1[2], t2[0],
        t2[1], t2[2], hess.data());
    return hess;
}

namespace autogen {

    // This function was generated by the Symbolic Math Toolbox version 8.3.
    // 10-Jun-2019 17:42:16
    void point_plane_distance_gradient(
        double v01,
        double v02,
        double v03,
        double v11,
        double v12,
        double v13,
        double v21,
        double v22,
        double v23,
        double v31,
        double v32,
        double v33,
        double g[12])
    {
        double t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t32,
            t33, t34, t43, t45, t44, t46;

        t11 = -v11 + v01;
        t12 = -v12 + v02;
        t13 = -v13 + v03;
        t14 = -v21 + v11;
        t15 = -v22 + v12;
        t16 = -v23 + v13;
        t17 = -v31 + v11;
        t18 = -v32 + v12;
        t19 = -v33 + v13;
        t20 = -v31 + v21;
        t21 = -v32 + v22;
        t22 = -v33 + v23;
        t32 = t14 * t18 + -(t15 * t17);
        t33 = t14 * t19 + -(t16 * t17);
        t34 = t15 * t19 + -(t16 * t18);
        t43 = 1.0 / ((t32 * t32 + t33 * t33) + t34 * t34);
        t45 = (t13 * t32 + t11 * t34) + -(t12 * t33);
        t44 = t43 * t43;
        t46 = t45 * t45;
        g[0] = t34 * t43 * t45 * 2.0;
        g[1] = t33 * t43 * t45 * -2.0;
        g[2] = t32 * t43 * t45 * 2.0;
        t45 *= t43;
        g[3] = -t44 * t46 * (t21 * t32 * 2.0 + t22 * t33 * 2.0)
            - t45 * ((t34 + t12 * t22) - t13 * t21) * 2.0;
        t43 = t44 * t46;
        g[4] = t43 * (t20 * t32 * 2.0 - t22 * t34 * 2.0)
            + t45 * ((t33 + t11 * t22) - t13 * t20) * 2.0;
        g[5] = t43 * (t20 * t33 * 2.0 + t21 * t34 * 2.0)
            - t45 * ((t32 + t11 * t21) - t12 * t20) * 2.0;
        g[6] = t45 * (t12 * t19 - t13 * t18) * 2.0
            + t43 * (t18 * t32 * 2.0 + t19 * t33 * 2.0);
        g[7] = t45 * (t11 * t19 - t13 * t17) * -2.0
            - t43 * (t17 * t32 * 2.0 - t19 * t34 * 2.0);
        g[8] = t45 * (t11 * t18 - t12 * t17) * 2.0
            - t43 * (t17 * t33 * 2.0 + t18 * t34 * 2.0);
        g[9] = t45 * (t12 * t16 - t13 * t15) * -2.0
            - t43 * (t15 * t32 * 2.0 + t16 * t33 * 2.0);
        g[10] = t45 * (t11 * t16 - t13 * t14) * 2.0
            + t43 * (t14 * t32 * 2.0 - t16 * t34 * 2.0);
        g[11] = t45 * (t11 * t15 - t12 * t14) * -2.0
            + t43 * (t14 * t33 * 2.0 + t15 * t34 * 2.0);
    }

    // This function was generated by the Symbolic Math Toolbox version 8.3.
    // 10-Jun-2019 17:42:25
    void point_plane_distance_hessian(
        double v01,
        double v02,
        double v03,
        double v11,
        double v12,
        double v13,
        double v21,
        double v22,
        double v23,
        double v31,
        double v32,
        double v33,
        double H[144])
    {
        double t11, t12, t13, t18, t20, t22, t23, t24, t25, t26, t27, t28, t65,
            t66, t67, t68, t69, t70, t71, t77, t85, t86, t90, t94, t95, t99,
            t103, t38, t39, t40, t41, t42, t43, t44, t45, t46, t72, t73, t75,
            t78, t80, t82, t125, t126, t127, t128, t129, t130, t131, t133, t135,
            t149, t150, t151, t189, t190, t191, t192, t193, t194, t195, t196,
            t197, t198, t199, t200, t202, t205, t203, t204, t206, t241, t309,
            t310, t312, t313, t314, t315, t316, t317, t318, t319, t321, t322,
            t323, t324, t325, t261, t262, t599, t600, t602, t605, t609, t610,
            t611, t613, t615, t616, t621, t622, t623, t625, t645, t646_tmp,
            t646, t601, t603, t604, t606, t607, t608, t612, t614, t617, t618,
            t619, t620, t624, t626, t627, t628, t629, t630, t631, t632, t633,
            t634, t635, t636, t637, t638;

        t11 = -v11 + v01;
        t12 = -v12 + v02;
        t13 = -v13 + v03;
        t18 = -v21 + v11;
        t20 = -v22 + v12;
        t22 = -v23 + v13;
        t23 = -v31 + v11;
        t24 = -v32 + v12;
        t25 = -v33 + v13;
        t26 = -v31 + v21;
        t27 = -v32 + v22;
        t28 = -v33 + v23;
        t65 = t18 * t24;
        t66 = t20 * t23;
        t67 = t18 * t25;
        t68 = t22 * t23;
        t69 = t20 * t25;
        t70 = t22 * t24;
        t71 = t18 * t23 * 2.0;
        t77 = t20 * t24 * 2.0;
        t85 = t22 * t25 * 2.0;
        t86 = t18 * t26 * 2.0;
        t90 = t20 * t27 * 2.0;
        t94 = t22 * t28 * 2.0;
        t95 = t23 * t26 * 2.0;
        t99 = t24 * t27 * 2.0;
        t103 = t25 * t28 * 2.0;
        t38 = t18 * t18 * 2.0;
        t39 = t20 * t20 * 2.0;
        t40 = t22 * t22 * 2.0;
        t41 = t23 * t23 * 2.0;
        t42 = t24 * t24 * 2.0;
        t43 = t25 * t25 * 2.0;
        t44 = t26 * t26 * 2.0;
        t45 = t27 * t27 * 2.0;
        t46 = t28 * t28 * 2.0;
        t72 = t65 * 2.0;
        t73 = t66 * 2.0;
        t75 = t67 * 2.0;
        t78 = t68 * 2.0;
        t80 = t69 * 2.0;
        t82 = t70 * 2.0;
        t125 = t11 * t20 + -(t12 * t18);
        t126 = t11 * t22 + -(t13 * t18);
        t127 = t12 * t22 + -(t13 * t20);
        t128 = t11 * t24 + -(t12 * t23);
        t129 = t11 * t25 + -(t13 * t23);
        t130 = t12 * t25 + -(t13 * t24);
        t131 = t65 + -t66;
        t133 = t67 + -t68;
        t135 = t69 + -t70;
        t149 = t131 * t131;
        t150 = t133 * t133;
        t151 = t135 * t135;
        t189 = (t11 * t27 + -(t12 * t26)) + t131;
        t190 = (t11 * t28 + -(t13 * t26)) + t133;
        t191 = (t12 * t28 + -(t13 * t27)) + t135;
        t192 = t20 * t131 * 2.0 + t22 * t133 * 2.0;
        t193 = t18 * t133 * 2.0 + t20 * t135 * 2.0;
        t194 = t24 * t131 * 2.0 + t25 * t133 * 2.0;
        t195 = t23 * t133 * 2.0 + t24 * t135 * 2.0;
        t196 = t27 * t131 * 2.0 + t28 * t133 * 2.0;
        t197 = t26 * t133 * 2.0 + t27 * t135 * 2.0;
        t198 = t18 * t131 * 2.0 + -(t22 * t135 * 2.0);
        t199 = t23 * t131 * 2.0 + -(t25 * t135 * 2.0);
        t200 = t26 * t131 * 2.0 + -(t28 * t135 * 2.0);
        t202 = 1.0 / ((t149 + t150) + t151);
        t205 = (t13 * t131 + t11 * t135) + -(t12 * t133);
        t203 = t202 * t202;
        t204 = pow(t202, 3.0);
        t206 = t205 * t205;
        t241 = t131 * t135 * t202 * 2.0;
        t309 = t11 * t202 * t205 * 2.0;
        t310 = t12 * t202 * t205 * 2.0;
        t13 = t13 * t202 * t205 * 2.0;
        t312 = (-v21 + v01) * t202 * t205 * 2.0;
        t313 = (-v22 + v02) * t202 * t205 * 2.0;
        t314 = (-v23 + v03) * t202 * t205 * 2.0;
        t315 = (-v31 + v01) * t202 * t205 * 2.0;
        t316 = t18 * t202 * t205 * 2.0;
        t317 = (-v32 + v02) * t202 * t205 * 2.0;
        t318 = t20 * t202 * t205 * 2.0;
        t319 = (-v33 + v03) * t202 * t205 * 2.0;
        t11 = t22 * t202 * t205 * 2.0;
        t321 = t23 * t202 * t205 * 2.0;
        t322 = t24 * t202 * t205 * 2.0;
        t323 = t25 * t202 * t205 * 2.0;
        t324 = t26 * t202 * t205 * 2.0;
        t325 = t27 * t202 * t205 * 2.0;
        t12 = t28 * t202 * t205 * 2.0;
        t261 = -(t131 * t133 * t202 * 2.0);
        t262 = -(t133 * t135 * t202 * 2.0);
        t599 = t130 * t135 * t202 * 2.0 + t135 * t194 * t203 * t205 * 2.0;
        t600 = -(t125 * t131 * t202 * 2.0) + t131 * t193 * t203 * t205 * 2.0;
        t602 = t129 * t133 * t202 * 2.0 + t133 * t199 * t203 * t205 * 2.0;
        t605 = -(t131 * t189 * t202 * 2.0) + t131 * t197 * t203 * t205 * 2.0;
        t609 =
            (t127 * t133 * t202 * 2.0 + -t11) + t133 * t192 * t203 * t205 * 2.0;
        t610 =
            (t126 * t135 * t202 * 2.0 + t11) + t135 * t198 * t203 * t205 * 2.0;
        t611 = (t130 * t131 * t202 * 2.0 + -t322)
            + t131 * t194 * t203 * t205 * 2.0;
        t613 = (t126 * t131 * t202 * 2.0 + -t316)
            + t131 * t198 * t203 * t205 * 2.0;
        t615 = (-(t125 * t135 * t202 * 2.0) + -t318)
            + t135 * t193 * t203 * t205 * 2.0;
        t616 = (-(t128 * t133 * t202 * 2.0) + -t321)
            + t133 * t195 * t203 * t205 * 2.0;
        t621 =
            (t133 * t191 * t202 * 2.0 + -t12) + t133 * t196 * t203 * t205 * 2.0;
        t622 =
            (t135 * t190 * t202 * 2.0 + t12) + t135 * t200 * t203 * t205 * 2.0;
        t623 = (t131 * t190 * t202 * 2.0 + -t324)
            + t131 * t200 * t203 * t205 * 2.0;
        t625 = (-(t135 * t189 * t202 * 2.0) + -t325)
            + t135 * t197 * t203 * t205 * 2.0;
        t645 = ((((t127 * t129 * t202 * 2.0 + -t13)
                  + (t72 + -(t66 * 4.0)) * t203 * t206)
                 + t129 * t192 * t203 * t205 * 2.0)
                + t127 * t199 * t203 * t205 * 2.0)
            + t192 * t199 * t204 * t206 * 2.0;
        t646_tmp = t203 * t206;
        t646 =
            ((((t126 * t130 * t202 * 2.0 + t13) + t646_tmp * (t73 - t65 * 4.0))
              + t126 * t194 * t203 * t205 * 2.0)
             + t130 * t198 * t203 * t205 * 2.0)
            + t194 * t198 * t204 * t206 * 2.0;
        t601 = t128 * t131 * t202 * 2.0 + -(t131 * t195 * t203 * t205 * 2.0);
        t603 = -(t127 * t135 * t202 * 2.0) + -(t135 * t192 * t203 * t205 * 2.0);
        t604 = -(t126 * t133 * t202 * 2.0) + -(t133 * t198 * t203 * t205 * 2.0);
        t606 = -(t135 * t191 * t202 * 2.0) + -(t135 * t196 * t203 * t205 * 2.0);
        t607 = -(t133 * t190 * t202 * 2.0) + -(t133 * t200 * t203 * t205 * 2.0);
        t608 = (t125 * t133 * t202 * 2.0 + t316)
            + -(t133 * t193 * t203 * t205 * 2.0);
        t612 = (t128 * t135 * t202 * 2.0 + t322)
            + -(t135 * t195 * t203 * t205 * 2.0);
        t614 = (-(t127 * t131 * t202 * 2.0) + t318)
            + -(t131 * t192 * t203 * t205 * 2.0);
        t617 = (-(t130 * t133 * t202 * 2.0) + t323)
            + -(t133 * t194 * t203 * t205 * 2.0);
        t618 = (-(t129 * t131 * t202 * 2.0) + t321)
            + -(t131 * t199 * t203 * t205 * 2.0);
        t619 = (-(t129 * t135 * t202 * 2.0) + -t323)
            + -(t135 * t199 * t203 * t205 * 2.0);
        t620 = (t133 * t189 * t202 * 2.0 + t324)
            + -(t133 * t197 * t203 * t205 * 2.0);
        t624 = (-(t131 * t191 * t202 * 2.0) + t325)
            + -(t131 * t196 * t203 * t205 * 2.0);
        t626 = (((t125 * t127 * t202 * 2.0 + t18 * t22 * t203 * t206 * 2.0)
                 + t125 * t192 * t203 * t205 * 2.0)
                + -(t127 * t193 * t203 * t205 * 2.0))
            + -(t192 * t193 * t204 * t206 * 2.0);
        t627 = (((t128 * t130 * t202 * 2.0 + t23 * t25 * t203 * t206 * 2.0)
                 + t128 * t194 * t203 * t205 * 2.0)
                + -(t130 * t195 * t203 * t205 * 2.0))
            + -(t194 * t195 * t204 * t206 * 2.0);
        t628 = (((-(t125 * t126 * t202 * 2.0) + t20 * t22 * t203 * t206 * 2.0)
                 + t126 * t193 * t203 * t205 * 2.0)
                + -(t125 * t198 * t203 * t205 * 2.0))
            + t193 * t198 * t204 * t206 * 2.0;
        t629 = (((-(t128 * t129 * t202 * 2.0) + t24 * t25 * t203 * t206 * 2.0)
                 + t129 * t195 * t203 * t205 * 2.0)
                + -(t128 * t199 * t203 * t205 * 2.0))
            + t195 * t199 * t204 * t206 * 2.0;
        t630 = (((-(t126 * t127 * t202 * 2.0) + t18 * t20 * t203 * t206 * 2.0)
                 + -(t126 * t192 * t203 * t205 * 2.0))
                + -(t127 * t198 * t203 * t205 * 2.0))
            + -(t192 * t198 * t204 * t206 * 2.0);
        t631 = (((-(t129 * t130 * t202 * 2.0) + t23 * t24 * t203 * t206 * 2.0)
                 + -(t129 * t194 * t203 * t205 * 2.0))
                + -(t130 * t199 * t203 * t205 * 2.0))
            + -(t194 * t199 * t204 * t206 * 2.0);
        t632 = (((-(t125 * t128 * t202 * 2.0) + (t71 + t77) * t203 * t206)
                 + t128 * t193 * t203 * t205 * 2.0)
                + t125 * t195 * t203 * t205 * 2.0)
            + -(t193 * t195 * t204 * t206 * 2.0);
        t633 = (((-(t127 * t130 * t202 * 2.0) + (t77 + t85) * t203 * t206)
                 + -(t130 * t192 * t203 * t205 * 2.0))
                + -(t127 * t194 * t203 * t205 * 2.0))
            + -(t192 * t194 * t204 * t206 * 2.0);
        t634 = (((-(t126 * t129 * t202 * 2.0) + (t71 + t85) * t203 * t206)
                 + -(t129 * t198 * t203 * t205 * 2.0))
                + -(t126 * t199 * t203 * t205 * 2.0))
            + -(t198 * t199 * t204 * t206 * 2.0);
        t635 = (((t127 * t191 * t202 * 2.0 + -((t90 + t94) * t203 * t206))
                 + t127 * t196 * t203 * t205 * 2.0)
                + t191 * t192 * t203 * t205 * 2.0)
            + t192 * t196 * t204 * t206 * 2.0;
        t636 = (((-(t128 * t189 * t202 * 2.0) + (t95 + t99) * t203 * t206)
                 + t128 * t197 * t203 * t205 * 2.0)
                + t189 * t195 * t203 * t205 * 2.0)
            + -(t195 * t197 * t204 * t206 * 2.0);
        t637 = (((t125 * t189 * t202 * 2.0 + -((t86 + t90) * t203 * t206))
                 + -(t125 * t197 * t203 * t205 * 2.0))
                + -(t189 * t193 * t203 * t205 * 2.0))
            + t193 * t197 * t204 * t206 * 2.0;
        t638 = (((-(t130 * t191 * t202 * 2.0) + (t99 + t103) * t203 * t206)
                 + -(t130 * t196 * t203 * t205 * 2.0))
                + -(t191 * t194 * t203 * t205 * 2.0))
            + -(t194 * t196 * t204 * t206 * 2.0);
        t86 = (((t126 * t190 * t202 * 2.0 + -((t86 + t94) * t203 * t206))
                + t126 * t200 * t203 * t205 * 2.0)
               + t190 * t198 * t203 * t205 * 2.0)
            + t198 * t200 * t204 * t206 * 2.0;
        t71 = (((-(t129 * t190 * t202 * 2.0) + (t95 + t103) * t203 * t206)
                + -(t129 * t200 * t203 * t205 * 2.0))
               + -(t190 * t199 * t203 * t205 * 2.0))
            + -(t199 * t200 * t204 * t206 * 2.0);
        t85 = (((t189 * t191 * t202 * 2.0 + t26 * t28 * t203 * t206 * 2.0)
                + t189 * t196 * t203 * t205 * 2.0)
               + -(t191 * t197 * t203 * t205 * 2.0))
            + -(t196 * t197 * t204 * t206 * 2.0);
        t90 = (((-(t189 * t190 * t202 * 2.0) + t27 * t28 * t203 * t206 * 2.0)
                + t190 * t197 * t203 * t205 * 2.0)
               + -(t189 * t200 * t203 * t205 * 2.0))
            + t197 * t200 * t204 * t206 * 2.0;
        t99 = (((-(t190 * t191 * t202 * 2.0) + t26 * t27 * t203 * t206 * 2.0)
                + -(t190 * t196 * t203 * t205 * 2.0))
               + -(t191 * t200 * t203 * t205 * 2.0))
            + -(t196 * t200 * t204 * t206 * 2.0);
        t77 = ((((-(t127 * t128 * t202 * 2.0) + t310)
                 + (t75 + -(t68 * 4.0)) * t203 * t206)
                + t127 * t195 * t203 * t205 * 2.0)
               + -(t128 * t192 * t203 * t205 * 2.0))
            + t192 * t195 * t204 * t206 * 2.0;
        t131 = ((((t126 * t128 * t202 * 2.0 + -t309)
                  + (t80 + -(t70 * 4.0)) * t203 * t206)
                 + t128 * t198 * t203 * t205 * 2.0)
                + -(t126 * t195 * t203 * t205 * 2.0))
            + -(t195 * t198 * t204 * t206 * 2.0);
        t133 = ((((-(t125 * t130 * t202 * 2.0) + -t310)
                  + t646_tmp * (t78 - t67 * 4.0))
                 + t130 * t193 * t203 * t205 * 2.0)
                + -(t125 * t194 * t203 * t205 * 2.0))
            + t193 * t194 * t204 * t206 * 2.0;
        t325 =
            ((((t125 * t129 * t202 * 2.0 + t309) + t646_tmp * (t82 - t69 * 4.0))
              + t125 * t199 * t203 * t205 * 2.0)
             + -(t129 * t193 * t203 * t205 * 2.0))
            + -(t193 * t199 * t204 * t206 * 2.0);
        t135 = ((((t125 * t191 * t202 * 2.0 + t313)
                  + ((t75 + t18 * t28 * 2.0) + -t78) * t203 * t206)
                 + t125 * t196 * t203 * t205 * 2.0)
                + -(t191 * t193 * t203 * t205 * 2.0))
            + -(t193 * t196 * t204 * t206 * 2.0);
        t324 = ((((t127 * t189 * t202 * 2.0 + -t313)
                  + ((t78 + t22 * t26 * 2.0) + -t75) * t203 * t206)
                 + -(t127 * t197 * t203 * t205 * 2.0))
                + t189 * t192 * t203 * t205 * 2.0)
            + -(t192 * t197 * t204 * t206 * 2.0);
        t318 = ((((-(t126 * t189 * t202 * 2.0) + t312)
                  + ((t82 + t22 * t27 * 2.0) + -t80) * t203 * t206)
                 + t126 * t197 * t203 * t205 * 2.0)
                + -(t189 * t198 * t203 * t205 * 2.0))
            + t197 * t198 * t204 * t206 * 2.0;
        t321 = ((((-(t130 * t189 * t202 * 2.0) + t317)
                  + -(((t78 + t25 * t26 * 2.0) + -t75) * t203 * t206))
                 + t130 * t197 * t203 * t205 * 2.0)
                + -(t189 * t194 * t203 * t205 * 2.0))
            + t194 * t197 * t204 * t206 * 2.0;
        t323 = ((((t129 * t191 * t202 * 2.0 + t319)
                  + -(((t72 + t23 * t27 * 2.0) + -t73) * t203 * t206))
                 + t129 * t196 * t203 * t205 * 2.0)
                + t191 * t199 * t203 * t205 * 2.0)
            + t196 * t199 * t204 * t206 * 2.0;
        t322 = ((((-(t125 * t190 * t202 * 2.0) + -t312)
                  + ((t80 + t20 * t28 * 2.0) + -t82) * t203 * t206)
                 + -(t125 * t200 * t203 * t205 * 2.0))
                + t190 * t193 * t203 * t205 * 2.0)
            + t193 * t200 * t204 * t206 * 2.0;
        t316 = ((((t130 * t190 * t202 * 2.0 + -t319)
                  + -(((t73 + t24 * t26 * 2.0) + -t72) * t203 * t206))
                 + t130 * t200 * t203 * t205 * 2.0)
                + t190 * t194 * t203 * t205 * 2.0)
            + t194 * t200 * t204 * t206 * 2.0;
        t65 = ((((-(t128 * t191 * t202 * 2.0) + -t317)
                 + -(((t75 + t23 * t28 * 2.0) + -t78) * t203 * t206))
                + -(t128 * t196 * t203 * t205 * 2.0))
               + t191 * t195 * t203 * t205 * 2.0)
            + t195 * t196 * t204 * t206 * 2.0;
        t66 = ((((-(t127 * t190 * t202 * 2.0) + t314)
                 + ((t73 + t20 * t26 * 2.0) + -t72) * t203 * t206)
                + -(t127 * t200 * t203 * t205 * 2.0))
               + -(t190 * t192 * t203 * t205 * 2.0))
            + -(t192 * t200 * t204 * t206 * 2.0);
        t13 = ((((t128 * t190 * t202 * 2.0 + t315)
                 + -(((t80 + t24 * t28 * 2.0) + -t82) * t203 * t206))
                + t128 * t200 * t203 * t205 * 2.0)
               + -(t190 * t195 * t203 * t205 * 2.0))
            + -(t195 * t200 * t204 * t206 * 2.0);
        t12 = ((((-(t126 * t191 * t202 * 2.0) + -t314)
                 + ((t72 + t18 * t27 * 2.0) + -t73) * t203 * t206)
                + -(t126 * t196 * t203 * t205 * 2.0))
               + -(t191 * t198 * t203 * t205 * 2.0))
            + -(t196 * t198 * t204 * t206 * 2.0);
        t11 = ((((t129 * t189 * t202 * 2.0 + -t315)
                 + -(((t82 + t25 * t27 * 2.0) + -t80) * t203 * t206))
                + -(t129 * t197 * t203 * t205 * 2.0))
               + t189 * t199 * t203 * t205 * 2.0)
            + -(t197 * t199 * t204 * t206 * 2.0);
        H[0] = t151 * t202 * 2.0;
        H[1] = t262;
        H[2] = t241;
        H[3] = t606;
        H[4] = t622;
        H[5] = t625;
        H[6] = t599;
        H[7] = t619;
        H[8] = t612;
        H[9] = t603;
        H[10] = t610;
        H[11] = t615;
        H[12] = t262;
        H[13] = t150 * t202 * 2.0;
        H[14] = t261;
        H[15] = t621;
        H[16] = t607;
        H[17] = t620;
        H[18] = t617;
        H[19] = t602;
        H[20] = t616;
        H[21] = t609;
        H[22] = t604;
        H[23] = t608;
        H[24] = t241;
        H[25] = t261;
        H[26] = t149 * t202 * 2.0;
        H[27] = t624;
        H[28] = t623;
        H[29] = t605;
        H[30] = t611;
        H[31] = t618;
        H[32] = t601;
        H[33] = t614;
        H[34] = t613;
        H[35] = t600;
        H[36] = t606;
        H[37] = t621;
        H[38] = t624;
        H[39] = ((t191 * t191 * t202 * 2.0 + t196 * t196 * t204 * t206 * 2.0)
                 - t646_tmp * (t45 + t46))
            + t191 * t196 * t203 * t205 * 4.0;
        H[40] = t99;
        H[41] = t85;
        H[42] = t638;
        H[43] = t323;
        H[44] = t65;
        H[45] = t635;
        H[46] = t12;
        H[47] = t135;
        H[48] = t622;
        H[49] = t607;
        H[50] = t623;
        H[51] = t99;
        H[52] = ((t190 * t190 * t202 * 2.0 + t200 * t200 * t204 * t206 * 2.0)
                 - t646_tmp * (t44 + t46))
            + t190 * t200 * t203 * t205 * 4.0;
        H[53] = t90;
        H[54] = t316;
        H[55] = t71;
        H[56] = t13;
        H[57] = t66;
        H[58] = t86;
        H[59] = t322;
        H[60] = t625;
        H[61] = t620;
        H[62] = t605;
        H[63] = t85;
        H[64] = t90;
        H[65] = ((t189 * t189 * t202 * 2.0 + t197 * t197 * t204 * t206 * 2.0)
                 - t646_tmp * (t44 + t45))
            - t189 * t197 * t203 * t205 * 4.0;
        H[66] = t321;
        H[67] = t11;
        H[68] = t636;
        H[69] = t324;
        H[70] = t318;
        H[71] = t637;
        H[72] = t599;
        H[73] = t617;
        H[74] = t611;
        H[75] = t638;
        H[76] = t316;
        H[77] = t321;
        H[78] = ((t130 * t130 * t202 * 2.0 + t194 * t194 * t204 * t206 * 2.0)
                 - t646_tmp * (t42 + t43))
            + t130 * t194 * t203 * t205 * 4.0;
        H[79] = t631;
        H[80] = t627;
        H[81] = t633;
        H[82] = t646;
        H[83] = t133;
        H[84] = t619;
        H[85] = t602;
        H[86] = t618;
        H[87] = t323;
        H[88] = t71;
        H[89] = t11;
        H[90] = t631;
        H[91] = ((t129 * t129 * t202 * 2.0 + t199 * t199 * t204 * t206 * 2.0)
                 - t646_tmp * (t41 + t43))
            + t129 * t199 * t203 * t205 * 4.0;
        H[92] = t629;
        H[93] = t645;
        H[94] = t634;
        H[95] = t325;
        H[96] = t612;
        H[97] = t616;
        H[98] = t601;
        H[99] = t65;
        H[100] = t13;
        H[101] = t636;
        H[102] = t627;
        H[103] = t629;
        H[104] = ((t128 * t128 * t202 * 2.0 + t195 * t195 * t204 * t206 * 2.0)
                  - t646_tmp * (t41 + t42))
            - t128 * t195 * t203 * t205 * 4.0;
        H[105] = t77;
        H[106] = t131;
        H[107] = t632;
        H[108] = t603;
        H[109] = t609;
        H[110] = t614;
        H[111] = t635;
        H[112] = t66;
        H[113] = t324;
        H[114] = t633;
        H[115] = t645;
        H[116] = t77;
        H[117] = ((t127 * t127 * t202 * 2.0 + t192 * t192 * t204 * t206 * 2.0)
                  - t646_tmp * (t39 + t40))
            + t127 * t192 * t203 * t205 * 4.0;
        H[118] = t630;
        H[119] = t626;
        H[120] = t610;
        H[121] = t604;
        H[122] = t613;
        H[123] = t12;
        H[124] = t86;
        H[125] = t318;
        H[126] = t646;
        H[127] = t634;
        H[128] = t131;
        H[129] = t630;
        H[130] = ((t126 * t126 * t202 * 2.0 + t198 * t198 * t204 * t206 * 2.0)
                  - t646_tmp * (t38 + t40))
            + t126 * t198 * t203 * t205 * 4.0;
        H[131] = t628;
        H[132] = t615;
        H[133] = t608;
        H[134] = t600;
        H[135] = t135;
        H[136] = t322;
        H[137] = t637;
        H[138] = t133;
        H[139] = t325;
        H[140] = t632;
        H[141] = t626;
        H[142] = t628;
        H[143] = ((t125 * t125 * t202 * 2.0 + t193 * t193 * t204 * t206 * 2.0)
                  - t646_tmp * (t38 + t39))
            - t125 * t193 * t203 * t205 * 4.0;
    }

} // namespace autogen
} // namespace ipc
