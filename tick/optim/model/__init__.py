# License: BSD 3 clause

import tick.base

from .linreg import ModelLinReg
from .huber import ModelHuber
from .epsilon_insensitive import ModelEpsilonInsensitive
from .absolute_regression import ModelAbsoluteRegression
from .linreg_with_intercepts import ModelLinRegWithIntercepts

from .logreg import ModelLogReg
from .hinge import ModelHinge
from .smoothed_hinge import ModelSmoothedHinge
from .quadratic_hinge import ModelQuadraticHinge
from .modified_huber import ModelModifiedHuber

from .poisreg import ModelPoisReg

from .coxreg_partial_lik import ModelCoxRegPartialLik

from .hawkes_fixed_expkern_loglik import ModelHawkesFixedExpKernLogLik
from .hawkes_fixed_sumexpkern_loglik import ModelHawkesFixedSumExpKernLogLik
from .hawkes_fixed_expkern_leastsq import ModelHawkesFixedExpKernLeastSq
from .hawkes_fixed_sumexpkern_leastsq import ModelHawkesFixedSumExpKernLeastSq
from .hawkes_fixed_expkern_loglik_custom import ModelHawkesCustom
from .hawkes_fixed_sumexpkern_loglik_custom import ModelHawkesSumExpCustom
from .modelcustombasic import ModelCustomBasic
from .hawkes_fixed_expkern_loglik_custom2 import ModelHawkesCustomType2
from .hawkes_fixed_sumexpkern_loglik_custom2 import ModelHawkesSumExpCustomType2
from .model_rsb import ModelRsb
from .hawkes_fixed_sumexpkern_leastsq_qrh1 import ModelHawkesFixedSumExpKernLeastSqQRH1
from .hawkes_fixed_sumexpkern_QRH1_leastsq_list import ModelHawkesFixedSumExpKernLeastSqQRH1List
from .hawkes_fixed_sumexpkern_QRH2_leastsq_list import ModelHawkesFixedSumExpKernLeastSqQRH2List
from .hawkes_fixed_sumexpkern_QRH3_leastsq_list import ModelHawkesFixedSumExpKernLeastSqQRH3List

from .sccs import ModelSCCS

__all__ = ["ModelLinReg",
           "ModelLinRegWithIntercepts",
           "ModelLogReg",
           "ModelPoisReg",
           'ModelHinge',
           'ModelSmoothedHinge',
           'ModelQuadraticHinge',
           'ModelHuber',
           'ModelModifiedHuber',
           'ModelEpsilonInsensitive',
           'ModelAbsoluteRegression',
           "ModelCoxRegPartialLik",
           "ModelHawkesFixedExpKernLogLik",
           "ModelHawkesFixedSumExpKernLogLik",
           "ModelHawkesFixedExpKernLeastSq",
           "ModelHawkesFixedSumExpKernLeastSq",
           "ModelHawkesCustom",
           "ModelHawkesSumExpCustom",
           "ModelSCCS",
           "ModelCustomBasic",
           "ModelHawkesCustomType2",
           "ModelHawkesSumExpCustomType2",
           "ModelRsb",
           "ModelHawkesFixedSumExpKernLeastSqQRH1",
           "ModelHawkesFixedSumExpKernLeastSqQRH1List",
           "ModelHawkesFixedSumExpKernLeastSqQRH2List",
           "ModelHawkesFixedSumExpKernLeastSqQRH3List"
           ]