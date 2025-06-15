/**
 * @file tabview_gen.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "tabview_private_gen.h"
#include "lvgl/src/core/lv_obj_class_private.h"
#include "ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  GLOBAL PROTOTYPES
 **********************/

void tabview_constructor_hook(lv_obj_t * obj);
void tabview_destructor_hook(lv_obj_t * obj);
void tabview_event_hook(lv_event_t * e);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void tabview_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void tabview_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void tabview_event(const lv_obj_class_t * class_p, lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t tabview_class = {
    .base_class = &lv_tabview_class,
    .constructor_cb = tabview_constructor,
    .destructor_cb = tabview_destructor,
    .event_cb = tabview_event,
    .instance_size = sizeof(tabview_t),
    .editable = 1,
    .name = "tabview"
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


lv_obj_t * tabview_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&tabview_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void tabview_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    tabview_t * widget = (tabview_t *)obj;
    
    static bool style_inited = false;

    if(!style_inited) {
        
        style_inited = true;
    }


    tabview_constructor_hook(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void tabview_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);

    tabview_destructor_hook(obj);
}

static void tabview_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /* Call the ancestor's event handler */
    res = lv_obj_event_base(&tabview_class, e);
    if(res != LV_RESULT_OK) return;

    tabview_event_hook(e);
}