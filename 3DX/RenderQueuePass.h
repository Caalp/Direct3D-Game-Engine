//#pragma once
//#include "BindingPass.h"
//#include "Job.h"
//
//class RenderQueuePass : public BindingPass
//{
//public:
//	// with RenderQueuePass we can call BindingPass constructor
//	using BindingPass::BindingPass;
//	void Accept(Job job);
//	void Execute(Graphics& gfx);
//	void Reset() override;
//
//
//
//private:
//	std::vector<Job> jobs;	
//};