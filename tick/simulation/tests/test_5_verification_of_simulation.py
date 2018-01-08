# License: BSD 3 clause

import numpy as np
from tick.simulation.build.simulation import Hawkes_custom
from tick.simulation import HawkesKernel0, HawkesKernelExp, HawkesKernelPowerLaw, \
    HawkesKernelSumExp
from tick.simulation import SimuHawkes

n_nodes = 2
dim = n_nodes
seed = 3007
MaxN_of_f = 5
f_i = [np.array([1., 0.8, 0.9, 1.0, 0.7]), np.array([1., 0.6, 0.5, 0.7, 1.0])]

beta = 3
end_time = 100000

kernels = np.array([
            [HawkesKernelExp(0.7, beta), HawkesKernelExp(0.6, beta)],
            [HawkesKernelExp(0.2, beta), HawkesKernelExp(0.3, beta)]
        ])

simu_model = SimuHawkes(kernels=kernels, end_time=end_time, custom=True, seed=seed, MaxN_of_f = MaxN_of_f, f_i=f_i)
for i in range(n_nodes):
    simu_model.set_baseline(i, 0.5)
    for j in range(n_nodes):
        simu_model.set_kernel(i, j, kernels[i, j])
simu_model.track_intensity(0.1)
# print(simu_model.simulate)
simu_model.simulate()

# plot_point_process(simu_model)
##################################################################################################################





##################################################################################################################
from tick.optim.model import ModelHawkesCustom
from tick.optim.solver import GD, AGD, SGD, SVRG, SDCA
from tick.optim.prox import ProxElasticNet, ProxL2Sq, ProxZero, ProxL1

timestamps = simu_model.timestamps
global_n = np.array(simu_model._pp.get_global_n())
global_n = np.insert(global_n, 0, 0).astype(int)

model = ModelHawkesCustom(beta, MaxN_of_f)
model.fit(timestamps, global_n, end_time)
#############################################################################
prox = ProxL1(0.01, positive=True)

# solver = AGD(step=5e-2, linesearch=False, max_iter= 350)
solver = AGD(step=1e-2, linesearch=False, max_iter=100, print_every=100)
solver.set_model(model).set_prox(prox)

x0 = np.array(
    [0.3, 0.3, 0.5, 0.5, 0.5, 0.5,   1., 0.8, 0.9, 1.0, 0.7, 1., 0.6, 0.5, 0.7, 1.0])
solver.solve(x0)

# normalisation
solution_adj = solver.solution
for i in range(dim):
    solution_adj[i] *= solver.solution[dim + dim * dim + MaxN_of_f * i]
    solution_adj[(dim + dim * i): (dim + dim * (i + 1))] *= solver.solution[dim + dim * dim + MaxN_of_f * i]
    solution_adj[(dim + dim * dim + MaxN_of_f * i): (dim + dim * dim + MaxN_of_f * (i + 1))] /= solver.solution[
        dim + dim * dim + MaxN_of_f * i]
print(solution_adj)