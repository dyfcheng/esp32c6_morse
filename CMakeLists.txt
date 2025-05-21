cmake_minimum_required(VERSION 3.16)

# ✅ Required to bring in ESP-IDF's custom build system
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# ✅ Must come AFTER include() to avoid misconfiguration
project(esp32c6_Morse VERSION 1.0.0)


# Note: ✅ When developing for firmware, Do not place project() before include() or the build will misbehave. 
# 	  	  This is different from for developing for desktop applications.
