//
// Created by aspgems on 17/11/22.
//


#include <iostream>
#include "../includes/EvDevHelper.h"

using namespace std;

int EvDevHelper::traktor_device_id = 0;

vector<string> EvDevHelper::get_evdev_device(){
    string path = "/dev/input";
    vector<string> dev_input_files;
    spdlog::debug("[EvDevHelper::get_evdev_device] Retrieving EVDEV Devices...");
    for (const auto & entry : filesystem::directory_iterator(path)){
        string uri = entry.path();
        if (uri.find("event") != string::npos)
            dev_input_files.push_back(uri);
    }
    spdlog::debug("[EvDevHelper::get_evdev_device] FINISHED");
    return dev_input_files;
}

tuple<int, struct libevdev *> EvDevHelper::get_traktor_controller_device(){
    spdlog::debug("[EvDevHelper::get_traktor_controller_device] Retrieving EVDEV Devices...");
    vector<string> uris = get_evdev_device();
    struct libevdev *dev = NULL;
    for (const string & file : uris){
        spdlog::debug("[EvDevHelper::get_traktor_controller_device] Trying to open {0} file...", file);
        const int fd = open(file.c_str(), O_RDONLY | O_NONBLOCK);
        spdlog::debug("[EvDevHelper::get_traktor_controller_device] FD obtained: {0}", fd);
        try{
            //auto evdev = evdevw::Evdev::create_from_fd(fd);
            int evdev = libevdev_new_from_fd(fd, &dev);
            if (evdev < 0) {
                spdlog::error("[EvDevHelper::get_traktor_controller_device] Failed to init libevdev ({0})", strerror(-evdev));
                exit(EXIT_FAILURE);
            }
            if ((libevdev_get_id_vendor(dev) == 0x17cc) && (libevdev_get_id_product(dev) == 0xbaff)){
                spdlog::debug("[EvDevHelper::get_traktor_controller_device] Found Traktor S4 Device: {0}", libevdev_get_name(dev));
                return make_tuple(evdev, dev);
            }
        }
        catch (const evdevw::Exception &e) {
            spdlog::error("[EvDevHelper::get_traktor_controller_device] Error Reading: {0} Error: {1}", file, strerror(e.get_error()));
        }
    }
    spdlog::debug("[EvDevHelper::get_traktor_controller_device] FINISHED");
    return make_tuple(-1, dev);
}

void EvDevHelper::read_events_from_device(RtMidiOut *pMidiOut) {
    spdlog::debug("[EvDevHelper::read_events_from_device] Reading events from Traktor Kontrol S4 Mk1");
    struct libevdev *dev = NULL;
    Button *buttons = new Button();
    int rc = 1;
    tie(rc, dev) = get_traktor_controller_device();
    if (rc < 0) {
        spdlog::error("[EvDevHelper::read_events_from_device] Failed to init libevdev (%s)", strerror(-rc));
        exit(EXIT_FAILURE);
    }
    spdlog::debug("Input device name: {0}", libevdev_get_name(dev));
    spdlog::debug("Input device ID: bus {0} vendor {1} product {2}",
           libevdev_get_id_bustype(dev),
           libevdev_get_id_vendor(dev),
           libevdev_get_id_product(dev));
    do {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if (rc >= 0){
            /*if (Button::buttons_mapping.find(ev.code) != Button::buttons_mapping.end()){
                unsigned int value = ev.value;
                if (value == 1){
                    value = 31;
                }
                else{
                    value = 10;
                }
                Button *btn_pressed = Button::buttons_mapping[ev.code];
                spdlog::info("KEY: {0} Value: {1} ", btn_pressed->name, value);
                if (btn_pressed->led_code >= 1){
                    string cmd = "amixer -c TraktorKontrolS cset numid=" + to_string(btn_pressed->led_code) + " " + to_string(value) + " > /dev/null";
                    system(cmd.c_str());
                }

                EvDevEvent *evdev_event = new EvDevEvent(ev.type, ev.code, ev.value, ev.time);
                evdev_e
                evdev_event->handle_event();

            }*/
            EvDevEvent *evdev_event = new EvDevEvent(ev.type, ev.code, ev.value, ev.time);
            evdev_event->handle_with(pMidiOut);
            /*spdlog::info("Event: TypeName: {0} - CodeName: {1} - Type: {2} - Code: {3} - Value: {4} - Time: {5}",
                   libevdev_event_type_get_name(ev.type),
                   libevdev_event_code_get_name(ev.type, ev.code),
                   ev.type,
                   ev.code,
                   ev.value,
                   ev.time.tv_sec);*/

        }
    } while (rc == 1 || rc == 0 || rc == -EAGAIN);
}

void EvDevHelper::initialize_buttons_leds(){
    spdlog::debug("[EvDevHelper::initialize_buttons_leds] Initializing controller leds....");
    int ctls[sizeof(Led::leds_mapping)];
    traktor_device_id = RtAudioHelper::get_traktor_device();
    spdlog::debug("[EvDevHelper::initialize_buttons_leds] Using device {0}", to_string(traktor_device_id));
    if (traktor_device_id != EXIT_FAILURE){
        map<int, Led *>::iterator it;
        int cont = 0;
        for (it = Led::leds_mapping.begin(); it !=Led::leds_mapping.end(); it++)
        {
            if (it->second->by_default == true) {
                spdlog::debug("[EvDevHelper::initialize_buttons_leds] Preparing for init Led Code {0}", to_string(it->second->code));
                ctls[cont] = it->second->code;
                if (((cont % 5) == 0) && (cont > 0)){
                    RtAudioHelper::bulk_led_value(traktor_device_id, ctls, Led::MIDDLE, cont + 1);
                    cont = 0;
                }
                else
                    cont++;
            }
        }
        RtAudioHelper::bulk_led_value(traktor_device_id, ctls, Led::MIDDLE, cont + 1);
    }
    else{
        spdlog::error("[EvDevHelper::initialize_buttons_leds] Cannot use {0} device", to_string(traktor_device_id));
        exit(EXIT_FAILURE);
    }
    spdlog::debug("[EvDevHelper::initialize_buttons_leds] FINISHED");
}

void EvDevHelper::shutdown_buttons_leds(){
    spdlog::debug("[EvDevHelper::shutdown_buttons_leds] Shutting down controller leds....");
    map<int, Led *>::iterator it;
    int ctls[sizeof(Led::leds_mapping)];
    int cont = 0;
    for (it = Led::leds_mapping.begin(); it != Led::leds_mapping.end(); it++)
    {
        ctls[cont] = it->second->code;
        spdlog::debug("Preparing for shutdown Led Code {0}", to_string(it->second->code));
        if (((cont % 5) == 0) && (cont > 0)){
            RtAudioHelper::bulk_led_value(traktor_device_id, ctls, Led::OFF, cont + 1);
            cont = 0;
        }
        else
            cont++;
    }
    RtAudioHelper::bulk_led_value(traktor_device_id, ctls, Led::OFF, cont + 1);
    spdlog::debug("[EvDevHelper::shutdown_buttons_leds] FINISHED");
}

