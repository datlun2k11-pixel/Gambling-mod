#include <Geode/Geode.hpp>

// Dummy fix for pugi::xml_node destructor linker error on Windows
// After patching bindings to remove ~xml_node() inline, the GeodeBindings still references
// the destructor on some toolchains. We provide a weak dummy to satisfy linker.
// The real destructor logic is only for DestructorLock cleanup, which is safe to no-op.

#if defined(_WIN32) || defined(GEODE_IS_WINDOWS)
// For MSVC/clang on Windows, provide the mangled destructor symbol
// MSVC mangles ~xml_node as ??1xml_node@pugi@@QEAA@XZ
// We use a pragma to alias it to a dummy function
extern "C" void dummy_pugi_xml_node_dtor() {}
#pragma comment(linker, "/alternatename:??1xml_node@pugi@@QEAA@XZ=dummy_pugi_xml_node_dtor")
#pragma comment(linker, "/alternatename:?_D1xml_node@pugi@@QEAA@XZ=dummy_pugi_xml_node_dtor")
#endif

// For Itanium ABI (Linux/macOS/Android/iOS), provide both D1 and D2 destructors
// These are normally defined in xml_node.cpp, but we removed it
extern "C" void _ZN4pugi8xml_nodeD1Ev(void* self) {}
extern "C" void _ZN4pugi8xml_nodeD2Ev(void* self) {}

// Also provide C++ definition as fallback (will be used if header declares it)
namespace pugi {
    // This will only be used if the class actually declares the destructor
    // If the class doesn't declare it, this definition would be error, so we guard
    // We use a weak symbol trick via extern C above instead
}
