//
// Role.h
//
// This file has been generated from sample.xml. Do not edit.
//


#ifndef Sample_Role_INCLUDED
#define Sample_Role_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"


namespace Sample {


class Role: public Poco::ActiveRecord::ActiveRecord<Poco::Int16>
{
public:
	using Ptr = Poco::AutoPtr<Role>;

	explicit Role(ID id);
	Role() = default;
	Role(const Role& other);
	~Role() = default;

	const std::string& name() const;
	Role& name(const std::string& value);

	const std::string& description() const;
	Role& description(const std::string& value);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	std::string _name;
	std::string _description;

	friend class Poco::Data::TypeHandler<Role>;
};


inline const std::string& Role::name() const
{
	return _name;
}


inline Role& Role::name(const std::string& value)
{
	_name = value;
	return *this;
}


inline const std::string& Role::description() const
{
	return _description;
}


inline Role& Role::description(const std::string& value)
{
	_description = value;
	return *this;
}


} // namespace Sample


namespace Poco {
namespace Data {


template <>
class TypeHandler<Sample::Role>
{
public:
	static std::size_t size()
	{
		return 2;
	}

	static void bind(std::size_t pos, const Sample::Role& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<std::string>::bind(pos++, ar._name, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._description, pBinder, dir);
}

	static void extract(std::size_t pos, Sample::Role& ar, const Sample::Role& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<std::string>::extract(pos++, ar._name, deflt._name, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._description, deflt._description, pExtr);
}

	static void prepare(std::size_t pos, const Sample::Role& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<std::string>::prepare(pos++, ar._name, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._description, pPrep);
	}
};


} } // namespace Poco::Data


#endif // Sample_Role_INCLUDED
