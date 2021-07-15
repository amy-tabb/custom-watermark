# custom-watermark
A quick project to add watermarks to images, scaled to the image size.  Uses ImageMagick and exiftool.  For more information, see the explanatory blog post at [amytabb.com](https://amytabb.com/tips/2021/07/15/custom-watermark-size-filesize/).

## Preliminaries
- C++
- C++ 17 compiler
- Cmake project
- need exiftool. `sudo apt install exiftool` on Ubuntu.
- need Image Magick. `sudo apt install imagemagick` on Ubuntu.

## Building

From the `build` folder, `cmake ../src`.  Then, `make`.  To install so that you can call the executable from anywhere, `sudo make install`.  I suggest you change some of the hardcoded values first, though!

## Running

```bash
./custom-watermark --help
Printing help for custom-watermark

DIRECTORIES AND PATHS ----------------------- 
--input=[STRING]              Mandatory, has to be a directory.
```

So to add watermarks to a directory of images (and possibly other files), run `./custom-watermark --input [directory]`.

