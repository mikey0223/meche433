add_executable(main
        main.c
        usb_descriptors.c
        usb_descriptors.h
        tusb_config.h
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(main PUBLIC
${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(main PUBLIC pico_stdlib hardware_i2c
                pico_unique_id tinyusb_device tinyusb_board)

#maps the printf function
# pico_enable_stdio_usb(main 1)
# pico_enable_stdio_uart(main 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url
example_auto_set_url(main)
