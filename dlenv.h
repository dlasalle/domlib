/**
 * @file dlenv.h
 * @brief Function prototypes for getting and setting environment variables
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright (c) 2013-2020, Dominique LaSalle
 * @version 1
 * @date 2013-10-08
 */




#ifndef DL_ENV_H
#define DL_ENV_H




#include <stdint.h>




/******************************************************************************
* PUBLIC FUNCTIONS ************************************************************
******************************************************************************/


const char * dl_get_env_string(
    char const * name,
    char const * def);


int dl_get_env_bool(
    char const * name, int def);


int64_t dl_get_env_int(
    char const * name,
    int64_t def);


double dl_get_env_float(
    char const * name,
    double def);




#endif
