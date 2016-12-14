/*
  ==============================================================================

    SequenceTimelineHeader.cpp
    Created: 23 Nov 2016 11:32:15pm
    Author:  Ben Kuper

  ==============================================================================
*/

#include "SequenceTimelineHeader.h"
#include "Style.h"

SequenceTimelineHeader::SequenceTimelineHeader(Sequence * _sequence) :
	sequence(_sequence)
{
	sequence->addAsyncContainerListener(this);
	addAndMakeVisible(needle);

	setSize(6, 20);
}

SequenceTimelineHeader::~SequenceTimelineHeader()
{
	sequence->removeAsyncContainerListener(this);
}

void SequenceTimelineHeader::paint(Graphics & g)
{
	g.setColour(BG_COLOR.darker(.1f));
	g.fillRoundedRectangle(getLocalBounds().toFloat(), 2);

	g.setColour(BG_COLOR.brighter(.1f));
	g.fillRoundedRectangle(getLocalBounds().removeFromTop(12).toFloat(), 2);

	//Draw ticks
	float start = floorf(sequence->viewStartTime->floatValue());
	float end = floorf(sequence->viewEndTime->floatValue());


	int numDivisions = 1;


	g.setFont(10);
	
	for (float i = start; i <= end; i+= 1.f/numDivisions)
	{
		int tx = getXForTime(i);

		if ((int)i == i) //is a tick on a second
		{
			
			if (fmodf(i, 60) == 0)
			{
				g.setColour(BG_COLOR.brighter(.6f));
				//g.drawLine(tx, 0, tx, getHeight(), 1);
				g.drawVerticalLine(tx, 0, (float)getHeight());
				g.setColour(BG_COLOR.darker(.6f));
				g.drawRoundedRectangle(getLocalBounds().toFloat(), 2, 2);

				g.setColour(BG_COLOR.brighter(.7f));
				g.fillRoundedRectangle(tx-10,0, 20, 12, 2);
				g.setColour(BG_COLOR.darker());
				g.drawText(String(floor<int>(i / 60)) + "'", tx-10, 2, 20, 10, Justification::centred);
			}
			else
			{
				g.setColour(BG_COLOR.brighter(.1f));
				//g.drawLine(tx, 0, tx, getHeight(), 1);
				g.drawVerticalLine(tx, 0, (float)getHeight());
				g.setColour(BG_COLOR.darker(.3f));
				g.drawText(String(fmodf(i, 60)), tx - 10, 2, 20, 10, Justification::centred);
			}
		} else
		{
			g.setColour(BG_COLOR);
			g.drawVerticalLine(tx, 0, (float)getHeight());
		}		
	}

	
	g.setColour(BG_COLOR.brighter(.7f));
	g.fillRoundedRectangle(0, 0, 20, 12, 2);
	g.setColour(BG_COLOR.darker());
	g.drawText(String(floor<int>(start / 60)) + "'", 2, 2, 18, 10, Justification::centred);

	g.setColour(BG_COLOR.darker(.6f));
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 2, 2);

}

void SequenceTimelineHeader::resized()
{
	Rectangle<int> r = getLocalBounds();
	Rectangle<int> nr = r.withSize(7, getHeight());
	nr.setPosition(getXForTime(sequence->currentTime->floatValue())-needle.getWidth()/2, 0);
	needle.setBounds(nr);
}

void SequenceTimelineHeader::mouseDown(const MouseEvent & e)
{
	if (e.mods.isLeftButtonDown())
	{
		sequence->currentTime->setValue(getTimeForX(e.getPosition().x));
	}
}

void SequenceTimelineHeader::mouseDrag(const MouseEvent & e)
{
	if(e.mods.isLeftButtonDown())
	{
		sequence->currentTime->setValue(getTimeForX(e.getPosition().x));
	}
}

int SequenceTimelineHeader::getXForTime(float time)
{
	float viewStart = sequence->viewStartTime->floatValue();
	float viewEnd = sequence->viewEndTime->floatValue();
	if (viewStart == viewEnd) return 0;
	return (int)jmap<float>(time, viewStart, viewEnd, 0, (float)getWidth());
}

float SequenceTimelineHeader::getTimeForX(int tx)
{
	float viewStart = sequence->viewStartTime->floatValue();
	float viewEnd = sequence->viewEndTime->floatValue();
	return jmap<float>((float)tx, 0, (float)getWidth(), viewStart, viewEnd);
}

void SequenceTimelineHeader::newMessage(const ContainerAsyncEvent & e)
{
	switch (e.type)
	{
	case ContainerAsyncEvent::ControllableFeedbackUpdate:

		if (e.targetControllable == sequence->viewStartTime || e.targetControllable == sequence->viewEndTime)
		{
			repaint();
			resized();
		} else if (e.targetControllable == sequence->currentTime)
		{
			resized();
		} else if (e.targetControllable == sequence->totalTime)
		{
			resized();
		}
		break;
		
	default:
	//other events not handled 
	break;
	}
}

void TimeNeedleUI::paint(Graphics & g)
{
	g.setColour(HIGHLIGHT_COLOR);
	Path p;
	p.addTriangle(0, 0, getWidth(), 0, getWidth()/2.f, 4);
	p.addTriangle(0, getHeight(), getWidth() / 2, getHeight() - 4, getWidth(), getHeight());
	g.fillPath(p);
	g.drawVerticalLine(getWidth() / 2, 0, getHeight());
}