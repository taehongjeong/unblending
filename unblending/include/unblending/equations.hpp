#ifndef EQUATIONS_HPP
#define EQUATIONS_HPP

#include <unblending/common.hpp>
#include <unblending/blend_mode.hpp>
#include <unblending/comp_op.hpp>

namespace unblending
{
    /// \brief Calculate the composite operation.
    /// \details Equation 6:
    /// \f[
    ///     \mathtt{comp}(\mathbf{x}_s, \mathbf{x}_d)
    /// \f]
    Vec4 composite_two_layers(const Vec3&     c_s,
                              const Vec3&     c_d,
                              const double    a_s,
                              const double    a_d,
                              const CompOp&   comp_op,
                              const BlendMode mode,
                              const bool      crop = false);
    
    /// \brief Calculate the recursive composition.
    /// \details Equation 7:
    /// \f[
    ///     \hat{\mathbf{x}}
    /// \f]
    Vec4 composite_layers(const VecX&                   alphas,
                          const VecX&                   colors,
                          const std::vector<CompOp>&    comp_ops,
                          const std::vector<BlendMode>& modes,
                          const bool                    crop = false);
    
    /// \brief Calculate the lagrangian term of the objective function.
    /// \details
    /// \f[
    ///     - \boldsymbol{\lambda}^{\mathrm{T}} \mathbf{C}(\mathbf{x})
    /// \f]
    double calculate_lagrange_term(const VecX& constraint_vector,
                                   const VecX& lambda);
    
    /// \brief Calculate the penalty term of the objective function.
    /// \details
    /// \f[
    ///     \frac{1}{2} \rho \| \mathbf{C}(\mathbf{x}) \|^2
    /// \f]
    double calculate_penalty_term(const VecX&  constraint_vector,
                                  const double rho);
    
    /// \brief Calculate the energy function.
    /// \details
    /// \f[
    ///     E(\mathbf{x})
    /// \f]
    double calculate_unmixing_energy_term(const VecX&                       alphas,
                                          const VecX&                       colors,
                                          const std::vector<ColorModelPtr>& models,
                                          const double                      sigma,
                                          const bool                        use_sparcity,
                                          const bool                        use_minimum_alpha);
    
    /// \brief Calculate the constraint vector.
    /// \details
    /// \f[
    ///     \mathbf{C}(\mathbf{x})
    /// \f]
    VecX calculate_constraint_vector(const VecX&                   alphas,
                                     const VecX&                   colors,
                                     const Vec3&                   target_color,
                                     const std::vector<CompOp>&    comp_ops,
                                     const std::vector<BlendMode>& modes,
                                     const bool                    use_target_alphas,
                                     const VecX&                   target_alphas = VecX(),
                                     const std::vector<int>&       gray_layers = std::vector<int>());
    
    /// \brief Calculate the derivative of the energy function.
    /// \details
    /// \f[
    ///     \frac{\partial}{\partial \mathbf{x}} E(\mathbf{x})
    /// \f]
    VecX calculate_derivative_of_unmixing_energy(const VecX&                       alphas,
                                                 const VecX&                       colors,
                                                 const std::vector<ColorModelPtr>& models,
                                                 const double                      sigma,
                                                 const bool                        use_sparcity,
                                                 const bool                        use_minimum_alpha);
    
    /// \brief Calculate the derivative of the constraint vector.
    /// \details Equation 15:
    /// \f[
    ///     \frac{\partial}{\partial \mathbf{x}} \mathbf{C}(\mathbf{x})
    /// \f]
    MatX calculate_derivative_of_constraint_vector(const VecX&                   alphas,
                                                   const VecX&                   colors,
                                                   const Vec3&                   target_color,
                                                   const std::vector<CompOp>&    comp_ops,
                                                   const std::vector<BlendMode>& modes,
                                                   const bool                    use_target_alphas,
                                                   const VecX&                   target_alphas = VecX(),
                                                   const std::vector<int>&       gray_layers = std::vector<int>());
    
    //////////////////////////////////////////////////////////////////////////////////
    // Wrapper functions
    //////////////////////////////////////////////////////////////////////////////////
    
    Vec4 composite_two_layers(const Vec4&     x_s,
                              const Vec4&     x_d,
                              const CompOp&   comp_op,
                              const BlendMode mode,
                              const bool      crop = false);
    
    double calculate_unmixing_energy_term(const VecX&                       x,
                                          const std::vector<ColorModelPtr>& models,
                                          const double                      sigma,
                                          const bool                        use_sparcity,
                                          const bool                        use_minimum_alpha);
    
    VecX calculate_constraint_vector(const VecX&                   x,
                                     const Vec3&                   target_color,
                                     const std::vector<CompOp>&    comp_ops,
                                     const std::vector<BlendMode>& modes,
                                     const bool                    use_target_alphas,
                                     const VecX&                   target_alphas = VecX(),
                                     const std::vector<int>&       gray_layers = std::vector<int>());
}

#endif // EQUATIONS_HPP
