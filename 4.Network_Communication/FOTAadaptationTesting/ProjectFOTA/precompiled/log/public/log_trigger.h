/******************************************************************************
 * @brief    LOG TRIGGER MODULE INTERRFACE
 * Copyright (c) 2017 NEUL LIMITED
******************************************************************************/

#ifndef SRC_LIB_LOG_PRIVATE_LOG_TRIGGER_H_
#define SRC_LIB_LOG_PRIVATE_LOG_TRIGGER_H_

/**
 * Ensure the log reader will be triggered.
 * This function should be called when the logger has detected it has written to an empty buffer.
 */
void log_trigger( void );

#endif /* SRC_LIB_LOG_PRIVATE_LOG_TRIGGER_H_ */
