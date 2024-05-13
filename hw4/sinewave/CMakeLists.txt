add_executable(sinewave
        sinewave.c
        )

# pull in common dependencies
target_link_libraries(sinewave pico_stdlib hardware_spi)

#maps the printf function
pico_enable_stdio_usb(sinewave 1)
pico_enable_stdio_uart(sinewave 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(sinewave)

# add url via pico_set_program_url
example_auto_set_url(sinewave)
