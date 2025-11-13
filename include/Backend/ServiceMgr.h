#pragma once
#include <Backend/Types.h>

// Borrowed from https://github.com/Amogh2211/FieaGameEngine/blob/main/FieaGameEngine/include/FieaGameEngine/ServiceMgr.h
// It is my own code but just wanted to credit hehe


// ------------- Types define for function pointers -----------------

// Create func takes no parameters but returns a void*
using CreateFunc = void* (*) ();
// Destroy takes a void* parameter but returns void
using DestroyFunc = void (*) (void*);
// Provide Func takes a void* parameter but also returns a void*
using ProvideFunc = void* (*) (void*);


/// ------------------- Bindings Start ---------------------------------

using InterfaceID = size_t;
#define PKMD_SERVICE_INTERFACE             \
static inline InterfaceID GetInterfaceId() \
{                                          \
    static char _unused{};                 \
    return (InterfaceID)&_unused;          \
}                                          \


#define PKMD_SERVICE_BIND1(_impl, _intf)                                                                                              \
static bool _Register()                                                                                                               \
{                                                                                                                                     \
    auto& manager = ServiceManager::Instance();                                                                                       \
    CreateFunc create = []()->void*{ return new _impl();};                                                                            \
    DestroyFunc destroy = [](void* service){delete static_cast<_impl*>(service);};                                                    \
    ProvideFunc provide = [](void* service) -> void*{return static_cast<_intf*>(static_cast<_impl*>(service));};                      \
    manager.RegisterInterfaceProvider<_intf>(create, destroy, provide);                                                               \
    return true;                                                                                                                      \
}                                                                                                                                     \
static inline bool registered = _Register();                                                                                          \

#define PKMD_SERVICE_BIND2(_impl, _intf1, _intf2)                                                                                     \
static bool _Register()                                                                                                               \
{                                                                                                                                     \
    auto& manager = ServiceManager::Instance();                                                                                       \
    CreateFunc create = []()->void*{ return new _impl();};                                                                            \
    DestroyFunc destroy = [](void* service){delete static_cast<_impl*>(service);};                                                    \
    ProvideFunc provide1 = [](void* service) -> void*{return static_cast<_intf1*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide2 = [](void* service) -> void*{return static_cast<_intf2*>(static_cast<_impl*>(service));};                    \
    manager.RegisterInterfaceProvider<_intf1>(create, destroy, provide1);                                                             \
    manager.RegisterInterfaceProvider<_intf2>(create, destroy, provide2);                                                             \
    return true;                                                                                                                      \
}                                                                                                                                     \
static inline bool registered = _Register();                                                                                          \


#define PKMD_SERVICE_BIND3(_impl, _intf1, _intf2, _intf3)                                                                             \
static bool _Register()                                                                                                               \
{                                                                                                                                     \
    auto& manager = ServiceManager::Instance();                                                                                       \
    CreateFunc create    = []()->void*{ return new _impl();};                                                                         \
    DestroyFunc destroy  = [](void* service){delete static_cast<_impl*>(service);};                                                   \
    ProvideFunc provide1 = [](void* service) -> void*{return static_cast<_intf1*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide2 = [](void* service) -> void*{return static_cast<_intf2*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide3 = [](void* service) -> void*{return static_cast<_intf3*>(static_cast<_impl*>(service));};                    \
    manager.RegisterInterfaceProvider<_intf1>(create, destroy, provide1);                                                             \
    manager.RegisterInterfaceProvider<_intf2>(create, destroy, provide2);                                                             \
    manager.RegisterInterfaceProvider<_intf3>(create, destroy, provide3);                                                             \
    return true;                                                                                                                      \
}                                                                                                                                     \
static inline bool registered = _Register();                                                                                          \

#define PKMD_SERVICE_BIND4(_impl, _intf1, _intf2, _intf3, _intf4)                                                                             \
static bool _Register()                                                                                                               \
{                                                                                                                                     \
    auto& manager = ServiceManager::Instance();                                                                                       \
    CreateFunc create    = []()->void*{ return new _impl();};                                                                         \
    DestroyFunc destroy  = [](void* service){delete static_cast<_impl*>(service);};                                                   \
    ProvideFunc provide1 = [](void* service) -> void*{return static_cast<_intf1*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide2 = [](void* service) -> void*{return static_cast<_intf2*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide3 = [](void* service) -> void*{return static_cast<_intf3*>(static_cast<_impl*>(service));};                    \
    ProvideFunc provide4 = [](void* service) -> void*{return static_cast<_intf4*>(static_cast<_impl*>(service));};                    \
    manager.RegisterInterfaceProvider<_intf1>(create, destroy, provide1);                                                             \
    manager.RegisterInterfaceProvider<_intf2>(create, destroy, provide2);                                                             \
    manager.RegisterInterfaceProvider<_intf3>(create, destroy, provide3);                                                             \
    manager.RegisterInterfaceProvider<_intf4>(create, destroy, provide4);                                                             \
    return true;                                                                                                                      \
}                                                                                                                                     \
static inline bool registered = _Register();                                                                                          \

/// ------------------- Bindings End ---------------------------------

namespace PKMD::Backend
{
    class ServiceMgr : Singleton<ServiceMgr>
	{
    public:
        /// @brief Helper to get an access to the instance
        /// @return Singleton ServiceMgr object
        static ServiceMgr& GetInstance()
        {
            static ServiceMgr instance ;
            return instance;
        }
        
        /// @brief Creates a mapping from and InterfaceId to a ServiceProvider struct
        /// @tparam I 
        /// @param create 
        /// @param destroy 
        /// @param provide 
        template <typename I>
        void RegisterInterfaceProvider(CreateFunc create, DestroyFunc destroy, ProvideFunc provide)
        {
            InterfaceID id = I::GetInterfaceId();
            _providers[id] = { create, destroy, provide };
        }

        
        /// @brief Create an implementation, and return as the requested interface type
        /// @tparam I 
        /// @return 
        template<typename I>
        static I* ProvideInterface()
        {
            //ServiceManager& sm = Instance();
            InterfaceID id = I::GetInterfaceId();

            auto& tempProviders = Instance()._providers;

            std::unordered_map<InterfaceID, ServiceProvider>::iterator it = tempProviders.find(id);
            if (it == tempProviders.end())
            {
                return nullptr; // Interface not registered
            }

            const ServiceProvider& provider = it->second;
            void* implementation = GetImplementation(provider);
            return static_cast<I*>(provider.Provide(implementation));
        }

        


    private:
        ServiceMgr() = default;

        struct ServiceProvider
        {
            CreateFunc Create;
            DestroyFunc Destroy;
            ProvideFunc Provide;
        };

        // std::unordered_map for storage and provide methods for registration and interface provision
        std::unordered_map<InterfaceID, ServiceProvider> _providers;
        std::unordered_map<CreateFunc, void*> _implementations;

        // Helper to get or create an implementation
        static void* GetImplementation(const ServiceProvider& provider)
        {
            CreateFunc id = provider.Create;
            ServiceMgr& mgr = ServiceMgr::GetInstance();
            auto& tempImplementations = mgr._implementations;

            auto it = tempImplementations.find(id);
            if (it != tempImplementations.end())
            {
                return it->second; // Return existing implementation
            }

            // Create a new implementation
            void* implementation = provider.Create();
            tempImplementations[id] = implementation;
            return implementation;
        }

	};
}
