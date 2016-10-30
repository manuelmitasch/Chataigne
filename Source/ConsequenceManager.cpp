/*
  ==============================================================================

    ConsequenceManager.cpp
    Created: 28 Oct 2016 8:07:30pm
    Author:  bkupe

  ==============================================================================
*/

#include "ConsequenceManager.h"


juce_ImplementSingleton(ConsequenceManager)

ConsequenceManager::ConsequenceManager() :
	BaseManager<Consequence>("Consequences")
{
	selectItemWhenCreated = false;
}

ConsequenceManager::~ConsequenceManager()
{
}
