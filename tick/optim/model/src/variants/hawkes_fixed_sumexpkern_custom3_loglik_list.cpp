// License: BSD 3 clause


#include "hawkes_fixed_sumexpkern_custom3_loglik_list.h"

ModelHawkesFixedSumExpKernCustom3LogLikList::ModelHawkesFixedSumExpKernCustom3LogLikList(
  const ArrayDouble &decays, const ulong _MaxN_of_f, const int max_n_threads) :
        ModelHawkesCustomLogLikList(max_n_threads), MaxN_of_f(_MaxN_of_f), decays(decays) {}

ulong ModelHawkesFixedSumExpKernCustom3LogLikList::get_n_coeffs() const {
  return n_nodes + n_nodes * n_nodes * get_n_decays() + n_nodes * MaxN_of_f;
}
