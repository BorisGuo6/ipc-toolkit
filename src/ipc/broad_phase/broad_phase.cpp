#include "broad_phase.hpp"

#include <ipc/broad_phase/brute_force.hpp>
#include <ipc/broad_phase/spatial_hash.hpp>
#include <ipc/broad_phase/hash_grid.hpp>
#include <ipc/broad_phase/sweep_and_tiniest_queue.hpp>
#include <ipc/broad_phase/broadmark.hpp>
#include <ipc/candidates/candidates.hpp>

#include <ipc/config.hpp>

#include "Broadphase/Algorithms/GPU/Bullet3GPUAlgorithms.h"
#include "Broadphase/Algorithms/BF/BF.h"
#include "Broadphase/Algorithms/DBVT/DBVT.h"
#include "Broadphase/Algorithms/Grid/Grid_ND.h"
#include "Broadphase/Algorithms/Grid/Grid_ND_Parallel.h"
#include "Broadphase/Algorithms/Grid/Grid_ND_SAP.h"
#include "Broadphase/Algorithms/KD/KD.h"
#include "Broadphase/Algorithms/SAP/SAP.h"
#include "Broadphase/Algorithms/SAP/SAP_Parallel.h"
#include "Broadphase/Algorithms/SAP/SAP_SIMD_Parallel.h"
#include "Broadphase/Algorithms/Tracy/Tracy.h"
#include "Broadphase/Algorithms/Tracy/Tracy_Parallel.h"
#include "Broadphase/Algorithms/iSAP/AxisSweep.h"

