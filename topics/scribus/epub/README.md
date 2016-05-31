# Compiling Scribus with the Epub plugin

- compile scribus
  - https://github.com/aoloe/scribus-manual-development/blob/master/content/getting-started/getting-started.md
- add the scribusAPI plugin

      ~~~.sh
      cd ~/src/
      git clone git@github.com:aoloe/scribus-plugin-API.git
      cd ~/src/scribus/scribus/plugins/
      ln -s ~/src/scribus-plugin-API/src scribusAPI
      echo "ADD_SUBDIRECTORY(scribusAPI)" >> CMakeLists.txt
      ~~~

- add the Epub plugin  
  ~~~.sh
  cd ~/src/
  git clone git@github.com:aoloe/scribus-plugin-export-epub.git
  cd ~/src/scribus/scribus/plugins/export/
  ln -s ~/src/scribus-plugin-export-epub/src epub
  echo "ADD_SUBDIRECTORY(epub)" >> CMakeLists.txt
  ~~~
- recompile Scribus  
  ~~~.sh
  cd ~/src/scribus/build/
  make -j4
  make install
  ~~~

# What is Scribus

It's a layout program that produces PDFs for professional print.

- pages are manually created
- text and images get into frames
- provides advanced typographic control and color management
- the properties palette and the "window" menu

# What is Epub

Epub is a file format for reflowable documents.

Technically, it's a Zip file of containing Html, Css, Images and XML files to glue everything together.

# Exporting from Scribus to Epub

- It's a plugin.
- Plugins do not have a fixed API and can access all the Scribus code.
- (The `scribusAPI` tries to volontarily limit the too broad access rights).
- Scribus provides an exact positioning of all its element, Epub requires a flexible reflowing and size of text and images.
- We don't want get Scribus to be an Epub editor.
- Scribus should be able to export the whole content and as much as meaningful / possible of the formatting to allow a comfortable Epub creation in Sigil
- We don't want to overload Scribus with settings that are only used for managing the content flow: we need to define heuristics that try to guess the structure of the documents.  
  (Adding some feature is welcome, if they are also useful for the generation of PDF, like for the detection of captions)

# The plugin's architecture

- The epub plugins uses the scribusAPI plugin to access the Scribus core (if things are missing, add them... if possible avoiding low level structures).
- All the code is in the `src/` directory.
- `epubexportplugin.cpp` is the standard entry point from Scribus.
- `epubexport.cpp` _orchestrates_ the creation of the Epub file.
- There are six modules (for now):
  - Content: collects the content (text, images)
  - Epubfile: manages the creation and filling of the epub file: manages the creation and filling of the epub file
  - Image: prepare the image for the export
  - Structure: stores information related to the structure of the content
  - Xhtml: collects each xhtml for the chapters
  - Zip: convience functions for zipping

# Tasks

- create a doxygen documentation
- setup a suite of tests
- work on an euristhic for images / captions / multi column text
- make sure that the zip library is the right one
- start implementing lists / footnotes
- resizing images (should already be started)


# Specification

EPUB export  Scribus

## Goal

Export a whole SLA document (or sections of it) to EPUB.

In a first step, Scribus will export the whole document to HTML and CSS in a compatible way with EPub creators (cf. Sigil).


## Features

### Text handling

- Convert styles
  - keep the name of the styles
  - detect h1, h2, h3, p, img
  - Retain bold, italics and underlined
  - Retain sup and sub
  - Retain CAPS, small caps, stroke, shadow
  - Retain the paragraph spacing and indentings
  - Keep colors (converting them to local defined rgb)
  - Font size (conversion in em or px)
  - Keep font names, include fonts and guess if it's a serif or not
- Retain local text formattings (see the "styles" for details)
- Detect text flow
  - Linked text frames are kept together
  - Order of text frames is defined by their left upper corner and page

### Image frames
  - all images converted to jpg (only for jpg), png (all other images; warning: transparencies!), gif (+ manual settings)
  - detect / define the image size (max size? full width, half width, ...)
  - cut at frame borders
  - Image position relative to the surrounding text

### Shapes
  - no support for now
  - evt. render groups of shapes as PNG

### Sections
  - Each section is put in its own HTML file

### Layout
  - Element on master pages are ignored


Future plans
- recognize bullets as soon as scribus has real list
- tables (as soon as supported by scribus)
- footnotes (as soon as supported by scribus)
- links (as soon as inline links are supported by scribus)
- manually mark elements to be ignored when exported

## Implementation

- The EPub exporter is implement as a Plugin for Scribus 1.5
- Export all text from a SLA file in the correct order
- Extract list of styles and their properties from a document
- Create a converter from Scribus formattings to HTML formattings (styles + local formatting)
- Detect / define h1, h2, h3, ...
- Detect and convert local formattings
- Place image frames based on their location on the page (upper / lower halves -> before / after last / first paragraph)
- Convert and cut images to the correct format / size
- Separation in sections

Roadmap
---

- Publish this document and look for comments
- Publish Claudia's workpaper
