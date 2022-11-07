cmake_minimum_required(VERSION 3.2)
set(CMAKE_C_OUTPUT_EXTENSION ".rel")
set(CMAKE_C_COMPILER sdcc)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_EXE_LINKER_FLAGS_INIT "")
project(STM8S103F3)

set(EXECUTABLE ${PROJECT_NAME})

set(SRC_FILES
        src/main.c
        src/stm8s_it.c
        src/gpio.c
        src/tick.c
        src/log.c
        src/uart.c
)

add_executable(${EXECUTABLE} ${SRC_FILES})

target_include_directories(${EXECUTABLE} PRIVATE
        src/
        spl/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/inc
)

target_compile_definitions(${EXECUTABLE} PRIVATE 
        -DSTM8S103
)

target_compile_options(${EXECUTABLE} PRIVATE
        --opt-code-size
        -mstm8 
        --std-c99
        --all-callee-saves 
        --stack-auto 
        --fverbose-asm  
)

target_link_options(${EXECUTABLE} PRIVATE
        -mstm8 
        --std-c99
)

add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size --target=ihex "${EXECUTABLE}.ihx"
)