/**
 * @file jog_interface_private_gen.h
 *
 */

#ifndef JOG_INTERFACE_PRIVATE_H
#define JOG_INTERFACE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/src/core/lv_obj_private.h"
#include "jog_interface.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t obj;  /* Base widget to extend */
    lv_obj_t * lv_buttonmatrix_1;
} jog_interface_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_USE_XML
    void jog_interface_register(void);
#endif

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*JOG_INTERFACE_PRIVATE_H*/