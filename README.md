# FindYourSister

This is a simple framework for object detection.

More information is provided in documentation.

## Features

- Fast and reliable framework based on OpenCV.
- Simple interfaces for object detection.
- Dynamic configuration via JSON files.
- Integrated image annotation tool.
- Adaptive for your own algorithms.

## Sample Code

```c++
void testAlgoMatch(string featuresFile, string imagesFile)
{
    FysAlgorithms app(featuresFile, imagesFile);
    app.runTest();
    namedWindow("matching");
    imshow("matching", app.visualizeMatch(0, 0));
    waitKey(5000);
}
```

## Documentation

You need Sphinx to generate the documentation.

```shell
pip install Sphinx
cd doc
make html
```

## Licence

BSD Licence.
