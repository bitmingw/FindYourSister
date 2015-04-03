"""
Copyright (c) 2015, Ming Wen

This is a sample file which extends labels in sloth annotation tool.

To enable this configuration, open the sloth with
sloth --config sloth_conf_refuel.py [json_file]
"""

from sloth.conf.default_config import LABELS

REFUEL = (
    {
        'attributes': {
            'class': 'station',
        },
        'inserter': 'sloth.items.RectItemInserter',
        'item': 'sloth.items.RectItem',
        'hotkey': 's',
        'text': 'Gas Station',
    },
    {
        'attributes': {
            'class': 'machine',
        },
        'inserter': 'sloth.items.RectItemInserter',
        'item': 'sloth.items.RectItem',
        'hotkey': 'm',
        'text': 'Gas Machine',
    },
    {
        'attributes': {
            'class': 'gun',
        },
        'inserter': 'sloth.items.RectItemInserter',
        'item': 'sloth.items.RectItem',
        'hotkey': 'g',
        'text': 'Gas Gun',
    },
    {
        'attributes': {
            'class': 'slot',
        },
        'inserter': 'sloth.items.RectItemInserter',
        'item': 'sloth.items.RectItem',
        'hotkey': 's',
        'text': 'Card Slot',
    },
    {
        'attributes': {
            'class': 'keyboard',
        },
        'inserter': 'sloth.items.RectItemInserter',
        'item': 'sloth.items.RectItem',
        'hotkey': 'k',
        'text': 'Keyboard',
    },
)

LABELS += REFUEL

