/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyFirstProjectAudioProcessorEditor::MyFirstProjectAudioProcessorEditor (MyFirstProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 480);

    // Dials

    addAndMakeVisible(ampDial);
    addAndMakeVisible(attackDial);
    addAndMakeVisible(decayDial);
    addAndMakeVisible(sustainDial);
    addAndMakeVisible(releaseDial);
    addAndMakeVisible(numEvenPartialsDial);
    addAndMakeVisible(evenPartialsAmpDial);
    addAndMakeVisible(numOddPartialsDial);
    addAndMakeVisible(oddPartialsAmpDial);
    addAndMakeVisible(numCluster1PartialsDial);
    addAndMakeVisible(cluster1PartialsAmpDial);
    addAndMakeVisible(cluster1FreqRatioDial);
    addAndMakeVisible(cluster1HarmRatioDial);
    addAndMakeVisible(numCluster2PartialsDial);
    addAndMakeVisible(cluster2PartialsAmpDial);
    addAndMakeVisible(cluster2FreqRatioDial);
    addAndMakeVisible(cluster2HarmRatioDial);
    addAndMakeVisible(numCluster3PartialsDial);
    addAndMakeVisible(cluster3PartialsAmpDial);
    addAndMakeVisible(cluster3FreqRatioDial);
    addAndMakeVisible(cluster3HarmRatioDial);

    // Labels

    addAndMakeVisible(ampLabel);
    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(releaseLabel);
    addAndMakeVisible(numEvenPartialsLabel);
    addAndMakeVisible(evenPartialsAmpLabel);
    addAndMakeVisible(numOddPartialsLabel);
    addAndMakeVisible(oddPartialsAmpLabel);
    addAndMakeVisible(numCluster1PartialsLabel);
    addAndMakeVisible(cluster1PartialsAmpLabel);
    addAndMakeVisible(cluster1FreqRatioLabel);
    addAndMakeVisible(cluster1HarmRatioLabel);
    addAndMakeVisible(numCluster2PartialsLabel);
    addAndMakeVisible(cluster2PartialsAmpLabel);
    addAndMakeVisible(cluster2FreqRatioLabel);
    addAndMakeVisible(cluster2HarmRatioLabel);
    addAndMakeVisible(numCluster3PartialsLabel);
    addAndMakeVisible(cluster3PartialsAmpLabel);
    addAndMakeVisible(cluster3FreqRatioLabel);
    addAndMakeVisible(cluster3HarmRatioLabel);

    // Label settings

    ampLabel.setText("Gain", juce::dontSendNotification);
    attackLabel.setText("Attack", juce::dontSendNotification);
    decayLabel.setText("Decay", juce::dontSendNotification);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    releaseLabel.setText("Release", juce::dontSendNotification);
    numEvenPartialsLabel.setText("nr. even partials", juce::dontSendNotification);
    evenPartialsAmpLabel.setText("even partial gain", juce::dontSendNotification);
    numOddPartialsLabel.setText("nr. odd partials", juce::dontSendNotification);
    oddPartialsAmpLabel.setText("odd partial gain", juce::dontSendNotification);
    numCluster1PartialsLabel.setText("nr. cluster 1 partials", juce::dontSendNotification);
    cluster1PartialsAmpLabel.setText("cluster 1 partial gain", juce::dontSendNotification);
    cluster1FreqRatioLabel.setText("cluster 1 freq offset", juce::dontSendNotification);
    cluster1HarmRatioLabel.setText("cluster 1 harm ratio", juce::dontSendNotification);
    numCluster2PartialsLabel.setText("nr. cluster 2 partials", juce::dontSendNotification);
    cluster2PartialsAmpLabel.setText("cluster 2 partial gain", juce::dontSendNotification);
    cluster2FreqRatioLabel.setText("cluster 2 freq offset", juce::dontSendNotification);
    cluster2HarmRatioLabel.setText("cluster 2 harm ratio", juce::dontSendNotification);
    numCluster3PartialsLabel.setText("nr. cluster 3 partials", juce::dontSendNotification);
    cluster3PartialsAmpLabel.setText("cluster 3 partial gain", juce::dontSendNotification);
    cluster3FreqRatioLabel.setText("cluster 3 freq offset", juce::dontSendNotification);
    cluster3HarmRatioLabel.setText("cluster 3 harm ratio", juce::dontSendNotification);

    // Attaching labels to dials

    ampLabel.attachToComponent(&ampDial, false);
    attackLabel.attachToComponent(&attackDial, false);
    decayLabel.attachToComponent(&decayDial, false);
    sustainLabel.attachToComponent(&sustainDial, false);
    releaseLabel.attachToComponent(&releaseDial, false);
    numEvenPartialsLabel.attachToComponent(&numEvenPartialsDial, false);
    evenPartialsAmpLabel.attachToComponent(&evenPartialsAmpDial, false);
    numOddPartialsLabel.attachToComponent(&numOddPartialsDial, false);
    oddPartialsAmpLabel.attachToComponent(&oddPartialsAmpDial, false);
    numCluster1PartialsLabel.attachToComponent(&numCluster1PartialsDial, false);
    cluster1PartialsAmpLabel.attachToComponent(&cluster1PartialsAmpDial, false);
    cluster1FreqRatioLabel.attachToComponent(&cluster1FreqRatioDial, false);
    cluster1HarmRatioLabel.attachToComponent(&cluster1HarmRatioDial, false);
    numCluster2PartialsLabel.attachToComponent(&numCluster2PartialsDial, false);
    cluster2PartialsAmpLabel.attachToComponent(&cluster2PartialsAmpDial, false);
    cluster2FreqRatioLabel.attachToComponent(&cluster2FreqRatioDial, false);
    cluster2HarmRatioLabel.attachToComponent(&cluster2HarmRatioDial, false);
    numCluster3PartialsLabel.attachToComponent(&numCluster3PartialsDial, false);
    cluster3PartialsAmpLabel.attachToComponent(&cluster3PartialsAmpDial, false);
    cluster3FreqRatioLabel.attachToComponent(&cluster3FreqRatioDial, false);
    cluster3HarmRatioLabel.attachToComponent(&cluster3HarmRatioDial, false);

    // Label justification

    ampLabel.setJustificationType(juce::Justification::centred);
    attackLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setJustificationType(juce::Justification::centred);
    numEvenPartialsLabel.setJustificationType(juce::Justification::centred);
    evenPartialsAmpLabel.setJustificationType(juce::Justification::centred);
    numOddPartialsLabel.setJustificationType(juce::Justification::centred);
    oddPartialsAmpLabel.setJustificationType(juce::Justification::centred);
    numCluster1PartialsLabel.setJustificationType(juce::Justification::centred);
    cluster1PartialsAmpLabel.setJustificationType(juce::Justification::centred);
    cluster1FreqRatioLabel.setJustificationType(juce::Justification::centred);
    cluster1HarmRatioLabel.setJustificationType(juce::Justification::centred);
    numCluster2PartialsLabel.setJustificationType(juce::Justification::centred);
    cluster2PartialsAmpLabel.setJustificationType(juce::Justification::centred);
    cluster2FreqRatioLabel.setJustificationType(juce::Justification::centred);
    cluster2HarmRatioLabel.setJustificationType(juce::Justification::centred);
    numCluster3PartialsLabel.setJustificationType(juce::Justification::centred);
    cluster3PartialsAmpLabel.setJustificationType(juce::Justification::centred);
    cluster3FreqRatioLabel.setJustificationType(juce::Justification::centred);
    cluster3HarmRatioLabel.setJustificationType(juce::Justification::centred);

    // Dial style settings

    ampDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    attackDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    decayDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    sustainDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    releaseDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    numEvenPartialsDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    evenPartialsAmpDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    numOddPartialsDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    oddPartialsAmpDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    numCluster1PartialsDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster1PartialsAmpDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster1FreqRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster1HarmRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    numCluster2PartialsDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster2PartialsAmpDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster2FreqRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster2HarmRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    numCluster3PartialsDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster3PartialsAmpDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster3FreqRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cluster3HarmRatioDial.setSliderStyle(juce::Slider::SliderStyle::Rotary);

    // Dial textboxes

    ampDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    attackDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    decayDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    sustainDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    releaseDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    numEvenPartialsDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    evenPartialsAmpDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    numOddPartialsDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    oddPartialsAmpDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    numCluster1PartialsDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster1PartialsAmpDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster1FreqRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster1HarmRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    numCluster2PartialsDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster2PartialsAmpDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster2FreqRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster2HarmRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    numCluster3PartialsDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster3PartialsAmpDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster3FreqRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);
    cluster3HarmRatioDial.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 15);

    // Dial ranges

    ampDial.setRange(0.0, 1.0, 0.001);
    attackDial.setRange(0.01, 10.0, 0.01);
    decayDial.setRange(0.01, 10.0, 0.01);
    sustainDial.setRange(0.0, 1.0, 0.01);
    releaseDial.setRange(0.01, 10.0, 0.01);
    numEvenPartialsDial.setRange(0, 20, 1);
    evenPartialsAmpDial.setRange(0.0, 1.0, 0.001);
    numOddPartialsDial.setRange(0, 20, 1);
    oddPartialsAmpDial.setRange(0.0, 1.0, 0.001);
    numCluster1PartialsDial.setRange(0, 10, 1);
    cluster1PartialsAmpDial.setRange(0.0, 1.0, 0.001);
    cluster1FreqRatioDial.setRange(0.1, 20.0, 0.001);
    cluster1HarmRatioDial.setRange(0.1, 3.0, 0.001);
    numCluster2PartialsDial.setRange(0, 10, 1);
    cluster2PartialsAmpDial.setRange(0.0, 1.0, 0.001);
    cluster2FreqRatioDial.setRange(0.1, 20.0, 0.001);
    cluster2HarmRatioDial.setRange(0.1, 3.0, 0.001);
    numCluster3PartialsDial.setRange(0, 10, 1);
    cluster3PartialsAmpDial.setRange(0.0, 1.0, 0.001);
    cluster3FreqRatioDial.setRange(0.1, 20.0, 0.001);
    cluster3HarmRatioDial.setRange(0.1, 3.0, 0.001);

    // Default values

    ampDial.setValue(1.0);
    attackDial.setValue(0.01);
    decayDial.setValue(0.01);
    sustainDial.setValue(1.0);
    releaseDial.setValue(0.01);
    numEvenPartialsDial.setValue(20);
    evenPartialsAmpDial.setValue(1.0);
    numOddPartialsDial.setValue(20);
    oddPartialsAmpDial.setValue(1.0);
    numCluster1PartialsDial.setValue(0);
    cluster1PartialsAmpDial.setValue(0.0);
    cluster1FreqRatioDial.setValue(1.0);
    cluster1HarmRatioDial.setValue(1.0);
    numCluster2PartialsDial.setValue(0);
    cluster2PartialsAmpDial.setValue(0.0);
    cluster2FreqRatioDial.setValue(1.0);
    cluster2HarmRatioDial.setValue(1.0);
    numCluster3PartialsDial.setValue(0);
    cluster3PartialsAmpDial.setValue(0.0);
    cluster3FreqRatioDial.setValue(1.0);
    cluster3HarmRatioDial.setValue(1.0);

    // Dial skews

    attackDial.setSkewFactorFromMidPoint(1.0);
    decayDial.setSkewFactorFromMidPoint(1.0);
    releaseDial.setSkewFactorFromMidPoint(1.0);
    cluster1FreqRatioDial.setSkewFactorFromMidPoint(1.0);
    cluster1HarmRatioDial.setSkewFactorFromMidPoint(1.0);
    cluster2FreqRatioDial.setSkewFactorFromMidPoint(1.0);
    cluster2HarmRatioDial.setSkewFactorFromMidPoint(1.0);
    cluster3FreqRatioDial.setSkewFactorFromMidPoint(1.0);
    cluster3HarmRatioDial.setSkewFactorFromMidPoint(1.0);

    // Connecting listeners

    ampDial.addListener(this);
    attackDial.addListener(this);
    decayDial.addListener(this);
    sustainDial.addListener(this);
    releaseDial.addListener(this);
    numEvenPartialsDial.addListener(this);
    evenPartialsAmpDial.addListener(this);
    numOddPartialsDial.addListener(this);
    oddPartialsAmpDial.addListener(this);
    numCluster1PartialsDial.addListener(this);
    cluster1PartialsAmpDial.addListener(this);
    cluster1FreqRatioDial.addListener(this);
    cluster1HarmRatioDial.addListener(this);
    numCluster2PartialsDial.addListener(this);
    cluster2PartialsAmpDial.addListener(this);
    cluster2FreqRatioDial.addListener(this);
    cluster2HarmRatioDial.addListener(this);
    numCluster3PartialsDial.addListener(this);
    cluster3PartialsAmpDial.addListener(this);
    cluster3FreqRatioDial.addListener(this);
    cluster3HarmRatioDial.addListener(this);
}

