#include "pressure_boundary.h"

namespace SPH
{
//=================================================================================================//
namespace fluid_dynamics
{
//=================================================================================================//
FlowPressureBuffer::FlowPressureBuffer(BodyPartByCell &body_part, Vecd normal_vector)
    : BaseFlowBoundaryCondition(body_part),
      kernel_sum_(*particles_->getVariableByName<Vecd>("KernelSummation")), direction_(normal_vector){};
//=================================================================================================//
void FlowPressureBuffer::update(size_t index_i, Real dt)
{
    vel_[index_i] += 2.0*kernel_sum_[index_i] *  getTargetPressure(dt) / rho_[index_i] * dt;
    Real projectionLength = 0.0;
    for (size_t i = 0; i < static_cast<size_t>(vel_[index_i].size()); ++i)
        projectionLength += vel_[index_i][i] * direction_[i];
    for (size_t i = 0; i < static_cast<size_t>(vel_[index_i].size()); ++i)
        vel_[index_i][i] = projectionLength * direction_[i];
}
} // namespace fluid_dynamics
  //=================================================================================================//
} // namespace SPH
  //=================================================================================================//