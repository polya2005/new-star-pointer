/**
 * @file ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "ui_gen.h"

#if LV_USE_XML
   #include "widgets/jog_interface/jog_interface_private_gen.h"
   #include "widgets/tabview/tabview_private_gen.h"
   #include "widgets/tabview_private_gen.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/* Global Styles */

/* Fonts */


/* Images */

/*Subjects*/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void ui_init_gen(const char * asset_path)
{
    char buf[256];

    /* Global Styles */

    /* Subjects */

    /* Fonts */

    /* Images */

    #if LV_USE_XML
        jog_interface_register();
        tabview_register();
        tabview_register();




    #endif
}

/* callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/
