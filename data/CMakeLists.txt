############################################################################################################

cmake_minimum_required ( VERSION 3.3.0 FATAL_ERROR )
project ( "ExemplaryData")

############################################################################################################

# Find the Python3 interpreter
find_package ( Python3 REQUIRED COMPONENTS Interpreter ) 

# Add custom command to generate the exemplary data
add_custom_target ( GenExempData
                    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/GenExempData.py)

############################################################################################################