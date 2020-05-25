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
#include <hidl/HidlTransportSupport.h>
#include <cmath>
#include <android-base/logging.h>
#include <fstream>

#define FINGERPRINT_ACQUIRED_VENDOR 6
#define FINGERPRINT_ERROR_VENDOR 8

#define OP_ENABLE_FP_LONGPRESS 3
#define OP_DISABLE_FP_LONGPRESS 4
#define OP_RESUME_FP_ENROLL 8
#define OP_FINISH_FP_ENROLL 10

#define OP_DISPLAY_AOD_MODE 8
#define OP_DISPLAY_NOTIFY_PRESS 9
#define OP_DISPLAY_SET_DIM 10

#define CMD_FINGERPRINT_EVENT 10

#define FOD_HBM_PATH "/sys/devices/platform/soc/soc:qcom,dsi-display-primary/fod_hbm"
#define FOD_HBM_ON 1
#define FOD_HBM_OFF 0

#define DC_STATUS_PATH "/sys/devices/platform/soc/soc:qcom,dsi-display-primary/msm_fb_ea_enable"
#define DC_STATUS_ON 1
#define DC_STATUS_OFF 0

#define BRIGHTNESS_PATH "/sys/class/backlight/panel0-backlight/brightness"

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
    this->mFodCircleVisible = false;
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
    set(FOD_HBM_PATH, FOD_HBM_ON);
    this->mVendorFpService->goodixExtendCommand(CMD_FINGERPRINT_EVENT, 1);
    

    return Void();
}

Return<void> FingerprintInscreen::onRelease() {
    set(FOD_HBM_PATH, FOD_HBM_OFF);
    this->mVendorFpService->goodixExtendCommand(CMD_FINGERPRINT_EVENT, 0);
  

    return Void();
}

Return<void> FingerprintInscreen::onShowFODView() {
    this->mFodCircleVisible = true;
    return Void();
}

Return<void> FingerprintInscreen::onHideFODView() {
    this->mFodCircleVisible = false;
    set(FOD_HBM_PATH, FOD_HBM_OFF);
    return Void();
}

Return<bool> FingerprintInscreen::handleAcquired(int32_t acquiredInfo, int32_t vendorCode) {
    LOG(ERROR) << "acquiredInfo: " << acquiredInfo << ", vendorCode: " << vendorCode << "\n";
    std::lock_guard<std::mutex> _lock(mCallbackLock);
    if (mCallback == nullptr) {
        return false;
    }
    
    if (acquiredInfo == FINGERPRINT_ACQUIRED_VENDOR) {
        if (mFodCircleVisible && vendorCode == 0) {
            Return<void> ret = mCallback->onFingerDown();
            if (!ret.isOk()) {
                LOG(ERROR) << "FingerDown() error: " << ret.description();
            }
            return true;
        }

        if (mFodCircleVisible && vendorCode == 1) {
            Return<void> ret = mCallback->onFingerUp();
            if (!ret.isOk()) {
                LOG(ERROR) << "FingerUp() error: " << ret.description();
            }
            return true;
        }
    }
    
    return false;
}

Return<bool> FingerprintInscreen::handleError(int32_t error, int32_t vendorCode) {
    LOG(ERROR) << "error: " << error << ", vendorCode: " << vendorCode << "\n";
    return false;
}

Return<void> FingerprintInscreen::setLongPressEnabled(bool) {
    return Void();
}

Return<int32_t> FingerprintInscreen::getDimAmount(int32_t)  {
    int realBrightness = get(BRIGHTNESS_PATH, 0);
    

    double dim = (255 + ((-12.08071) * pow((double)realBrightness, 0.4)));
    LOG(INFO) << "dimAmount = " << dim;
    return (int32_t)dim;
    
    

   
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
    return 178;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace inscreen
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace lineage
}  // namespace vendor
