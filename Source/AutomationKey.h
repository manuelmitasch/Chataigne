/*
  ==============================================================================

    AutomationKey.h
    Created: 11 Dec 2016 1:22:20pm
    Author:  Ben

  ==============================================================================
*/

#ifndef AUTOMATIONKEY_H_INCLUDED
#define AUTOMATIONKEY_H_INCLUDED

#include "BaseItem.h"
#include "Easing.h"

class AutomationKey :
	public BaseItem
{
public:
	AutomationKey();
	virtual ~AutomationKey();

	FloatParameter * position; //depends on parent automation
	FloatParameter * value; //0-1

	ScopedPointer<Easing> easing;


	float getValue(AutomationKey * nextKey, const float &position);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutomationKey)
};



#endif  // AUTOMATIONKEY_H_INCLUDED
