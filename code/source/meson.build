code = files('xtofu.c')

lib = static_library('fscl-xtofu-c',
    code,
    include_directories: dir)

fscl_xtofu_c_dep = declare_dependency(
    link_with: lib,
    include_directories: dir)
