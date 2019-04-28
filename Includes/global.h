// All includes in the entire project

#include <Windows.h>
#include <vector>
#include <unordered_set>
#include <map>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <random>

#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

// vk to string
std::string GetKeyString(int Input);

// random
int random(int min, int max);

// clicker
extern int minCps;
extern int maxCps;
extern bool toggled;

// mouse
extern int mousedown;
int initHook();

// keyboard
extern unsigned int currentkey;

#endif