#pragma once


#include <Backend/RTTI/RTTI.h>
#include <Backend/ServiceMgr.h>
#include <memory>


namespace PKMD::Backend
{
	struct IFactoryBase : public RTTI
	{
		RTTI_DECLARATIONS(IFactoryBase, RTTI);
	public:
		virtual std::string GetProductName() = 0;
		// Lookup by base type
		virtual RTTI::IdType GetBaseTypeId() const = 0;
	};

	template<typename T> struct IAbstractFactory : IFactoryBase
	{
		RTTI_DECLARATIONS(IAbstractFactory, IFactoryBase);

	public:
		[[nodiscard]] virtual T* Create() = 0;


		// Implement GetBaseTypeId() using RTTI
		virtual RTTI::IdType GetBaseTypeId() const override { return T::TypeIdClass(); }
	};

	struct IFactoryService
	{
		PKMD_SERVICE_INTERFACE;

	public:
		// Wrapper for register factory
		template<typename T>
		void Register(std::unique_ptr<IAbstractFactory<T>>&& concreteFactory);

		// thin wrapper for GetFactory, which calls Create if a factory is found
		template<typename T>
		T* Create(const std::string& productName);

	protected:
		// associate this factory with an abstract factory for the class w/ the given id
		virtual void RegisterFactory(RTTI::IdType baseId, std::unique_ptr<IFactoryBase>&& factory) = 0;
		// retrieve a factory associated with abstract factory for the class w/ the given id, matching the provided productName
		virtual IFactoryBase* GetFactory(RTTI::IdType baseId, const string& productName) = 0;
	};

	template<typename T>
	inline void IFactoryService::Register(std::unique_ptr<IAbstractFactory<T>>&& concreteFactory)
	{
		// Ensure valid pointer has been sent
		PKMD_ERROR(concreteFactory != nullptr);

		// Register this based on TypeID, 
		// move is used because std::unique_ptr does not support copy construction
		RegisterFactory(T::TypeIdClass(), std::move(concreteFactory));
	}

	template<typename T>
	T* IFactoryService::Create(const std::string& productName)
	{
		IFactoryBase* factoryBase = GetFactory(T::TypeIdClass(), productName);
		// Ensure successful lookup
		PKMD_ERROR(factoryBase != nullptr);

		// Cast to child, Abstract Factory
		auto* abstractFactory = static_cast<IAbstractFactory<T>*>(factoryBase);
		PKMD_ERROR(abstractFactory != nullptr);

		// Call type specifc create to get the correct class
		return abstractFactory->Create();
	}


	/// --------------- Macros for setting up C++ classes -----------------------
#define FACTORY_DECLARE(ProductType, BaseType) \
class ProductType##Factory : public IAbstractFactory<BaseType> { \
	public: \
	[[nodiscard]] virtual ProductType* Create();\
	virtual std::string GetProductName(); };\


#define FACTORY_DEFINE_ABSTRACT(BaseType)\
	RTTI_DEFINITIONS(IAbstractFactory<BaseType>);

#define FACTORY_DEFINE(ProductType) \
    ProductType* ProductType##Factory::Create() { return new ProductType(); } \
    std::string ProductType##Factory::GetProductName() { return ProductType::TypeName(); } \

}