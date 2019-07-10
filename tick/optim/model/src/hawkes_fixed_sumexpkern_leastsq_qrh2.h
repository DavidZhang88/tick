#ifndef TICK_OPTIM_MODEL_SRC_HAWKES_FIXED_SUMEXPKERN_LEASTSQ_QRH2_H_
#define TICK_OPTIM_MODEL_SRC_HAWKES_FIXED_SUMEXPKERN_LEASTSQ_QRH2_H_

// License: BSD 3 clause

#include "base.h"
#include "base/hawkes_single.h"

/** \class ModelHawkesFixedSumExpKernLeastSqQRH2
 * \brief Class for computing L2 Contrast function and gradient for Hawkes processes with
 * sum exponential kernels with fixed exponent (i.e., \sum_u alpha_u*beta_u*e^{-beta_u t},
 * with fixed beta)
 */
class DLL_PUBLIC ModelHawkesFixedSumExpKernLeastSqQRH2 : public ModelHawkesSingle {

    //!
    ulong MaxN;
    ArrayDouble global_timestamps;
    ArrayLong global_n;
    ArrayULong type_n;

    ulong Total_events;

//! @brief Some arrays used for intermediate computings.
    ArrayDouble2dList1D g;
    ArrayDouble2dList1D G;
    ArrayDouble2dList1D H;

    ArrayDouble Length;
    ArrayULongList1D Count;


//! @brief The array of decays (remember that the decays are fixed!)
ArrayDouble decays;

//! @brief n_decays (number of decays in the sum exponential kernel)
ulong n_decays;

public:
//! @brief Default constructor
//! @note This constructor is only used to create vectors of ModelHawkesFixedExpKernLeastSq and serialization
ModelHawkesFixedSumExpKernLeastSqQRH2() {}

//! @brief Constructor
//! \param timestamps : a list of arrays representing the realization
//! \param decays : the 2d array of the decays
//! \param end_time : The time until which this process has been observed
//! \param max_n_threads : maximum number of threads to be used for multithreading
//! \param optimization_level : 0 corresponds to no optimization and 1 to use of faster
//! (approximated) exponential function
ModelHawkesFixedSumExpKernLeastSqQRH2(const ArrayDouble &decays,
                                      const ulong MaxN,
                                      const unsigned int max_n_threads = 1,
                                      const unsigned int optimization_level = 0);

public:
        void set_data(const SArrayDoublePtrList1D &_timestamps,
                      const SArrayLongPtr _global_n,
                      const double _end_times) override;

    /**
     * @brief Precomputations of intermediate values
     * They will be used to compute faster loss, gradient and hessian norm.
     */
    void compute_weights();

    /**
     * @brief Compute loss
     * \param coeffs : Point in which loss is computed
     * \return Loss' value
     */
    double loss(const ArrayDouble &coeffs) override;

    /**
     * @brief Compute loss corresponding to sample i (between 0 and rand_max = n_nodes)
     * \param i : selected component
     * \param coeffs : Point in which loss is computed
     * \return Loss' value
     */
    double loss_i(const ulong i, const ArrayDouble &coeffs) override;

    /**
     * @brief Compute gradient
     * \param coeffs : Point in which gradient is computed
     * \param out : Array in which the value of the gradient is stored
     */
    void grad(const ArrayDouble &coeffs, ArrayDouble &out) override;

    /**
     * @brief Compute gradient corresponding to sample i (between 0 and rand_max = n_nodes)
     * \param i : selected component
     * \param coeffs : Point in which gradient is computed
     * \param out : Array in which the value of the gradient is stored
     */
    void grad_i(ulong i, const ArrayDouble &coeffs, ArrayDouble &out) override;

    /**
     * @brief Compute loss and gradient
     * \param coeffs : Point in which loss and gradient are computed
     * \param out : Array in which the value of the gradient is stored
     * \return Loss' value
     */
    double loss_and_grad(const ArrayDouble &coeffs, ArrayDouble &out);

    ulong get_n_coeffs() const override{
        return n_nodes * MaxN + n_nodes * n_nodes * decays.size();
    }

    void allocate_weights();

    /**
     * @brief Precomputations of intermediate values for component i
     * \param i : selected component
     */

void compute_weights_i(const ulong i);

private:
    void compute_weights_H_j(const ulong j);


    ulong get_mu_i_first_index(const ulong i) const{
        return MaxN * i;
    }

    ulong get_mu_i_last_index(const ulong i) const{
        return MaxN * (i + 1);
    }

    ulong get_alpha_u_i_j_index(const ulong u, const ulong i, const ulong j) const{
        return n_nodes * MaxN + u * n_nodes * n_nodes + i * n_nodes + j;
    }

friend class ModelHawkesFixedSumExpKernLeastSqQRH2List;

};

//CEREAL_REGISTER_TYPE(ModelHawkesFixedSumExpKernLeastSqQRH2);

#endif  // TICK_OPTIM_MODEL_SRC_HAWKES_FIXED_SUMEXPKERN_LEASTSQ_QRH2_H_
