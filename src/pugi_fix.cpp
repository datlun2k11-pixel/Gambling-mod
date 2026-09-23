// Dummy fix for pugi::xml_node destructor linker error
// We provide the mangled destructor symbol directly without including any headers
// to avoid redefinition errors. This satisfies the linker when bindings are patched.

#ifdef _WIN32
// Windows MSVC mangling: ??1xml_node@pugi@@QEAA@XZ
namespace pugi {
    class xml_node {
    public:
        ~xml_node();
    };
}
pugi::xml_node::~xml_node() {}
#else
// Itanium ABI (Linux/macOS/Android/iOS) uses _ZN4pugi8xml_nodeD1Ev / D2Ev
extern "C" void _ZN4pugi8xml_nodeD1Ev(void* self) {}
extern "C" void _ZN4pugi8xml_nodeD2Ev(void* self) {}
#endif
