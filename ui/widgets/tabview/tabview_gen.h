/**
 * @file tabview_gen.h
 *
 */

#ifndef TABVIEW_GEN_H
#define TABVIEW_GEN_H

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
 * Create a tabview object
 * @param parent pointer to an object, it will be the parent of the new tabview
 * @return pointer to the created tabview
 */
lv_obj_t * tabview_create(lv_obj_t * parent);




/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TABVIEW_GEN_H*/