namespace ipc {

void BroadPhase::build(
    const Eigen::MatrixXd& vertices,
    const Eigen::MatrixXi& edges,
    const Eigen::MatrixXi& faces,
    double inflation_radius)
{
    assert(edges.size() == 0 || edges.cols() == 2);
    assert(faces.size() == 0 || faces.cols() == 3);
    clear();
    build_vertex_boxes(vertices, vertex_boxes, inflation_radius);
    build_edge_boxes(vertex_boxes, edges, edge_boxes);
    build_face_boxes(vertex_boxes, faces, face_boxes);
}

void BroadPhase::build(
    const Eigen::MatrixXd& vertices_t0,
    const Eigen::MatrixXd& vertices_t1,
    const Eigen::MatrixXi& edges,
    const Eigen::MatrixXi& faces,
    double inflation_radius)
{
    assert(edges.size() == 0 || edges.cols() == 2);
    assert(faces.size() == 0 || faces.cols() == 3);
    clear();
    build_vertex_boxes(
        vertices_t0, vertices_t1, vertex_boxes, inflation_radius);
    build_edge_boxes(vertex_boxes, edges, edge_boxes);
    build_face_boxes(vertex_boxes, faces, face_boxes);
}

void BroadPhase::clear()
{
    vertex_boxes.clear();
    edge_boxes.clear();
    face_boxes.clear();
}

void BroadPhase::detect_collision_candidates(
    int dim, Candidates& candidates) const
{
    candidates.clear();
    if (dim == 2) {
        // This is not needed for 3D
        detect_edge_vertex_candidates(candidates.ev_candidates);
    } else {
        // These are not needed for 2D
        detect_edge_edge_candidates(candidates.ee_candidates);
        detect_face_vertex_candidates(candidates.fv_candidates);
    }
}

////////////////////////////////////////////////////////////////////////////////

std::unique_ptr<BroadPhase>
BroadPhase::make_broad_phase(const BroadPhaseMethod broad_phase_method)
{
    switch (broad_phase_method) {
    case BroadPhaseMethod::BRUTE_FORCE:
        return std::make_unique<BruteForce>();
    case BroadPhaseMethod::HASH_GRID:
        return std::make_unique<HashGrid>();
    case BroadPhaseMethod::SPATIAL_HASH:
        return std::make_unique<SpatialHash>();
    case BroadPhaseMethod::SWEEP_AND_TINIEST_QUEUE:
        return std::make_unique<SweepAndTiniestQueue>();
    case BroadPhaseMethod::SWEEP_AND_TINIEST_QUEUE_GPU:
#ifdef IPC_TOOLKIT_WITH_CUDA
        return std::make_unique<SweepAndTiniestQueueGPU>();
#else
        throw std::runtime_error("GPU Sweep and Tiniest Queue is disabled "
                                 "because CUDA is disabled!");
#endif
#ifdef IPC_TOOLKIT_WITH_BROADMARK
    case BroadPhaseMethod::BROADMARK_GPU_LBVH:
        return std::make_unique<Broadmark<GPU_LBVH>>();
    case BroadPhaseMethod::BROADMARK_GRID:
        return std::make_unique<Broadmark<Grid_3D>>();
    case BroadPhaseMethod::BROADMARK_GRID_PARALLEL:
        return std::make_unique<Broadmark<Grid_3D_Parallel>>();
    case BroadPhaseMethod::BROADMARK_SAP:
        return std::make_unique<Broadmark<SAP>>();
    case BroadPhaseMethod::BROADMARK_SAP_PARALLEL:
        return std::make_unique<Broadmark<SAP_Parallel>>();
    case BroadPhaseMethod::BROADMARK_DBVT_D:
        return std::make_unique<Broadmark<DBVT_D>>();
    case BroadPhaseMethod::BROADMARK_DBVT_F:
        return std::make_unique<Broadmark<DBVT_F>>();
    case BroadPhaseMethod::BROADMARK_ISAP:
        return std::make_unique<Broadmark<AxisSweep>>();
    case BroadPhaseMethod::BROADMARK_KD:
        return std::make_unique<Broadmark<KD>>();
    case BroadPhaseMethod::BROADMARK_TRACY:
        return std::make_unique<Broadmark<Tracy>>();
    case BroadPhaseMethod::BROADMARK_TRACY_PARALLEL:
        return std::make_unique<Broadmark<Tracy_Parallel>>();
    case BroadPhaseMethod::BROADMARK_GRID_SAP:
        return std::make_unique<Broadmark<Grid_3D_SAP>>();
    // case BroadPhaseMethod::BROADMARK_CGAL:
    //     return std::make_unique<Broadmark<CGAL_Internal>>();
    case BroadPhaseMethod::BROADMARK_GPU_GRID:
        return std::make_unique<Broadmark<GPU_Grid>>();
    case BroadPhaseMethod::BROADMARK_GPU_SAP:
        return std::make_unique<Broadmark<GPU_SAP>>();
#else
    case BroadPhaseMethod::BROADMARK_GPU_LBVH:
    case BroadPhaseMethod::BROADMARK_GRID:
    case BroadPhaseMethod::BROADMARK_GRID_PARALLEL:
    case BroadPhaseMethod::BROADMARK_SAP:
    case BroadPhaseMethod::BROADMARK_SAP_PARALLEL:
    case BroadPhaseMethod::BROADMARK_DBVT_D:
    case BroadPhaseMethod::BROADMARK_DBVT_F:
    case BroadPhaseMethod::BROADMARK_ISAP:
    case BroadPhaseMethod::BROADMARK_KD:
    case BroadPhaseMethod::BROADMARK_TRACY:
    case BroadPhaseMethod::BROADMARK_TRACY_PARALLEL:
    case BroadPhaseMethod::BROADMARK_GRID_SAP:
    // case BroadPhaseMethod::BROADMARK_CGAL:
    case BroadPhaseMethod::BROADMARK_GPU_GRID:
    case BroadPhaseMethod::BROADMARK_GPU_SAP:
        throw std::runtime_error("Broadmark is disabled!");
#endif
    default:
        throw std::runtime_error("Invalid BroadPhaseMethod!");
    }
}

////////////////////////////////////////////////////////////////////////////////

bool BroadPhase::can_edge_vertex_collide(size_t ei, size_t vi) const
{
    const auto& [e0i, e1i, _] = edge_boxes[ei].vertex_ids;

    return vi != e0i && vi != e1i
        && (can_vertices_collide(vi, e0i) || can_vertices_collide(vi, e1i));
}

bool BroadPhase::can_edges_collide(size_t eai, size_t ebi) const
{
    const auto& [ea0i, ea1i, _] = edge_boxes[eai].vertex_ids;
    const auto& [eb0i, eb1i, __] = edge_boxes[ebi].vertex_ids;

    bool share_endpoint =
        ea0i == eb0i || ea0i == eb1i || ea1i == eb0i || ea1i == eb1i;

    return !share_endpoint
        && (can_vertices_collide(ea0i, eb0i) || can_vertices_collide(ea0i, eb1i)
            || can_vertices_collide(ea1i, eb0i)
            || can_vertices_collide(ea1i, eb1i));
}

bool BroadPhase::can_face_vertex_collide(size_t fi, size_t vi) const
{
    const auto& [f0i, f1i, f2i] = face_boxes[fi].vertex_ids;

    return vi != f0i && vi != f1i && vi != f2i
        && (can_vertices_collide(vi, f0i) || can_vertices_collide(vi, f1i)
            || can_vertices_collide(vi, f2i));
}

bool BroadPhase::can_edge_face_collide(size_t ei, size_t fi) const
{
    const auto& [e0i, e1i, _] = edge_boxes[ei].vertex_ids;
    const auto& [f0i, f1i, f2i] = face_boxes[fi].vertex_ids;

    bool share_endpoint = e0i == f0i || e0i == f1i || e0i == f2i || e1i == f0i
        || e1i == f1i || e1i == f2i;

    return !share_endpoint
        && (can_vertices_collide(e0i, f0i) || can_vertices_collide(e0i, f1i)
            || can_vertices_collide(e0i, f2i) || can_vertices_collide(e1i, f0i)
            || can_vertices_collide(e1i, f1i)
            || can_vertices_collide(e1i, f2i));
}

} // namespace ipc
