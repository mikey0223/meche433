add_executable(trianglewave
        trianglewave.c
        )

# pull in common dependencies
target_link_libraries(trianglewave pico_stdlib hardware_spi)

#maps the printf function
pico_enable_stdio_usb(trianglewave 1)
pico_enable_stdio_uart(trianglewave 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(trianglewave)

# add url via pico_set_program_url
example_auto_set_url(trianglewave)
