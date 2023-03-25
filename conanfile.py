from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.build import check_min_cppstd
import os

class gclRecipe(ConanFile):
    name = "gcl"
    version = "0.9.1"

    # Optional metadata
    license = "<Put the package license here>"
    author = "<Put your name here> <And your email here>"
    url = "https://github.com/existedinnettw/google-concurrency-library"
    description = " Export several internal C++ Google concurrency libraries with modern building support"
    topics = ("gcl", "pipeline", "c++14")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "*.in", "src/*", "include/*", "samples/*", "testing/*"
    # exports_sources="./*"

    requires = (["openssl/[~3]", "zlib/[~1]"])  # >=1.0 <2.0
    # def requirements(self):
    #     self.requires(["openssl/[~3]", "zlib/[~1]"]) #>=1.0 <2.0 #not work

    def build_requirements(self):
        self.test_requires("gtest/[~1.12]")  # recipe forbid 13 for gcc5

    def validate(self):
        check_min_cppstd(self, "14")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            # test_folder = os.path.join("tests")
            # if self.settings.os == "Windows":
            #     test_folder = os.path.join("tests", str(self.settings.build_type))
            # self.run(os.path.join(test_folder, "test_hello"))
            cmake.test()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        '''
        conan package is relevent to cmake package. conan only get information of
        cmake target. And with have to make that target a conan package(libs) under following.
        '''
        self.cpp_info.libs = ["goocon"] # The libs to link against. still target_link_lib it by gcl::gcl
        # self.cpp_info.system_libs.append("pthread")
        # self.cpp_info.system_libs = []  # System libs to link against
        #another name to find_package
        #method1
        self.cpp_info.set_property("cmake_target_name", "gcl::goocon")
        #method2
        # self.cpp_info.components["goocon"].set_property("cmake_target_name", "gcl::goocon")
        # self.cpp_info.components["goocon"].libs=["goocon"]
        # self.cpp_info.components["goocon"].system_libs.append("pthread") #this work
        # self.cpp_info.components["goocon"].system_libs=self.cpp_info.system_libs #not work