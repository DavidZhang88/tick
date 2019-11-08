#include "hawkes_QRH3.h"

Hawkes_QRH3::Hawkes_QRH3(unsigned int n_nodes, int seed, ulong _MaxN_of_f, const SArrayDoublePtrList1D &_f_i)
        : Hawkes(n_nodes, seed), global_n(0), Qty(0) {
    this->MaxN_of_f = _MaxN_of_f;
    this->f_i = _f_i;

    f_i_Max = ArrayDouble(n_nodes);

    for (ulong i = 0; i != n_nodes; ++i)
        f_i_Max[i] = f_i[i]->max();

    last_global_n = 0;
}

Hawkes_QRH3::Hawkes_QRH3(unsigned int n_nodes, int seed, ulong _MaxN_of_f, const SArrayDoublePtrList1D &_f_i, const ArrayDouble &extrainfo, const std::string _simu_mode)
        : Hawkes(n_nodes, seed), global_n(0), Qty(0), simu_mode(_simu_mode) {
    this->MaxN_of_f = _MaxN_of_f;
    this->f_i = _f_i;

    f_i_Max = ArrayDouble(n_nodes);

    for (ulong i = 0; i != n_nodes; ++i)
        f_i_Max[i] = f_i[i]->max();

    last_global_n = 0;
    if(simu_mode == "random")
        return;
    else if(simu_mode == "generate"){
        current_num = extrainfo[0];
        avg = extrainfo[1];
        dim = extrainfo[2];
        avg_order_size = ArrayDouble(dim);
        for(ulong k = 0; k != dim; ++k)
            avg_order_size[k] = extrainfo[3 + k];

        ulong round = ceil(current_num / avg);  //round a number
        last_global_n = (round > MaxN_of_f - 1) ? MaxN_of_f - 1 : round;
        if(current_num <= 0) {
            current_num = 0;
            last_global_n = 0;
        }
    }
    else
        TICK_ERROR("Unknown scenario");
}



bool Hawkes_QRH3::update_time_shift_(double delay,
                                       ArrayDouble &intensity,
                                       double *total_intensity_bound1) {
    if (total_intensity_bound1) *total_intensity_bound1 = 0;
    bool flag_negative_intensity1 = false;

    // We loop on the contributions
    for (unsigned int i = 0; i < n_nodes; i++) {
        intensity[i] = get_baseline(i, get_time());
        if (total_intensity_bound1)
            *total_intensity_bound1 += get_baseline_bound(i, get_time());

        for (unsigned int j = 0; j < n_nodes; j++) {
            HawkesKernelPtr &k = kernels[i * n_nodes + j];

            if (k->get_support() == 0) continue;
            double bound = 0;
            intensity[i] += k->get_convolution(get_time() + delay, *timestamps[j], &bound) * f_i[i]->operator[](last_global_n);

            if (total_intensity_bound1) {
                *total_intensity_bound1 += bound * f_i_Max[i];
            }
            if (intensity[i] < 0) {
                if (threshold_negative_intensity) intensity[i] = 0;
                flag_negative_intensity1 = true;
            }
        }
    }
    return flag_negative_intensity1;
}

void Hawkes_QRH3::update_jump(int index) {
    if(simu_mode == "random") {
        last_global_n = (unsigned long) std::rand() % MaxN_of_f;
        global_n.append1(last_global_n);
        // We make the jump on the corresponding signal
        timestamps[index]->append1(time);
        n_total_jumps++;
    }
    else if(simu_mode == "generate"){
        current_num += avg_order_size[index];
        ulong round = ceil(current_num / avg);  //round a number
        last_global_n = (round > MaxN_of_f - 1) ? MaxN_of_f - 1 : round;
        if(current_num <= 0) {
            current_num = 0;
            last_global_n = 0;
        }
        global_n.append1(last_global_n);
        // We make the jump on the corresponding signal
        timestamps[index]->append1(time);
        Qty.append1(current_num);
        n_total_jumps++;

        if(current_num < 0){
            //!terminate the simulation, becuase there is no order now
            //!set time large enough to terminate the simulation
            this->time = 1e10;
        }
    }
    else {
        TICK_ERROR("Unknown simulation scenario.");
    }
}

void Hawkes_QRH3::init_intensity_(ArrayDouble &intensity, double *total_intensity_bound) {
    *total_intensity_bound = 0;
    for (unsigned int i = 0; i < n_nodes; i++) {
        intensity[i] = get_baseline(i, 0.) * f_i[i]->operator[](last_global_n);;
//        *total_intensity_bound += get_baseline_bound(i, 0.);
        *total_intensity_bound += get_baseline(i, 0.) * f_i_Max[i];
    }
}