Quick Start
===========

Generate Labels
-----------------

This program includes a simple tool for image annotation based on sloth.
You can find the detailed documentation under ``sloth/doc`` folder.

After labeling images and saving the results in a json file,
it needs to be modified before used in our program.
The modification takes two steps.

First, we need to load miscellaneous info about images.
``tools/gen_misc.py`` is developed for this purpose.
For example, if reference images are saved at ``sample/train``
and test images are saved at ``sample/test``.
The following commands will generate proper info.

.. code-block:: sh

   cd tools
   python gen_misc.py ../sample/train train trainInfo.json
   python gen_misc.py ../sample/test test testInfo.json

Second, let's combine the miscellaneous info with sloth annotations.
This is complete with the help of ``gen_labels.py`` and
``gen_labels.json``, where the json file controls
the behavior of the program.
If the annotation file ``imgLabel.json`` is in ``tools`` folder
with ``trainInfo.json`` and ``testInfo.json``,
running the program will generate the final result ``images.json`` here.

.. code-block:: sh

   python gen_labels.py

You can modify ``gen_labels.json`` to specify other filenames.
Copy the final result to ``config`` folder so it can be recognized
by the framework.

Run a Test
----------

If you have complete steps above, there is a sample program in
``test`` folder. To run the program, use these commands:

.. code-block:: sh

   make
   cd bin
   ./fys

An illustration of point mapping of two images will appear and last
for five seconds.

