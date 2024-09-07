file(GLOB _plugins *)

foreach(_current_plugin ${_plugins})
    if(IS_DIRECTORY ${_current_plugin})
       if(${_current_plugin} MATCHES "_codec_")  # TODO: Remove when other plugin work
          add_subdirectory(${_current_plugin})
       endif()
   endif(IS_DIRECTORY ${_current_plugin})
endforeach(_current_plugin)
