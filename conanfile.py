from conans import ConanFile, CMake


class KamiConan(ConanFile):
    name = "kami"
    version = "0.5.0"
    license = "MIT"
    author = "James P. Howard, II <james.howard@jhu.edu>"
    url = "https://github.com/jhuapl/kami"
    description = "Agent-Based Modeling in Modern C++"
    topics = ("agent-based modeling", "simulation", "orms")
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package"
    exports_sources = "*"

    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False}


    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.configure()
        return cmake


    def build(self):
        cmake = CMake(self) # it will find the packages by using our auto-generated FindXXX.cmake files
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        # These libraries are required when using the
        # following generators:
        #  cmake, cmake_paths, cmake_
        self.cpp_info.libs = ["kami"]


    def requirements(self):
        self.requires("fmt/7.1.3")
        self.requires("spdlog/1.8.5")
        self.requires("cli11/1.9.1")
        self.requires("neargye-semver/0.3.0")
        self.requires("gtest/cci.20210126")
        self.requires("nlohmann_json/3.11.1")
