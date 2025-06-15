/**
 * @file jog_interface_gen.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "jog_interface_private_gen.h"
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

void jog_interface_constructor_hook(lv_obj_t * obj);
void jog_interface_destructor_hook(lv_obj_t * obj);
void jog_interface_event_hook(lv_event_t * e);

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void jog_interface_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void jog_interface_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void jog_interface_event(const lv_obj_class_t * class_p, lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t jog_interface_class = {
    .base_class = &lv_obj_class,
    .constructor_cb = jog_interface_constructor,
    .destructor_cb = jog_interface_destructor,
    .event_cb = jog_interface_event,
    .instance_size = sizeof(jog_interface_t),
    .editable = 1,
    .name = "jog_interface"
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


lv_obj_t * jog_interface_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&jog_interface_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/


static void jog_interface_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    jog_interface_t * widget = (jog_interface_t *)obj;
    
    static bool style_inited = false;

    if(!style_inited) {
        
        style_inited = true;
    }
    lv_obj_set_width(obj, lv_pct(100));

    lv_obj_t * lv_buttonmatrix_1 = lv_buttonmatrix_create(obj);
    lv_obj_set_align(lv_buttonmatrix_1, LV_ALIGN_CENTER);
    lv_buttonmatrix_set_map(lv_buttonmatrix_1, (const char *[]){" ", "^", " ", "\n", "<", "GO", ">", "\n", " ", "v", " ", "", NULL});
    lv_buttonmatrix_set_ctrl_map(lv_buttonmatrix_1, (const lv_buttonmatrix_ctrl_t[]) {LV_BUTTONMATRIX_CTRL_HIDDEN, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_HIDDEN, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_HIDDEN, LV_BUTTONMATRIX_CTRL_NONE, LV_BUTTONMATRIX_CTRL_HIDDEN, LV_BUTTONMATRIX_CTRL_NONE});
    widget->lv_buttonmatrix_1 = lv_buttonmatrix_1;

    jog_interface_constructor_hook(obj);

    LV_TRACE_OBJ_CREATE("finished");
}

static void jog_interface_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);

    jog_interface_destructor_hook(obj);
}

static void jog_interface_event(const lv_obj_class_t * class_p, lv_event_t * e)
{
    LV_UNUSED(class_p);

    lv_result_t res;

    /* Call the ancestor's event handler */
    res = lv_obj_event_base(&jog_interface_class, e);
    if(res != LV_RESULT_OK) return;

    jog_interface_event_hook(e);
}