# Image2HMTL (C++ Version)
This is the C++ version of [Image2HTML](https://github.com/AoiTokikawa/Image2HTML) that was written in HTML, CSS, and JavaScript. It also comes with ways to customize the background color and the alignment of the image.  
This version also generates a valid HTML document with `<!DOCTYPE html>`, `<html>`, `<head>`, and `<body>` tags. Future versions of this program might add ways to customize this.

## Dependencies
This code uses the CImg library (downloaded from [here](https://cimg.eu/download.html))

## Usage
After compiling the source code (per your OS) using Image2HTML is easy.  
**NOTE**: For the examples we will assume that the executable executes with `image2html`, so please adjust accordingly.  
  
The program takes 4 user-provided arguments `[image filename]`, `[html output filename]`, `[html document background-color]`, and `[image-alignment]`  
  
Here is a breakdown of the arguments:
  - `[image filename]` - name of the image to be processed
  - `[html output filename]` - name of the HTML file that is output by the program
  - `[html document background-color]` - color of the background of the HTML document, currently only supports lowercase `rrggbb` and `rrggbbaa` hex strings as arguments
  - `[image-alignment]` - alignment of the image in the HTML document, currently only supports `center`, `right`, and `left` as arguments

### Converting `example.png` to HTML
This example sets the background to `ffffff` (white) and the alignment to `center`:
```
image2HTML example.png example.html ffffff center
```
This should output `example.html` containing the HTML document version of `example.png`.
