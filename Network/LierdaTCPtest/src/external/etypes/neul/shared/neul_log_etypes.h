/******************************************************************************
 * @brief    NEUL LOG ETYPES
 * Copyright (c) 2018 Huawei Technologies Co. Ltd
******************************************************************************/
#ifndef ETYPES_SHARED_NEUL_LOG_ETYPES_H_
#define ETYPES_SHARED_NEUL_LOG_ETYPES_H_


/** @addtogroup libNEUL_LOGAPI
 * @{
 * */

typedef enum ETYPES_ENUM_HOLDER_TYPE(U8)
{
    NEUL_LOG_LEVEL_NONE,
    NEUL_LOG_LEVEL_VERBOSE,
    NEUL_LOG_LEVEL_NORMAL,
    NEUL_LOG_LEVEL_WARNING,
    NEUL_LOG_LEVEL_ERROR,
    NEUL_LOG_LEVEL_CUSTOM,
    NEUL_LOG_MAX,
}
NEUL_LOG_LEVEL;


typedef struct {
    NEUL_LOG_LEVEL value;
} NEUL_LOG_LEVEL_es;

/** @} end of group libNEUL_LOGAPI */

#endif /* ETYPES_SHARED_NEUL_LOG_ETYPES_H_ */
