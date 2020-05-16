/*
 * Copyright (C) 2019 The LineageOS Project
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

#define LOG_TAG "FingerprintInscreenService"

#include "FingerprintInscreen.h"

#include <unistd.h>
#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <hardware_legacy/power.h>
#include <fstream>

#define CMD_FINGERPRINT_EVENT 10

#define HBM_ENABLE_PATH "/sys/class/backlight/panel0-hbm/brightness"

#define DC_STATUS_PATH "/sys/devices/platform/soc/soc:qcom,dsi-display-primary/msm_fb_ea_enable"
#define DC_STATUS_ON 1
#define DC_STATUS_OFF 0

namespace vendor {
namespace lineage {
namespace biometrics {
namespace fingerprint {
namespace inscreen {
namespace V1_0 {
namespace implementation {

/*
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
    LOG(INFO) << "wrote path: " << path << ", value: " << value << "\n";
}

template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

FingerprintInscreen::FingerprintInscreen() {
    this->mVendorFpService = IGoodixFPExtendService::getService();
}

Return<void> FingerprintInscreen::onStartEnroll() {
    this->mVendorFpService->goodixExtendCommand(CMD_FINGERPRINT_EVENT, 1);
    return Void();
}

Return<void> FingerprintInscreen::onFinishEnroll() {
    return Void();
}

Return<void> FingerprintInscreen::onPress() {
    acquire_wake_lock(PARTIAL_WAKE_LOCK, LOG_TAG);
    this->shouldChangeDcStatus = false;
    if(1 == get(DC_STATUS_PATH,  0)) {
        set(DC_STATUS_PATH, DC_STATUS_OFF);
        this->shouldChangeDcStatus = true;
    }
	set(HBM_ENABLE_PATH, 1);
    this->mVendorFpService->goodixExtendCommand(CMD_FINGERPRINT_EVENT, 1);
    
    
    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    if(true == this->shouldChangeDcStatus) {
	set(DC_STATUS_PATH, DC_STATUS_ON);
	this->shouldChangeDcStatus = false;
    }
    this->mVendorFpService->goodixExtendCommand(CMD_FINGERPRINT_EVENT, 0);
    set(HBM_ENABLE_PATH, 0);
    release_wake_lock(LOG_TAG);
    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t acquiredInfo, int32_t vendorCode) {
    LOG(ERROR) << "acquiredInfo: " << acquiredInfo << ", vendorCode: " << vendorCode << "\n";
    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t error, int32_t vendorCode) {
    LOG(ERROR) << "error: " << error << ", vendorCode: " << vendorCode << "\n";
    return false;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t brightness) {
   # return 255 - brightness;
	return(int32_t)(255 * (1.0 - pow(brightness / 1023.0f, 0.455)));
	
	/*
	  float alpha;

    if (brightness > 62) {
        alpha = 1.0 - pow(brightness / 255.0 * 430.0 / 600.0, 0.45);
    } else {
        alpha = 1.0 - pow(brightness / 200.0, 0.45);
    }

    return 255 * alpha;
    */
	
	/*
	double dim = (255 + ((-12.08071) * pow((double)brightness, 0.4)));
    return (int32_t)dim;
    */
	
}

Return<bool> FingerprintInscreen::shouldBoostBrightness() {
    return false;
}

Return<void> FingerprintInscreen::setCallback(const sp<IFingerprintInscreenCallback>& callback) {
    {
        std::lock_guard<std::mutex> _lock(mCallbackLock);
        mCallback = callback;
    }

    return Void();
}

Return<int32_t> FingerprintInscreen::getPositionX() {
    return 450;
}

Return<int32_t> FingerprintInscreen::getPositionY() {
    return 1916;
}

Return<int32_t> FingerprintInscreen::getSize() {
    return 185;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace lineage
}  // namespace vendor
