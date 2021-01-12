#pragma once
#include <memory>
#include <functional>
#include <list>
#include <map>
#include <vector>
#include "Keyboard.h"
class IEventData
{
public:
	typedef size_t id_t;
	virtual id_t GetID() = 0;
};

typedef std::shared_ptr<IEventData> IEventDataPtr;
typedef std::function<void(IEventDataPtr&)> EventDelegate;

class IEventManager
{
public:
	virtual bool AddListener(IEventData::id_t id, EventDelegate proc) = 0;
	virtual bool RemoveListener(IEventData::id_t id, EventDelegate proc) = 0;
	virtual void QueueEvent(IEventDataPtr ev) = 0;
	virtual void ProcessEvents() = 0;

};

#define DECLARE_EVENT(type) \
	static IEventData::id_t ID() { return reinterpret_cast<IEventData::id_t>(&ID);}\
	IEventData::id_t GetID() override {return ID();}


class EventManager : public IEventManager
{
public:
	typedef std::list<EventDelegate> EventDelegateList;
	~EventManager() {}
	virtual bool AddListener(IEventData::id_t id, EventDelegate proc) override;
	virtual bool RemoveListener(IEventData::id_t id, EventDelegate proc) override;
	virtual void QueueEvent(IEventDataPtr ev) override;
	virtual void ProcessEvents() override;

private:

	std::list<std::shared_ptr<IEventData>> mEventQueue;
	std::map<IEventData::id_t, EventDelegateList> mEventListeners;
};

class EventListener
{
public:
	template<class T>
	bool OnEvent(std::function<void(std::shared_ptr<T>)> proc)
	{
		return OnEvent(T::ID(), [&, proc](IEventDataPtr data)
		{
			auto ev = std::dynamic_pointer_cast<T>(data);
			if (ev) { proc(ev); }
		}
		);
	}

	typedef std::pair<IEventData::id_t, EventDelegate> _EvPair;
	EventListener(std::weak_ptr<IEventManager> mgr) : _els_mEventManager(mgr) {}

	virtual ~EventListener()
	{
		if (_els_mEventManager.expired()) return;
		auto em = _els_mEventManager.lock();
		for (auto i : _els_mLocalEvents)
		{
			em->RemoveListener(i.first, i.second);
		}
	}
protected:
	bool OnEvent(IEventData::id_t id, EventDelegate proc)
	{
		if (_els_mEventManager.expired()) return false;
		auto em = _els_mEventManager.lock();
		if (em->AddListener(id, proc))
		{
			_els_mLocalEvents.push_back(_EvPair(id, proc));
		}
	}
private:
	std::weak_ptr<IEventManager> _els_mEventManager;
	std::vector<_EvPair>        _els_mLocalEvents;

};

class KeyboardEvent : public IEventData
{

public:
	DECLARE_EVENT(KeyboardEvent);
	KeyboardEvent(unsigned char keyEvent) :mEvent(keyEvent) {}
	const unsigned char& GetEvent() const;
private:
	unsigned char mEvent;

};

class ImGuiEvent : public IEventData
{
public:
	DECLARE_EVENT(ImGuiEvent);
	ImGuiEvent() {/** OutputDebugStringA("ImGui Event...");*/ }

};
