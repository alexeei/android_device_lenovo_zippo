# Bluetooth
PRODUCT_PROPERTY_OVERRIDES += \
    persist.bluetooth.a2dp_offload.cap=sbc-aac-aptx-aptxhd-ldac  \
    persist.bluetooth.a2dp_offload.disabled=false  \
    persist.vendor.bt.aac_frm_ctl.enabled=false  \
    persist.vendor.btstack.a2dp_offload_cap=sbc-aptx-aptxtws-aptxhd-aptxadaptive-aac-ldac  \
    persist.vendor.btstack.connect.peer_earbud=true  \
    persist.vendor.btstack.enable.splita2dp=true \
    vendor.qcom.bluetooth.soc=cherokee


# Camera
PRODUCT_PROPERTY_OVERRIDES += \
    persist.camera.sat.fallback.dist=40 \
    persist.camera.sat.fallback.dist.d=10 \
    persist.camera.sat.fallback.luxindex=310 \
    persist.camera.sat.fallback.lux.d=50 \
    persist.vendor.camera.enableNCSService=TRUE \
    persist.vendor.camera.enableTOFInterface=TRUE \
    sys.camera.packagename.zui=1 \
    vendor.camera.aux.packagelist=org.codeaurora.snapcam,com.android.camera,org.lineageos.snap,com.zui.camera

# CNE and DPM
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.cne.feature=1 \
    persist.vendor.dpm.feature=1 \
    persist.vendor.dpm.nsrm.bkg.evt=3955

# Data Modules
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.data.mode=concurrent \
    ro.vendor.use_data_netmgrd=true

# Display
PRODUCT_PROPERTY_OVERRIDES += \
    ro.eyecare.brightness.threshold=11 \
    ro.eyecare.brightness.level=5 \
    ro.displayfeature.histogram.enable \
    ro.hist.brightness.threshold=7 \
    ro.sf.lcd_density=440 \
    sys.displayfeature.hbm.enable=true

# Graphics
PRODUCT_PROPERTY_OVERRIDES += \
    debug.sf.disable_backpressure=1 \
    debug.sf.enable_hwc_vds=1  \
    debug.mdpcomp.logs=0  \
    debug.gralloc.enable_fb_ubwc=1  \
    ro.hardware.egl=adreno  \
    ro.opengles.version=196610  \
    ro.hardware.vulkan=adreno  \
    vendor.gralloc.disable_ubwc=0  \
    debug.egl.hw=1   \
    debug.sf.hw=1

# GPS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.overlay.izat.optin=rro

# HWUI
PRODUCT_PROPERTY_OVERRIDES += \
ro.hwui.drop_shadow_cache_size=6  \
ro.hwui.gradient_cache_size=1  \
ro.hwui.layer_cache_size=48  \
ro.hwui.path_cache_size=32  \
ro.hwui.r_buffer_cache_size=8  \
ro.hwui.text_large_cache_height=1024  \
ro.hwui.text_large_cache_width=2048  \
ro.hwui.text_small_cache_height=1024  \
ro.hwui.text_small_cache_width=1024  \
ro.hwui.texture_cache_flushrate=0.4  \
ro.hwui.texture_cache_size=72

# IOP
PRODUCT_PROPERTY_OVERRIDES += \
    vendor.iop.enable_prefetch_ofr=0 \
    vendor.iop.enable_uxe=0

# Media
PRODUCT_PROPERTY_OVERRIDES += \
    media.settings.xml=/system/etc/media_profiles_vendor.xml \
    vendor.mm.enable.qcom_parser=63963135 \
    debug.stagefright.omx_default_rank.sw-audio=16

# Memory optimizations
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.qti.sys.fw.bservice_enable=true  \
    ro.vendor.qti.sys.fw.bservice_age=5000  \
    ro.vendor.qti.sys.fw.bservice_limit=8

# Netflix
PRODUCT_PROPERTY_OVERRIDES += \
    ro.netflix.bsp_rev=Q855-16947-1

# Perf
PRODUCT_PROPERTY_OVERRIDES += \
ro.vendor.qti.sys.fw.bg_apps_limit=60

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
    DEVICE_PROVISIONED=1 \
    rild.libpath=/vendor/lib64/libril-qc-hal-qmi.so \
    ril.subscription.types=RUIM \
    ro.telephony.default_cdma_sub=0 \
    ro.telephony.default_network=22,22 \
    persist.dbg.volte_avail_ovr=1 \
    persist.dbg.vt_avail_ovr=1 \
    persist.radio.NO_STAPA=1 \
    persist.radio.VT_CAM_INTERFACE=1 \
    persist.vendor.data.iwlan.enable=true \
    persist.vendor.radio.data_con_rprt=1 \
    persist.vendor.radio.force_on_dc=true \
    persist.vendor.radio.redir_party_num=1 \
    persist.vendor.radio.report_codec=1 \
    telephony.lteOnCdmaDevice=1

# RCS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.rcs.supported=0

# Sensors
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.sensors.enable.mag_filter=true

# Subsystem ramdump
PRODUCT_PROPERTY_OVERRIDES += \
    persist.vendor.ssr.restart_level=ALL_ENABLE

# SurfaceFlinger
PRODUCT_PROPERTY_OVERRIDES += \
ro.surface_flinger.has_wide_color_display=true  \
ro.surface_flinger.has_HDR_display=true  





# Set lmkd options
PRODUCT_PRODUCT_PROPERTIES += \
    ro.config.low_ram = false \
    ro.lmk.kill_heaviest_task = true \
    ro.lmk.kill_timeout_ms = 100 \
    ro.lmk.use_minfree_levels = true \
    ro.lmk.log_stats = true
    
# USB debugging
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp,adb \
    ro.adb.secure=0 \
    ro.secure=0 \
    ro.debuggable=1    

# WiFi Display
PRODUCT_PRODUCT_PROPERTIES += \
persist.debug.wfd.enable=1  \
persist.sys.wfd.virtual=0

#Memplus
PRODUCT_PRODUCT_PROPERTIES += \
persist.vendor.memplus.enable=1
