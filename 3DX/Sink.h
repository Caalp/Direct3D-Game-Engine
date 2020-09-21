#pragma once
#include "Source.h"

class Sink
{
public:

	Sink(std::string sinkName);
	void SetPassName(std::string passName);
	void SetTargetName(std::string targetName);
	const std::string& GetRegisteredName() const;
	const std::string& GetPassName() const;
	const std::string& GetTargetName() const;
	virtual void Bind(Source& s) = 0;

	

	/*std::string& GetSinkName() const;*/
private:
	std::string sinkName;
	std::string sinkTargetName;
	std::string sinkPassName;
};

template <class T>
class DirectBufferSink : public Sink
{
	
public:
	static std::unique_ptr<DirectBufferSink> Make(std::string name, std::shared_ptr<T>& target)
	{
		return std::make_unique<DirectBufferSink>(std::move(name), target);
	}

	DirectBufferSink(std::string name, std::shared_ptr<T>& target) : Sink(std::move(name)),directSink(target)
	{}
	void Bind(Source& source) override
	{
		auto p = std::dynamic_pointer_cast<T>(source.GetSource());

		isLinked = true;
		directSink = std::move(p);
	}
	/*bool IsLinked() const;
	void SetLinked(bool stat);*/
protected:
	bool isLinked = false;
	std::shared_ptr<T>& directSink;

};


template <class T>
class BindableBufferSink : public Sink
{
public:

	static std::unique_ptr<BindableBufferSink> Make(std::string name, std::shared_ptr<T>& target)
	{
		return std::make_unique<BindableBufferSink>(std::move(name), target);
	}

	BindableBufferSink(std::string name, std::shared_ptr<T>& target) : Sink(std::move(name)), bindableSink(target)
	{}
	void Bind(Source& source) override
	{

	};
private:
	std::shared_ptr<T>& bindableSink;
};
