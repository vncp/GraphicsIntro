#include "eventhandler.h"
#include <iostream>

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{}

void EventHandler::subscribe(int key, Listener *listener)
{
  if (listeners.find(key) == listeners.end()) {
    listeners.emplace(key, std::vector<Listener*>());
  }
  listeners.at(key).emplace_back(listener);
}

void EventHandler::unsubscribe(int key, Listener *toRemove)
{
  for (std::vector<Listener*>::iterator l = listeners[key].begin(); l != listeners[key].end(); l++) {
    if ((*l) == toRemove) {
      listeners[key].erase(l);
    }
  }
}

void EventHandler::notify(int key) {
  if (listeners.find(key) == listeners.end()) {
    return;
  }
  for (auto listener : listeners[key]) {
    listener->handleEvent(key);
  }
}
