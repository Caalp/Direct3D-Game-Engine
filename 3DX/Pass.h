#pragma once
#include <vector>
#include <memory>
#include "Sink.h"
#include "Source.h"

class Graphics;

class Pass
{
public:
	Pass() = default;
	Pass(const std::string passName);
	virtual void Execute(Graphics& gfx) = 0;
	void RegisterSink(std::unique_ptr<Sink> sinkingObject);
	void RegisterSource(std::unique_ptr<Source> sourceObject);
	void SetSinkLinkage(std::string registeredSinkName, std::string targetName);
	Source& GetSource(std::string name);

	// Check also with const Sink&
	const Sink& GetSinkByName(std::string sinkName);
	//const std::unique_ptr<Sink>& GetSink() const;

	// Try with out const 
	const std::vector<std::unique_ptr<Sink>>& GetSinks();
	//const std::vector<std::unique_ptr<Sink>>& GetSources();
	const std::string GetPassName() const;
	virtual void Reset() = 0;
protected:
	bool isLinked = false;
	const std::string passName;
	std::vector<std::unique_ptr<Sink>> sinks;
	std::vector<std::unique_ptr<Source>> sources;
};