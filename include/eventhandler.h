#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include <unordered_map>
#include <vector>
// Subscriber Interface
class Listener {
public:
  virtual void handleEvent(int key) = 0;
  virtual void handleEvent(int key, float *val) = 0;
};

class EventHandler {
private:
  // Key - KEY; Value - List<Listener>
  std::unordered_map<int, std::vector<Listener*>> listeners;
public:
  EventHandler();
  ~EventHandler();
  void subscribe(int key, Listener *listener);
  void unsubscribe(int key, Listener *listener);
  void notify(int key);

  template <class T>
  void notify(int key, T *val);
};

template <class T>
void EventHandler::notify(int key, T *val) {
  if (listeners.find(key) == listeners.end()) {
    return;
  }
  for (auto listener : listeners[key]) {
    listener->handleEvent(key, val);
  }
}

#endif /* __EVENTHANDLER_H__ */
