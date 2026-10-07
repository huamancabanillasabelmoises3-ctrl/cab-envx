# 1. Versión mínima requerida de CMake (Corregido 'minimum')
cmake_minimum_required(VERSION 3.15)

# 2. Configuración del proyecto
project(EnviromentCABX VERSION 1.0 LANGUAGES CXX)

# 3. Estándar de C++20 (Corregido 'STANDARD')
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Escaneo automático y dinámico de archivos en 'src' (Línea 14 completada)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 5. Crear el ejecutable usando la lista de archivos encontrados
add_executable(envx ${SOURCES})

# 6. Incluir la carpeta de cabeceras (¡No olvides esta para tus archivos .h!)
target_include_directories(envx PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
