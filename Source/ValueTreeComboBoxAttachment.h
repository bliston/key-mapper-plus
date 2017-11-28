/*
 ==============================================================================

 Copyright (c) 2016, Daniel Walz
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 3. Neither the name of the copyright holder nor the names of its contributors
 may be used to endorse or promote products derived from this software without
 specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 OF THE POSSIBILITY OF SUCH DAMAGE.

 ==============================================================================
 */


/*
  ==============================================================================

    ValueTreeComboBoxAttachment.h
    Created: 4 Jun 2016 11:17:03am
    Author:  Daniel Walz

  ==============================================================================
*/

#ifndef VALUETREECOMBOBOXATTACHMENT_H_INCLUDED
#define VALUETREECOMBOBOXATTACHMENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 This attachment connects a node in a ValueTree with a combobox.
 It supports two modes:
 selectSubNodes == true: The Combobox is filled with the sub nodes. As combobox items the
 property is used.

 selectSubNodes == false: The combobox has already it's items and the selected index 
 is stored in the property.
 */
class ValueTreeComboBoxAttachment : public juce::ComboBox::Listener,
	public juce::ValueTree::Listener
{
public:
	ValueTreeComboBoxAttachment(juce::ValueTree& _tree,
		juce::ComboBox* _comboBox,
		juce::Identifier _property,
		juce::UndoManager* _undoMgr = nullptr)
		: tree(_tree),
		property(_property),
		undoMgr(_undoMgr),
		updating(false)
	{
		// Don't attach an invalid valuetree!
		jassert(tree.isValid());
		comboBox = _comboBox;
		if (tree.hasProperty(property)) {
			setSelection();
		}
		tree.addListener(this);
		comboBox->addListener(this);
	}

	~ValueTreeComboBoxAttachment()
	{
		tree.removeListener(this);
		if (comboBox) {
			comboBox->removeListener(this);
		}
	}

	void comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) override
	{
		if (!updating) {
			updating = true;
			if (comboBox == comboBoxThatHasChanged) {
				setProperty();
			}
			updating = false;
		}
	}

	void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &_property) override
	{
		if (!updating) {
			updating = true;
				if (treeWhosePropertyHasChanged == tree && _property == property && comboBox) {
					if (tree.hasProperty(property)) {
						setSelection();
					}
				}
			}
			updating = false;
	}
	void valueTreeChildAdded(juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenAdded) override {}
    void valueTreeChildRemoved (juce::ValueTree &parentTree, juce::ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override {}
    void valueTreeChildOrderChanged (juce::ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override {}
    void valueTreeParentChanged (juce::ValueTree &treeWhoseParentHasChanged) override {}
    void valueTreeRedirected (juce::ValueTree &treeWhichHasBeenChanged) override {}


private:

	void setProperty()
	{
		tree.setProperty(property, comboBox->getItemText(comboBox->getSelectedItemIndex()), undoMgr);
	}

	void setSelection()
	{
		for (int i = 0; i < comboBox->getNumItems(); ++i) {
			if (tree.getProperty(property).equals(comboBox->getItemText(i)))
			{
				comboBox->setSelectedItemIndex(i);
			}
		}
	}

    juce::ValueTree                                 tree;
    juce::Component::SafePointer<juce::ComboBox>    comboBox;
    juce::Identifier                                property;
    juce::UndoManager*                              undoMgr;
    bool                                            updating;
};


#endif  // VALUETREECOMBOBOXATTACHMENT_H_INCLUDED
