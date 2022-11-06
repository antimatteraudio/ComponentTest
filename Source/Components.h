/*
  ==============================================================================

    Components.h
    Created: 4 Nov 2022 3:00:43pm
    Author:  jeph

  ==============================================================================
*/

#pragma once

//==============================================================================
class SunComponent   : public juce::Component
{
public:
    SunComponent() {}
    
    void paint (juce::Graphics&) override {}
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SunComponent)
};

//==============================================================================
class FloorComponent   : public juce::Component
{
public:
    FloorComponent() {}
    
    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colours::green);
        g.drawLine (0.0f, (float) getHeight() / 2.0f, (float) getWidth(), (float) getHeight() / 2.0f, 5.0f);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FloorComponent)
};

//==============================================================================
class WallComponent   : public juce::Component
{
public:
    WallComponent() {}
    
    void paint (juce::Graphics& g) override
    {
        g.fillCheckerBoard (getLocalBounds().toFloat(), 30, 10,
                            juce::Colours::sandybrown, juce::Colours::saddlebrown);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WallComponent)
};

//==============================================================================
class RoofComponent   : public juce::Component
{
public:
    RoofComponent() {}
    
    void paint (juce::Graphics& g) override
    {
        g.setColour (juce::Colours::red);
        
        juce::Path roof;
        roof.addTriangle (0.0f, (float) getHeight(), (float) getWidth(), (float) getHeight(), (float) getWidth() / 2.0f, 0.0f);
        g.fillPath (roof);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoofComponent)
};

//==============================================================================
class HouseComponent   : public juce::Component
{
public:
    HouseComponent()
    {
        addAndMakeVisible (wall);
        addAndMakeVisible (roof);
    }
    
    void resized() override
    {
        auto separation = juce::jlimit (2, 10, getHeight() / 20);                                                               // [1]
        
        roof.setBounds (0, 0, getWidth(), (int) (getHeight() * 0.2) - separation / 2);                                          // [2]
        wall.setBounds (0, (int) (getHeight() * 0.20) + separation / 2, getWidth(), (int) (getHeight() * 0.80) - separation);   // [3]
    }
    
private:
    WallComponent wall;
    RoofComponent roof;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HouseComponent)
};


//==============================================================================
//This works for framed knobs or sliders
class FilmStripKnob : public juce::Slider
{
public:
    
    FilmStripKnob(juce::Image image, const int numFrames, const bool stripIsHorizontal, int index)
    :   Slider(juce::String(index)),
    filmStrip(image),
    numFrames_(numFrames),
    isHorizontal_(stripIsHorizontal)
    {
        if(filmStrip.isValid())
        {
            setTextBoxStyle(NoTextBox, 0, 0, 0);
            setSliderStyle(RotaryVerticalDrag);
            frameHeight = filmStrip.getHeight() / numFrames_;
            frameWidth = filmStrip.getWidth();
            setRange(0.0f, 1.0f, 0.001f);
        }
    }
    
    void paint(juce::Graphics& g) override
    {
        if(filmStrip.isValid()) {
            int value = (int)((getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (numFrames_ - 1));
            if(isHorizontal_) {
                g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                            value * frameWidth, 0, frameWidth, frameHeight);
            } else {
                g.drawImage(filmStrip, 0, 0, getWidth(), getHeight(),
                            0, value * frameHeight, frameWidth, frameHeight);
            }
        }
    }
    
private:
    juce::Image filmStrip;
    const int numFrames_;
    const bool isHorizontal_;
    int frameWidth, frameHeight;
};



//==============================================================================
class SceneComponent: public juce::Component
{
    static FilmStripKnob myKnob(juce::Image, int, bool, int);
public:

    SceneComponent()
    {
        addAndMakeVisible (floor);
        addAndMakeVisible (house);
        juce::Image knobImage = juce::ImageCache::getFromMemory(BinaryData::knob1_png, BinaryData::knob1_pngSize);
        static FilmStripKnob myKnob(knobImage, knobImage.getHeight()/knobImage.getWidth(), 0, 0);
        addAndMakeVisible(myKnob);
        myKnob.setBounds(171, 70, knobImage.getWidth(), knobImage.getWidth());
       
    }
    
    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::lightblue);
    }
    
    void resized() override
    {
        floor.setBounds (10, 297, 580, 5);
        house.setBounds (300, 70, 200, 220);
    }
    
private:
    FloorComponent floor;
    HouseComponent house;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};


