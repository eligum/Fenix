# Set the final executable name
set(MY_TARGET_NAME "sandbox.exe")

add_executable("${MY_TARGET_NAME}" main.cc
                                   dummy1.cc
                                   dummy2.cc
                                   dummy3.cc)
