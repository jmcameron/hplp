/*
 * libhpcables: hand-helds support libraries.
 * Copyright (C) 2013 Lionel Debroux
 * Code patterns and snippets borrowed from libticables & libticalcs:
 * Copyright (C) 1999-2009 Romain Li�vin
 * Copyright (C) 2009-2013 Lionel Debroux
 * Copyright (C) 1999-2013 libti* contributors.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * \file link_prime_hid.h Cables: Prime HID cable.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <hplibs.h>
#include <hpcalcs.h>
#include "logging.h"

#include <hidapi/hidapi.h>

extern const cable_fncts cable_prime_hid_fncts;

static int cable_prime_hid_open (cable_handle * handle) {
    int res = -1;
    if (handle != NULL) {
        hid_device * device_handle = hid_open(USB_VID_HP, USB_PID_PRIME, NULL);
        if (device_handle) {
            handle->model = CABLE_PRIME_HID;
            handle->handle = (void *)device_handle;
            handle->fncts = &cable_prime_hid_fncts;
            handle->read_timeout = 500;
            handle->open = 1;
            handle->busy = 0;
            res = 0;
            hpcables_error("%s: cable open succeeded", __FUNCTION__);
        }
        else {
            hpcables_error("%s: cable open failed", __FUNCTION__);
        }
    }
    else {
        hpcables_error("%s: handle is NULL", __FUNCTION__);
    }
    return res;
}

static int cable_prime_hid_close (cable_handle * handle) {
    int res = -1;
    if (handle != NULL) {
        hid_device * device_handle = (hid_device *)handle->handle;
        if (device_handle != NULL) {
            hid_close(device_handle);
            res = 0;
            hpcables_error("%s: cable close succeeded", __FUNCTION__);
        }
        else {
            hpcables_error("%s: device_handle is NULL", __FUNCTION__);
        }
    }
    else {
        hpcables_error("%s: handle is NULL", __FUNCTION__);
    }
    return res;
}

static int cable_prime_hid_send (cable_handle * handle, uint8_t * data, uint32_t len) {
    int res = -1;
    if (handle != NULL && data != NULL) {
        hid_device * device_handle = (hid_device *)handle->handle;
        if (device_handle != NULL) {
            res = hid_write(device_handle, data, len);
            if (res >= 0) {
                hpcables_info("%s: wrote %d bytes", __FUNCTION__, res);
                res = 0; // Indicate success.
            }
            else {
                hpcables_error("%s: write failed %ls", __FUNCTION__, hid_error(device_handle));
            }
        }
        else {
            hpcables_error("%s: device_handle is NULL", __FUNCTION__);
        }
    }
    else {
        hpcables_error("%s: an argument is NULL", __FUNCTION__);
    }
    return res;
}

static int cable_prime_hid_recv (cable_handle * handle, uint8_t * data, uint32_t * len) {
    int res = -1;
    if (handle != NULL && data != NULL && len != NULL) {
        hid_device * device_handle = (hid_device *)handle->handle;
        if (device_handle != NULL) {
            res = hid_read_timeout(device_handle, data, PRIME_RAW_DATA_SIZE, handle->read_timeout);
            if (res >= 0) {
                hpcables_info("%s: read %d bytes", __FUNCTION__, res);
                *len = res;
                res = 0; // Indicate success
            }
            else {
                hpcables_error("%s: read failed", __FUNCTION__);
            }
        }
        else {
            hpcables_error("%s: device_handle is NULL", __FUNCTION__);
        }
    }
    else {
        hpcables_error("%s: an argument is NULL", __FUNCTION__);
    }
    return res;
}

const cable_fncts cable_prime_hid_fncts =
{
    CABLE_PRIME_HID,
    "Prime HID cable",
    "Prime HID cable",
    &cable_prime_hid_open,
    &cable_prime_hid_close,
    &cable_prime_hid_send,
    &cable_prime_hid_recv
};