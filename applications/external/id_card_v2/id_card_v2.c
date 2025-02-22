#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/widget.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <stdlib.h>
#include <string.h>
#include <flipper_format/flipper_format.h>

#define TAG "ID"
#define ID_SAVE_PATH EXT_PATH("id.txt")
#define TEXT_BUFFER_SIZE 256

typedef enum {
    IDScenesMainMenuScene,
    IDScenesIDCardScene,
    IDScenesGreetingInputScene,
    IDScenesGreetingMessageScene,
    IDScenesAboutScene,
    IDScenesSceneCount,
} IDScenesScene;

typedef enum {
    IDScenesSubmenuView,
    IDScenesWidgetView,
    IDScenesTextInputView,
} IDScenesView;

typedef struct App {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* widget;
    TextInput* text_input;
    char* user_input;
    uint16_t user_input_size;
    bool user_input_available;
} App;

typedef enum {
    IDScenesMainMenuSceneIDCard,
    IDScenesMainMenuSceneSetup,
    IDScenesMainMenuSceneAbout,
} IDScenesMainMenuSceneIndex;

typedef enum {
    IDScenesMainMenuSceneIDCardEvent,
    IDScenesMainMenuSceneSetupEvent,
} IDScenesMainMenuEvent;

typedef enum {
    IDScenesGreetingInputSceneSaveEvent,
} IDScenesGreetingInputEvent;

void save_user_input(const char* filename, const char* input) {
    Storage* storage = (Storage*)furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);
    if(storage_file_open(file, filename, FSAM_WRITE, FSOM_CREATE_ALWAYS)) {
        storage_file_write(file, input, strlen(input));
        storage_file_close(file);
    }
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}

void load_user_input(const char* filename, char* buffer, size_t buffer_size) {
    Storage* storage = (Storage*)furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);
    if(storage_file_open(file, filename, FSAM_READ, FSOM_OPEN_EXISTING)) {
        uint16_t bytes_read = storage_file_read(file, buffer, buffer_size - 1);
        buffer[bytes_read] = '\0';
        storage_file_close(file);
    }
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
}

void id_menu_callback(void* context, uint32_t index) {
    App* app = context;
    switch(index) {
    case IDScenesMainMenuSceneIDCard:
        scene_manager_handle_custom_event(app->scene_manager, IDScenesMainMenuSceneIDCardEvent);
        break;
    case IDScenesMainMenuSceneSetup:
        scene_manager_handle_custom_event(app->scene_manager, IDScenesMainMenuSceneSetupEvent);
        break;
    case IDScenesMainMenuSceneAbout:
        scene_manager_next_scene(app->scene_manager, IDScenesAboutScene);
        break;
    }
}

bool id_main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    bool consumed = false;
    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case IDScenesMainMenuSceneIDCardEvent:
            scene_manager_next_scene(app->scene_manager, IDScenesIDCardScene);
            consumed = true;
            break;
        case IDScenesMainMenuSceneSetupEvent:
            scene_manager_next_scene(app->scene_manager, IDScenesGreetingInputScene);
            consumed = true;
            break;
        }
        break;
    default:
        break;
    }
    return consumed;
}

void id_main_menu_scene_on_enter(void* context) {
    App* app = context;
    submenu_reset(app->submenu);
    submenu_set_header(app->submenu, "ID Card v2");
    submenu_add_item(app->submenu, "ID Card", IDScenesMainMenuSceneIDCard, id_menu_callback, app);
    submenu_add_item(app->submenu, "Setup", IDScenesMainMenuSceneSetup, id_menu_callback, app);
    submenu_add_item(app->submenu, "About", IDScenesMainMenuSceneAbout, id_menu_callback, app);
    view_dispatcher_switch_to_view(app->view_dispatcher, IDScenesSubmenuView);
}
void id_main_menu_scene_on_exit(void* context) {
    App* app = context;
    submenu_reset(app->submenu);
}

void id_card_scene_on_enter(void* context) {
    App* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 5, 5, AlignLeft, AlignCenter, FontPrimary, "ID Card");

    load_user_input(ID_SAVE_PATH, app->user_input, app->user_input_size);

    char* input_copy = strdup(app->user_input);
    if(input_copy != NULL) {
        int y_position = 30;

        char* token = strtok(input_copy, "_");

        if(token != NULL && strcmp(token, "0") != 0) {
            widget_add_string_element(
                app->widget, 5, y_position, AlignLeft, AlignCenter, FontPrimary, "Name:");
            widget_add_string_element(
                app->widget, 55, y_position, AlignLeft, AlignCenter, FontPrimary, token);
            y_position += 10;
        }

        token = strtok(NULL, "_");
        if(token != NULL && strcmp(token, "0") != 0) {
            widget_add_string_element(
                app->widget, 5, y_position, AlignLeft, AlignCenter, FontPrimary, "Tel:");
            widget_add_string_element(
                app->widget, 55, y_position, AlignLeft, AlignCenter, FontPrimary, token);
            y_position += 10;
        }

        token = strtok(NULL, "_");
        if(token != NULL && strcmp(token, "0") != 0) {
            widget_add_string_element(
                app->widget, 5, y_position, AlignLeft, AlignCenter, FontPrimary, "Address:");
            widget_add_string_element(
                app->widget, 55, y_position, AlignLeft, AlignCenter, FontPrimary, token);
            y_position += 10;
        }

        token = strtok(NULL, "_");
        if(token != NULL && strcmp(token, "0") != 0) {
            widget_add_string_element(
                app->widget, 5, y_position, AlignLeft, AlignCenter, FontPrimary, "Notes:");
            widget_add_string_element(
                app->widget, 55, y_position, AlignLeft, AlignCenter, FontPrimary, token);
            y_position += 10;
        }

        free(input_copy);
    }

    view_dispatcher_switch_to_view(app->view_dispatcher, IDScenesWidgetView);
}

