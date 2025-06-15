/**
 * @file tabview_private_gen.h
 *
 */

#ifndef TABVIEW_PRIVATE_H
#define TABVIEW_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/src/widgets/tabview/lv_tabview_private.h" /*The ancestor of tabview*/
#include "tabview.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_tabview_t obj;  /* Base widget to extend */
} tabview_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if LV_USE_XML
    void tabview_register(void);
#endif

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*TABVIEW_PRIVATE_H*/