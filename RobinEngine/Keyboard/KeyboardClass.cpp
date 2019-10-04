#include "KeyboardClass.h"

keyboardClass::keyboardClass()
{
    for (int i = 0; i < 256; i++)
        this->keyStates[i] = false;
}

bool keyboardClass::KeyIsPressed(const unsigned char keycode)
{
    return this->keyStates[keycode];
}

bool keyboardClass::KeyBufferIsEmpty()
{
    return this->keyBuffer.empty();
}

bool keyboardClass::CharBufferIsEmpty()
{
    return this->charBuffer.empty();
}

KeyboardEvent keyboardClass::ReadKey()
{
    if (this->keyBuffer.empty()) 
    {
        return KeyboardEvent(); //return empty keyboard event.
    }
    else 
    {
        KeyboardEvent e = this->keyBuffer.front();
        this->keyBuffer.pop(); // Remove first buffer element
        return e;
    }
}

unsigned char keyboardClass::ReadChar()
{
    if (this->charBuffer.empty()) {
        return 0u; // null char
    }
    else
    {
        unsigned char e = this->charBuffer.front();
        this->charBuffer.pop();
        return e;
    }
}

void keyboardClass::OnKeyPressed(const unsigned char key)
{
    this->keyStates[key] = true;
    this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press,key));
}

void keyboardClass::OnKeyReleased(const unsigned char key)
{
    this->keyStates[key] = false;
    this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}
void keyboardClass::OnChar(const unsigned char key)
{
    this->charBuffer.push(key);
}

void keyboardClass::EnableAutoRepeatKeys()
{
    this->autoRepeatKeys= true;
}

void keyboardClass::DisableAutoRepeatKeys()
{
    this->autoRepeatKeys = false;
}

void keyboardClass::EnableAutoRepeatChars()
{
    this->autoRepeatChars = true;
}

void keyboardClass::DisableAutoRepeatChars()
{
    this->autoRepeatChars = false;
}

bool keyboardClass::IsKeysAutoRepeat()
{
    return this->autoRepeatKeys;
}

bool keyboardClass::IsCharsAutoRepeat()
{
    return this->autoRepeatChars;
}
