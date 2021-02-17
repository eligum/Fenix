# Prints the value of all the variables passed
function(print)
    foreach(var IN LISTS "${ARGN}")
        message("${var} = ${${var}}")
    endforeach()
endfunction()