bool id_card_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}
void id_card_scene_on_exit(void* context) {
    UNUSED(context);
}

void id_text_input_callback(void* context) {
    App* app = context;
    scene_manager_handle_custom_event(app->scene_manager, IDScenesGreetingInputSceneSaveEvent);
}

void id_greeting_input_scene_on_enter(void* context) {
    App* app = context;
    bool clear_text = true;
    text_input_reset(app->text_input);
    text_input_set_header_text(app->text_input, "Enter name_tel_addr_notes");
    text_input_set_result_callback(
        app->text_input,
        id_text_input_callback,
        app,
        app->user_input,
        app->user_input_size,
        clear_text);
    view_dispatcher_switch_to_view(app->view_dispatcher, IDScenesTextInputView);
}

bool id_greeting_input_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    bool consumed = false;
    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == IDScenesGreetingInputSceneSaveEvent) {
            scene_manager_next_scene(app->scene_manager, IDScenesGreetingMessageScene);
            app->user_input_available = true;
            save_user_input(ID_SAVE_PATH, app->user_input);
            consumed = true;
        }
    }
    return consumed;
}
void id_greeting_input_scene_on_exit(void* context) {
    UNUSED(context);
}

void id_greeting_message_scene_on_enter(void* context) {
    App* app = context;
    widget_reset(app->widget);
    widget_add_string_element(
        app->widget, 64, 5, AlignCenter, AlignCenter, FontPrimary, "Changes Saved");
    view_dispatcher_switch_to_view(app->view_dispatcher, IDScenesWidgetView);
}
bool id_greeting_message_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}
void id_greeting_message_scene_on_exit(void* context) {
    App* app = context;
    widget_reset(app->widget);
}

void id_about_scene_on_enter(void* context) {
    App* app = context;
    widget_reset(app->widget);

    widget_add_string_element(
        app->widget, 5, 5, AlignLeft, AlignCenter, FontPrimary, "To leave the field empty,");
    widget_add_string_element(
        app->widget, 5, 15, AlignLeft, AlignCenter, FontPrimary, "for example,without Tel");
    widget_add_string_element(
        app->widget, 5, 25, AlignLeft, AlignCenter, FontPrimary, "name_0_address_notes");
    widget_add_string_element(
        app->widget, 5, 45, AlignLeft, AlignCenter, FontPrimary, "author:@evillero");
    view_dispatcher_switch_to_view(app->view_dispatcher, IDScenesWidgetView);
}

bool id_about_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}
void id_about_scene_on_exit(void* context) {
    App* app = context;
    widget_reset(app->widget);
}

void (*const id_scene_on_enter_handlers[])(void*) = {
    id_main_menu_scene_on_enter,
    id_card_scene_on_enter,
    id_greeting_input_scene_on_enter,
    id_greeting_message_scene_on_enter,
    id_about_scene_on_enter,
};

bool (*const id_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    id_main_menu_scene_on_event,
    id_card_scene_on_event,
    id_greeting_input_scene_on_event,
    id_greeting_message_scene_on_event,
    id_about_scene_on_event,
};

void (*const id_scene_on_exit_handlers[])(void*) = {
    id_main_menu_scene_on_exit,
    id_card_scene_on_exit,
    id_greeting_input_scene_on_exit,
    id_greeting_message_scene_on_exit,
    id_about_scene_on_exit,
};

static const SceneManagerHandlers id_scene_manager_handlers = {
    .on_enter_handlers = id_scene_on_enter_handlers,
    .on_event_handlers = id_scene_on_event_handlers,
    .on_exit_handlers = id_scene_on_exit_handlers,
    .scene_num = IDScenesSceneCount,
};

static bool id_scene_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

bool id_scene_back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

static App* app_alloc() {
    App* app = malloc(sizeof(App));
    app->user_input_size = 64;
    app->user_input = malloc(app->user_input_size);
    app->scene_manager = scene_manager_alloc(&id_scene_manager_handlers, app);
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(app->view_dispatcher);
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, id_scene_custom_callback);
    view_dispatcher_set_navigation_event_callback(
        app->view_dispatcher, id_scene_back_event_callback);
    app->submenu = submenu_alloc();
    view_dispatcher_add_view(
        app->view_dispatcher, IDScenesSubmenuView, submenu_get_view(app->submenu));
    app->widget = widget_alloc();
    view_dispatcher_add_view(
        app->view_dispatcher, IDScenesWidgetView, widget_get_view(app->widget));
    app->text_input = text_input_alloc();
    view_dispatcher_add_view(
        app->view_dispatcher, IDScenesTextInputView, text_input_get_view(app->text_input));
    app->user_input_available = false;
    load_user_input(ID_SAVE_PATH, app->user_input, app->user_input_size);
    return app;
}

static void app_free(App* app) {
    furi_assert(app);
    view_dispatcher_remove_view(app->view_dispatcher, IDScenesSubmenuView);
    view_dispatcher_remove_view(app->view_dispatcher, IDScenesWidgetView);
    view_dispatcher_remove_view(app->view_dispatcher, IDScenesTextInputView);
    scene_manager_free(app->scene_manager);
    view_dispatcher_free(app->view_dispatcher);
    submenu_free(app->submenu);
    widget_free(app->widget);
    text_input_free(app->text_input);
    free(app->user_input);
    free(app);
}

int32_t id_app(void* p) {
    UNUSED(p);
    App* app = app_alloc();

    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(app->scene_manager, IDScenesMainMenuScene);
    view_dispatcher_run(app->view_dispatcher);

    app_free(app);
    return 0;
}
