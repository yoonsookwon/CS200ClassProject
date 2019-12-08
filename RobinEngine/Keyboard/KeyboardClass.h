/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#pragma once
#include "KeyboardEvent.h"
#include <queue>

class keyboardClass {

public:
    keyboardClass();
    bool KeyIsPressed(const unsigned char keycode);
    bool KeyBufferIsEmpty();
    bool CharBufferIsEmpty();
    KeyboardEvent ReadKey();
    unsigned char ReadChar();
    void OnKeyPressed(const unsigned char key);
    void OnKeyReleased(const unsigned char key);
    void OnChar(const unsigned char key);
    void EnableAutoRepeatKeys(); 
    void DisableAutoRepeatKeys();
    void EnableAutoRepeatChars();
    void DisableAutoRepeatChars();
    bool IsKeysAutoRepeat();
    bool IsCharsAutoRepeat();
private:
    bool autoRepeatKeys = false;
    bool autoRepeatChars = false;
    bool keyStates[256] = {false};
    std::queue<KeyboardEvent> keyBuffer;
    std::queue<unsigned char> charBuffer;
};