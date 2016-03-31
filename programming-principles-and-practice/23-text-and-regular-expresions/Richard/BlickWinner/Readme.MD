# Blick am Abend Winners

This program pulls down the web page from Blick am Abend and uses
a regular expression to extract the winners and their takings.

The tricky step was to narrow the greedyness of the regular expression as
the .* had a tendency to extract all the winners and all the html tags
in between before matching on the ending pattern. .*? is the syntax that
limits this.
