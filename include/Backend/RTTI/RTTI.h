#pragma once
#include <Backend/Types.h>

namespace PKMD::Backend
{
    class RTTI
    {
    public:
        using IdType = std::size_t;

        RTTI() = default;
        RTTI(const RTTI&) = default;
        RTTI& operator=(const RTTI&) = default;
        RTTI(RTTI&&) noexcept = default;
        RTTI& operator=(RTTI&&) noexcept = default;
        virtual ~RTTI() = default;

        virtual IdType TypeIdInstance() const = 0;
        virtual bool Is(IdType) const;

        template <typename T>
        T* As();

        template <typename T>
        const T* As() const;

        virtual std::string ToString() const;
        virtual bool Equals(const RTTI* rhs) const;
    };
}

#define RTTI_DEFINITIONS(Type)                                                                                              \
    const PKMD::Backend::RTTI::IdType Type::_typeId = reinterpret_cast<PKMD::Backend::RTTI::IdType>(&Type::_typeId)

#define RTTI_DECLARATIONS(Type, ParentType)                                                                             \
    public:                                                                                                             \
        static std::string TypeName() { return std::string(#Type); }                                                    \
        static PKMD::Backend::RTTI::IdType TypeIdClass() { return _typeId; }                                             \
        PKMD::Backend::RTTI::IdType TypeIdInstance() const override { return TypeIdClass(); }                            \
        bool Is(PKMD::Backend::RTTI::IdType id) const override { return (id == _typeId ? true : ParentType::Is(id)); }   \
    private:                                                                                                            \
        static const PKMD::Backend::RTTI::IdType _typeId



#include <Backend/RTTI/RTTI.inl>