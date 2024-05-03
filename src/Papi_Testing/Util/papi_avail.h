#include <utility> // For std::pair
#include <vector>
#include <papi.h>

using MetricInfo = std::pair<int, std::string>;
std::vector<MetricInfo> availMetrics = {
    // {PAPI_L1_DCM, "Level 1 data cache misses"},
    // {PAPI_L1_ICM, "Level 1 instruction cache misses"},
    // {PAPI_L2_DCM, "Level 2 data cache misses"},
    // {PAPI_L2_ICM, "Level 2 instruction cache misses"},

    {PAPI_L1_TCM, "Level 1 cache misses"},
    {PAPI_L2_TCM, "Level 2 cache misses"},
    {PAPI_L3_TCM, "Level 3 cache misses"},
    // {PAPI_TLB_DM, "Data translation lookaside buffer misses"},

    // {PAPI_TLB_IM, "Instruction translation lookaside buffer misses"},
    // {PAPI_L1_LDM, "Level 1 load misses"},
    // {PAPI_L1_STM, "Level 1 store misses"},
    // {PAPI_L2_STM, "Level 2 store misses"},

    // {PAPI_STL_ICY,  "Cycles with no instruction issue"},
    // {PAPI_BR_UCN,   "Unconditional branch instructions"},
    // {PAPI_BR_CN,    "Conditional branch instructions"},
    // {PAPI_BR_TKN,   "Conditional branch instructions taken"},

    // {PAPI_BR_NTK,   "Conditional branch instructions not taken"},
    // {PAPI_BR_MSP,   "Conditional branch instructions mispredicted"},
    // {PAPI_BR_PRC,   "Conditional branch instructions correctly predicted"},
    // {PAPI_TOT_INS,  "Instructions completed"},

    // {PAPI_FP_INS, "Floating point instructions"},
    // {PAPI_LD_INS, "Load instructions"},
    // {PAPI_SR_INS, "Store instructions"},
    // {PAPI_BR_INS, "Branch instructions"},

    // {PAPI_TOT_CYC, "Total cycles"},
    {PAPI_L2_DCH, "Level 2 data cache hits"},
    // {PAPI_L2_DCA, "Level 2 data cache accesses"},
    // {PAPI_L3_DCA, "Level 3 data cache accesses"},

    // {PAPI_L2_DCR, "Level 2 data cache reads"},
    // {PAPI_L3_DCR, "Level 3 data cache reads"},
    // {PAPI_L2_DCW, "Level 2 data cache writes"},
    // {PAPI_L3_DCW, "Level 3 data cache writes"},

    // {PAPI_L2_ICH, "Level 2 instruction cache hits"},
    // {PAPI_L2_ICA, "Level 2 instruction cache accesses"},
    // {PAPI_L3_ICA, "Level 3 instruction cache accesses"},
    // {PAPI_L2_ICR, "Level 2 instruction cache reads"},

    // {PAPI_L3_ICR, "Level 3 instruction cache reads"},
    // {PAPI_L2_TCA, "Level 2 total cache accesses"},
    // {PAPI_L3_TCA, "Level 3 total cache accesses"},
    // {PAPI_L2_TCR, "Level 2 total cache reads"},

    // {PAPI_L3_TCR, "Level 3 total cache reads"},
    // {PAPI_L2_TCW, "Level 2 total cache writes"},
    // {PAPI_L3_TCW, "Level 3 total cache writes"},
    // {PAPI_FDV_INS, "Floating point divide instructions"},

    // {PAPI_FP_OPS, "Floating point operations"},
    // {PAPI_SP_OPS, "Floating point operations; optimized to count scaled single precision vector operations"},
    // {PAPI_DP_OPS, "Floating point operations; optimized to count scaled double precision vector operations"},
    // {PAPI_VEC_SP, "Single precision vector/SIMD instructions"},

    // {PAPI_VEC_DP, "Double precision vector/SIMD instructions"},
    // {PAPI_REF_CYC, "Reference clock cycles"}
};