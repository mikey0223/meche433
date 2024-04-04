add_executable(loop
        loop.c
        )

# pull in common dependencies
target_link_libraries(loop pico_stdlib hardware_adc)

#maps the printf function
pico_enable_stdio_usb(loop 1)
pico_enable_stdio_uart(loop 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(loop)

# add url via pico_set_program_url
example_auto_set_url(loop)
