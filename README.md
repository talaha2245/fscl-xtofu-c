# Fossil XToFu - `C`

Fossil XTofu serves as the foundational generic type for creating generic algorithms and data structures. This versatile library provides essential secure type checking, streamlining the development process and ensuring a solid framework for your flavorless applications.

## Prerequisites

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Setting up, Compiling, Installing, and Running the Project

**Adding Dependency**:

Create a directory named subprojects in the root directory, next create a file named `fscl-xtofu-c.wrap` in the `subprojects` directory of your project with the following content:

   ```ini
   [wrap-git]
   url = https://github.com/fossil-lib/fscl-xtofu-c.git
   revision = main
   
   [provide]
   fscl-xtofu-c = fscl_xtofu_c_dep
   ```

**Integrate Dependency**:
   ```meson
   project('my_project', 'c')

   exe = executable('my_project', 'my_project.c',
       dependencies : dependency('fscl-xtofu-c')) # add this line

   test('basic', exe)
   ```

## Configure Options

You have options when configuring the build, each serving a different purpose:

- **Running Tests**: To enable running tests, use `-Dwith_test=enabled` when configuring the build.

Example:

```python
meson setup builddir -Dwith_test=enabled
```

## Contributing and Support

If you're interested in contributing to this project, encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue or visit the [Fossil Logic Docs](https://fossillogic.com/the-docs) for more information.
