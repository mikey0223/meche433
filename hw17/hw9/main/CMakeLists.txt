add_executable(main
        main.c
        ssd1306.c
        ssd1306.h
        font.h
        )

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_i2c hardware_adc hardware_pwm)

#maps the printf function
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(main)

# add url via pico_set_program_url
example_auto_set_url(main)
