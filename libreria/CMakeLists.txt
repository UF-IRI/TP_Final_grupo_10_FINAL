## >>>>>>>>>>>>>>>
## >>>>>>>>>>>>>>>
add_library(libreria Funciones.cpp "Funciones.h")
## <<<<<<<<<<<<<<<
## <<<<<<<<<<<<<<<

target_include_directories(libreria PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
