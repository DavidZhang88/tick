# License: BSD 3 clause

import numpy as np

from .base import ModelFirstOrder, ModelSelfConcordant
from .build.model import ModelHawkesFixedSumExpKernLeastSqQRH3List as \
    _ModelHawkesFixedSumExpKernLeastSqQRH3List


class ModelHawkesFixedSumExpKernLeastSqQRH3List(ModelFirstOrder):

    _attrinfos = {
        "_end_times": {
        },
    }

    def __init__(self, decays: np.ndarray, MaxN : int, n_threads: int = 1):
        ModelFirstOrder.__init__(self)
        self._model = _ModelHawkesFixedSumExpKernLeastSqQRH3List(decays, MaxN, n_threads)
        print(self._model)


    def fit(self, events, global_n, end_times=None):
        """Set the corresponding realization(s) of the process.

        Parameters
        ----------
        events : `list` of `list` of `np.ndarray`
            List of Hawkes processes realizations.
            Each realization of the Hawkes process is a list of n_node for
            each component of the Hawkes. Namely `events[i][j]` contains a
            one-dimensional `numpy.array` of the events' timestamps of
            component j of realization i.
            If only one realization is given, it will be wrapped into a list

        end_times : `np.ndarray` or `float`, default = None
            List of end time of all hawkes processes that will be given to the
            model. If None, it will be set to each realization's latest time.
            If only one realization is provided, then a float can be given.
        """
        self._end_times = end_times
        return ModelFirstOrder.fit(self, events, global_n)

    def _loss(self, coeffs):
        return self._model.loss(coeffs)

    def _grad(self, coeffs: np.ndarray, out: np.ndarray) -> np.ndarray:
        self._model.grad(coeffs, out)
        return out

    def _get_n_coeffs(self):
        return self._model.get_n_coeffs()

    def _set_data(self, events, global_ns):
        # self._set("data", events)
        if not isinstance(events[0][0], np.ndarray):
            events = [events]

        end_times = self._end_times
        if end_times is None:
            end_times = np.array([max(map(max, e)) for e in events])

        if isinstance(end_times, (int, float)):
            end_times = np.array([end_times], dtype=float)

        self._model.set_data(events, global_ns, end_times)
