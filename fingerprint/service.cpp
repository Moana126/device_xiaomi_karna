/*
 * Copyright (C) 2017 The Android Open Source Project
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.1-service.surya"

#include <android/log.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/biometrics/fingerprint/2.1/IBiometricsFingerprint.h>
#include <android/hardware/biometrics/fingerprint/2.1/types.h>
#include "BiometricsFingerprint.h"

using android::hardware::biometrics::fingerprint::V2_1::IBiometricsFingerprint;
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;

using android::status_t;

status_t BiometricsFingerprint::registerAsSystemService() {
    status_t ret = 0;

    ret = IBiometricsFingerprint::registerAsService();
    if (ret != 0) {
        ALOGE("Failed to register IBiometricsFingerprint (%d)", ret);
        goto fail;
    } else {
        ALOGI("Successfully registered IBiometricsFingerprint");
    }

fail:
    return ret;
}

int main() {
    android::sp<BiometricsFingerprint> service = nullptr;

    service = new BiometricsFingerprint();
    if (service == nullptr) {
        ALOGE("Instance of BiometricsFingerprint is null");
        return 1;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status_t status = service->registerAsSystemService();
    if (status != android::OK) {
        ALOGE("Cannot register service for Fingerprint HAL(%d).", status);
        return 1;
    }

    joinRpcThreadpool();

    return 0; // should never get here
}
