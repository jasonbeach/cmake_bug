To observe correct behavior, comment out the lines in the toplevel `CMakeLists.txt` that add the libraries (lines 15 - 16) and make sure the similar lines in `src/Fuz/CMakeLists.txt` are uncommented (`good_example` branch). Then in the build directory
 
 ```
cmake -DCMAKE_INSTALL_PREFIX=../install ..
make install
vi ../install/lib/foo/FooTargets.cmake
```

and look down around line 58 at the `INTERFACE_LINK_LIBRARIES` and it should look like:

```
set_target_properties(apcl::Foo PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/Foo/Foo"
  INTERFACE_LINK_LIBRARIES "pthread;\$<LINK_ONLY:avcodec>;\$<LINK_ONLY:avformat>;\$<LINK_ONLY:avutil>;\$<LINK_ONLY:swscale>"
  INTERFACE_SOURCES "${_IMPORT_PREFIX}/include/Foo/Foo.hpp"
)
 ```

Then to see the bad behavior, comment out the `add_library` lines in `src/Fuz/CMakeLists.txt` and uncomment them in the top-level `CMakeLists.txt`  (i.e.` master` branch) and then from the top-level directory:

```
cd install
rm -rf *
cd ../build
rm -rf *
cmake -DCMAKE_INSTALL_PREFIX=../install ..
make install
vi ../install/lib/foo/FooTargets.cmake
```

and again look around line 58 at the `INTERFACE_LINK_LIBRARIES` and for me it looks like

```
set_target_properties(apcl::Foo PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include/Foo/Foo"
  INTERFACE_LINK_LIBRARIES "pthread;\$<LINK_ONLY:avcodec::@<0x1ca8af0>>;\$<LINK_ONLY:avformat::@<0x1ca8af0>>;\$<LINK_ONLY:avutil::@<0x1ca8af0>>;\$<LINK_ONLY:swscale::@<0x1ca8af0>>"
  INTERFACE_SOURCES "${_IMPORT_PREFIX}/include/Foo/Foo.hpp"
) 
```