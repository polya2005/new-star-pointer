/**
 * @file starptr_interface_gen.h
 */

#ifndef STARPTR_INTERFACE_GEN_H
#define STARPTR_INTERFACE_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/*Include all the widget and components of this library*/
#include "components/title_gen.h"
#include "screens/jog_screen_gen.h"

/*********************
 *      DEFINES
 *********************/

// TODO: should these definitions be prefixed with the project name?


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/* callbacks */

/*Fonts*/


/*Images*/


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the component library
 */

void starptr_interface_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*STARPTR_INTERFACE_GEN_H*/
