from conans import ConanFile, CMake


class KamiConan(ConanFile):
    name = "kami"
    version = "0.2.0"
    author = "James P. Howard, II <james.howard@jhu.edu>"
    url = "http://github.com/GavinNL/cpp_library_template"
    description = "Agent-Based Modeling in Modern C++"
    topics = ("agent-based modeling", "simulation", "orms")
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

    def requirements(self):
        # Or add a new requirement!
        self.requires("spdlog/1.8.0")
        self.requires("cli11/1.9.1")