MyFirstProjectAudioProcessorEditor::~MyFirstProjectAudioProcessorEditor()
{
    ampDial.removeListener(this);
    attackDial.removeListener(this);
    decayDial.removeListener(this);
    sustainDial.removeListener(this);
    releaseDial.removeListener(this);
    numEvenPartialsDial.removeListener(this);
    evenPartialsAmpDial.removeListener(this);
    numOddPartialsDial.removeListener(this);
    oddPartialsAmpDial.removeListener(this);
    numCluster1PartialsDial.removeListener(this);
    cluster1PartialsAmpDial.removeListener(this);
    cluster1FreqRatioDial.removeListener(this);
    cluster1HarmRatioDial.removeListener(this);
    numCluster2PartialsDial.removeListener(this);
    cluster2PartialsAmpDial.removeListener(this);
    cluster2FreqRatioDial.removeListener(this);
    cluster2HarmRatioDial.removeListener(this);
    numCluster3PartialsDial.removeListener(this);
    cluster3PartialsAmpDial.removeListener(this);
    cluster3FreqRatioDial.removeListener(this);
    cluster3HarmRatioDial.removeListener(this);
}

//==============================================================================
void MyFirstProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void MyFirstProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto area = getLocalBounds();
    area.reduce(20, 20);
    int dialRadius = 100;
    int width = area.getWidth();
    int height = area.getHeight();
    int reducedHeight = height / 3;
    int reducedWidth = width / 8;
    int xOffset = 10;
    int yOffset = 40;

    ampDial.setBounds(xOffset, yOffset, dialRadius, dialRadius);

    attackDial.setBounds(xOffset, reducedHeight + yOffset, dialRadius, dialRadius);
    decayDial.setBounds(reducedWidth + xOffset, reducedHeight + yOffset, dialRadius, dialRadius);
    sustainDial.setBounds(reducedWidth * 2 + xOffset, reducedHeight + yOffset, dialRadius, dialRadius);
    releaseDial.setBounds(reducedWidth * 3 + xOffset, reducedHeight + yOffset, dialRadius, dialRadius);

    numEvenPartialsDial.setBounds(xOffset,                   reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    evenPartialsAmpDial.setBounds(reducedWidth + xOffset,    reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    numOddPartialsDial.setBounds(reducedWidth * 2 + xOffset, reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    oddPartialsAmpDial.setBounds(reducedWidth * 3 + xOffset, reducedHeight * 2 + yOffset, dialRadius, dialRadius);

    numCluster1PartialsDial.setBounds(reducedWidth * 4 + xOffset, yOffset, dialRadius, dialRadius);
    cluster1PartialsAmpDial.setBounds(reducedWidth * 5 + xOffset, yOffset, dialRadius, dialRadius);
    cluster1FreqRatioDial.setBounds(reducedWidth * 6 + xOffset,   yOffset, dialRadius, dialRadius);
    cluster1HarmRatioDial.setBounds(reducedWidth * 7 + xOffset,   yOffset, dialRadius, dialRadius);

    numCluster2PartialsDial.setBounds(reducedWidth * 4 + xOffset, reducedHeight + yOffset, dialRadius, dialRadius);
    cluster2PartialsAmpDial.setBounds(reducedWidth * 5 + xOffset, reducedHeight + yOffset, dialRadius, dialRadius);
    cluster2FreqRatioDial.setBounds(reducedWidth * 6 + xOffset,   reducedHeight + yOffset, dialRadius, dialRadius);
    cluster2HarmRatioDial.setBounds(reducedWidth * 7 + xOffset,   reducedHeight + yOffset, dialRadius, dialRadius);

    numCluster3PartialsDial.setBounds(reducedWidth * 4 + xOffset, reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    cluster3PartialsAmpDial.setBounds(reducedWidth * 5 + xOffset, reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    cluster3FreqRatioDial.setBounds(reducedWidth * 6 + xOffset,   reducedHeight * 2 + yOffset, dialRadius, dialRadius);
    cluster3HarmRatioDial.setBounds(reducedWidth * 7 + xOffset,   reducedHeight * 2 + yOffset, dialRadius, dialRadius);

}

void MyFirstProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &ampDial)
    {
        double ampVal = ampDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setAmp( ampVal );
    }

    else if (slider == &attackDial)
    {
        audioProcessor.setAttack(attackDial.getValue());
    }
    else if (slider == &decayDial)
    {
        audioProcessor.setDecay(decayDial.getValue());
    }
    else if (slider == &sustainDial)
    {
        audioProcessor.setSustain(sustainDial.getValue());
    }
    else if (slider == &releaseDial)
    {
        audioProcessor.setRelease(releaseDial.getValue());
    }

    else if (slider == &numEvenPartialsDial)
    {
        audioProcessor.setEvenPartials(numEvenPartialsDial.getValue());
    }
    else if (slider == &evenPartialsAmpDial)
    {
        double ampVal = evenPartialsAmpDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setEvenAmp(ampVal);
    }
    else if (slider == &numOddPartialsDial)
    {
        audioProcessor.setOddPartials(numOddPartialsDial.getValue());
    }
    else if (slider == &oddPartialsAmpDial)
    {
        double ampVal = oddPartialsAmpDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setOddAmp(ampVal);
    }

    else if (slider == &numCluster1PartialsDial)
    {
        audioProcessor.setCluster1Partials(numCluster1PartialsDial.getValue());
    }
    else if (slider == &cluster1PartialsAmpDial)
    {
        double ampVal = cluster1PartialsAmpDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setCluster1Amp(ampVal);
    }
    else if (slider == &cluster1FreqRatioDial)
    {
        audioProcessor.setCluster1Ratio(cluster1FreqRatioDial.getValue());
    }
    else if (slider == &cluster1HarmRatioDial)
    {
        audioProcessor.setCluster1FreqMult(cluster1HarmRatioDial.getValue());
    }

    else if (slider == &numCluster2PartialsDial)
    {
        audioProcessor.setCluster2Partials(numCluster2PartialsDial.getValue());
    }
    else if (slider == &cluster2PartialsAmpDial)
    {
        double ampVal = cluster2PartialsAmpDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setCluster1Amp(ampVal);
    }
    else if (slider == &cluster2FreqRatioDial)
    {
        audioProcessor.setCluster2Ratio(cluster2FreqRatioDial.getValue());
    }
    else if (slider == &cluster2HarmRatioDial)
    {
        audioProcessor.setCluster2FreqMult(cluster2HarmRatioDial.getValue());
    }

    else if (slider == &numCluster3PartialsDial)
    {
        audioProcessor.setCluster3Partials(numCluster3PartialsDial.getValue());
    }
    else if (slider == &cluster3PartialsAmpDial)
    {
        double ampVal = cluster3PartialsAmpDial.getValue();
        ampVal = 70.0 * (ampVal - 1.0);
        ampVal = juce::Decibels::decibelsToGain(ampVal);
        audioProcessor.setCluster1Amp(ampVal);
    }
    else if (slider == &cluster3FreqRatioDial)
    {
        audioProcessor.setCluster3Ratio(cluster3FreqRatioDial.getValue());
    }
    else if (slider == &cluster3HarmRatioDial)
    {
        audioProcessor.setCluster3FreqMult(cluster3HarmRatioDial.getValue());
    }
}