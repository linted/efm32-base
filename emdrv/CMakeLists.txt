
add_library(rtcdrv STATIC rtcdrv/src/rtcdriver.c)
target_include_directories(rtcdrv PUBLIC rtcdrv/inc/
                                         common/inc/
                                         rtcdrv/config)
target_link_libraries(rtcdrv PUBLIC emlib)
