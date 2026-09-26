# In that same example, if you added `INTERFACE`:

# ```cmake
# add_library(core src/core.cpp)
# target_include_directories(core
#     PUBLIC    include
#     PRIVATE   src/internal
#     INTERFACE some/other/dir
# )
# ```

# `some/other/dir` would be added to the include path **only for targets that link against `core`** (like `dashboard`) — `core`'s own `src/core.cpp` would *not* get that path when it's being compiled.

# That's the whole distinguishing feature of `INTERFACE` vs `PUBLIC`:

# | Keyword | Applies to `core`'s own `.cpp` files | Applies to consumers (e.g. `dashboard`) |
# |---|---|---|
# | `PRIVATE` | ✅ | ❌ |
# | `PUBLIC` | ✅ | ✅ |
# | `INTERFACE` | ❌ | ✅ |

# **A realistic case where this shows up:** say `core` generates a header at build time (e.g., a version header written to `${CMAKE_BINARY_DIR}/generated`) that `core.cpp` itself doesn't `#include`, but consumers of `core` are expected to `#include` it. You'd mark that directory `INTERFACE` — `core` doesn't need it to compile itself, but anything linking `core` does.

# In your project right now, you don't have this situation — you'd only reach for `INTERFACE` once you have a library target where the library's own source files don't need something that its consumers do.
# The mental model: PRIVATE/PUBLIC/INTERFACE aren't describing "who is allowed to use this path." They're describing two separate property lists that CMake maintains on every target:

# The build-time property — used when compiling that target's own .cpp files.
# The usage-requirement property — attached to the target's export/link interface, handed to anything that does target_link_libraries(other_target PRIVATE/PUBLIC core).
# PRIVATE → sets only property (1)
# PUBLIC → sets both (1) and (2)
# INTERFACE → sets only property (2)

# So INTERFACE literally means "don't add this to my own compile command, only add it to my consumers' compile command." CMake will happily let you do this even though it seems odd for a library not to use its own declared include path.

# Why this is actually useful (not just an edge case): the classic real example is a header-only library:

# cmake
# add_library(MyHeaderOnlyLib INTERFACE)
# target_include_directories(MyHeaderOnlyLib INTERFACE include)

# Here MyHeaderOnlyLib has no .cpp files at all — there's no "own compilation" to apply the path to. It exists purely to bundle up requirements for whoever links it. INTERFACE is the only keyword that makes sense in that case, since PRIVATE and PUBLIC would try to apply to a compile step that doesn't exist.

# For a target that does have its own .cpp files (like core in our example), using INTERFACE on a specific path is rarer but shows up when: core.cpp doesn't need that header directory itself, but you want it forwarded to anyone linking core — e.g., a generated-headers folder, or a directory containing a shim intended only for downstream code, not for core's own implementation.

# For your project right now, with a single executable, you'll basically never write INTERFACE — it only matters once you have multi-target dependency chains.

add_library(telemetry_core INTERFACE)
target_include_directories(telemetry_core INTERFACE include)
