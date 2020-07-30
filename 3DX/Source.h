#pragma once
#include <memory>
#include <string>
#include "RenderTarget.h"


class Source
{
public:

	
	const std::string& GetName() const;
	virtual std::shared_ptr<BufferResource> GetSource();
	virtual ~Source() = default;
	//std::string& GetSinkName() const;
protected:
	Source(std::string sourceName);
private:
	std::string sourceName;

};

template <class T>
class DirectBufferSource : public Source
{

public:
	static std::unique_ptr<DirectBufferSource> Make(std::string name, std::shared_ptr<T>& target)
	{
		return std::make_unique<DirectBufferSource>(std::move(name), target);
	}
	DirectBufferSource(std::string name, std::shared_ptr<T>& target) : Source(name),directSource(target)
	{}
	std::shared_ptr<BufferResource> GetSource() override
	{
		isLinked = true;
		return directSource;
	}
private:
	bool isLinked = false;
	std::shared_ptr<T>& directSource;

};


template <class T>
class BindableBufferSource : public Source
{
public:
	static std::unique_ptr<BindableBufferSource> Make(std::string name, std::shared_ptr<T>& source)
	{
		return std::make_unique<BindableBufferSource>(std::move(name), source);
	}
	BindableBufferSource(std::string name, std::shared_ptr<T>& source) : Source(std::move(name)), bindableSource(source)
	{}
	/*std::shared_ptr<BufferResource> GetSource() override
	{
		isLinked = true;
		return bindableSource;
	}*/
private:
	bool isLinked = false;
	std::shared_ptr<T>& bindableSource;
};

