/**
 * @file jog_interface_gen.h
 *
 */

#ifndef JOG_INTERFACE_GEN_H
#define JOG_INTERFACE_GEN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a jog_interface object
 * @param parent pointer to an object, it will be the parent of the new jog_interface
 * @return pointer to the created jog_interface
 */
lv_obj_t * jog_interface_create(lv_obj_t * parent);




/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*JOG_INTERFACE_GEN_H*/