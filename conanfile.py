from conans import ConanFile, CMake


class CppLibraryTemplateConan(ConanFile):
    name = "kami"
    version = "0.1.0"
    license = "Unlicense"
    author = "James P. Howard, II <james.howard@jhu.edu>"
    url = "http://github.com/GavinNL/cpp_library_template"
    description = "A simple C++ Library Template."
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "*"

    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}


    def _configure_cmake(self):
        cmake = CMake(self)

        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared

        cmake.configure()

        return cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        '''
            Create a package using "cmake --build . --target install"
            All installation files are defined in the CMakeLists.txt file rather
            than in the conan package.
        '''
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        # These libraries are required when using the
        # following generators:
        #  cmake, cmake_paths, cmake_
        self.cpp_info.libs = ["dog", "cat", "bar", "kami", "kamidata"]
