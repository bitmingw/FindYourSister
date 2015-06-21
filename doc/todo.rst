Your Works
==========

Based on the framework, an object recognition program can be built with
only a few lines code.

.. code-block:: c++

   void testAlgoMatch(string featuresFile, string imagesFile)
   {
   FysAlgorithms app(featuresFile, imagesFile);
   app.runTest();
   
   namedWindow("matching");
   imshow("matching", app.visualizeMatch(0, 0));
   waitKey(5000);
   }

However, it is only an illustration.
You should add your own algorithms to improve the performance.
To restrain the feature points in specific areas, please use
helper functions in ``src/util.cpp``.
To add you own algorithms for object detection, please change the
function ``runEach()`` in ``src/fys_algorithms.cpp``.

