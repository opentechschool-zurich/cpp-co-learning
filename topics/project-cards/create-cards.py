# from urllib.request import urlopen, Request # python3
import urllib2
import re
import os
import sys
import scribus
from scribus import BUTTON_OK,ICON_WARNING

# each section corresponds to a master page in the scribus document
sectionList = [
	'Numbers',
	'Classic Algorithms',
	'Graph',
	'Data Structures',
	'Text',
	'Networking',
	'Classes',
	'Threading',
	'Web',
	'Files',
	'Databases',
	'Graphics and Multimedia',
	'Security'
]

def getMarkdownPageContent(url):
    # req = Request(url)
    # f = urlopen(req)
    # return f.read().decode('utf-8')
    response = urllib2.urlopen(url)
    return response.read()

markdown = getMarkdownPageContent('https://raw.githubusercontent.com/karan/Projects/master/README.md')

#TODO: remove the http links

lines = []

# get the all the lines after the "Numbers" title

lineBefore = ''
start = False
for line in markdown.split('\n'):
    line = line.rstrip()
    if (start == False) :
        if line == '---------' and lineBefore == 'Numbers' :
            lines.append(lineBefore)
            start = True
    if start :
        lines.append(line)
    lineBefore = line

# sort the projects by section

sectionsRaw = {}
section = ''
lineBuffer = ''
for line in lines :
    if line[:3] == '---' :
        if lineBuffer in sectionList :
            section = lineBuffer
        else :
            section = 'Normal2'
        sectionsRaw[section] = []
        lineBuffer = ''
    elif line == '' :
        if lineBuffer != '' :
            sectionsRaw[section].append(lineBuffer)
        lineBuffer = ''
    else :
        lineBuffer += line

# get the title and the description out ot the project

projects = []
for section, projectsRaw in sectionsRaw.items() :
    for project in projectsRaw :
        # m = re.match(r"(\w+) (\w+)", "Isaac Newton, physicist")
        match = re.match(r'\*\*(.+)\*\* - (.+)', project, re.MULTILINE)
        if match :
            # print(match.group(1))
            # print(match.group(2))
            # TODO: remove the * for italics
            projects.append({'section' : section, 'title': match.group(1), 'description': match.group(2)})
        # print(project)

# print(projects)
# sys.exit(1)

# add the projects to a scribus doc, one project per A6 page. for each section there is a specific master page with a logo.

if (not scribus.haveDoc()) :
    # TODO: how to open a file in the script's directory?
    # scribus.openDoc(os.path.dirname(os.path.realpath(__file__)) + '/cards.sla')
    # scribus.openDoc(os.path.dirname(os.path.realpath(sys.argv[0])) + '/cards.sla')
    scribus.messageBox("Error", "You should first open the cards.sla file", ICON_WARNING, BUTTON_OK)
    sys.exit(1)

# for page in range(2, scribus.pageCount()) :
# scribus.messageBox("Error", str(scribus.pageCount()), ICON_WARNING, BUTTON_OK)
for page in range(scribus.pageCount(), 1, -1) :
    scribus.deletePage(page)

for project in projects :
    scribus.newPage(-1, project['section'])

    # title: x=10 y=10 w=85mm h=20
    # description: x=10 y=40 w=85mm h=80
    titleFrame = scribus.createText(10, 10, 85, 20)
    scribus.setText(project['title'], titleFrame)
    scribus.setStyle('title', titleFrame)
    descriptionFrame = scribus.createText(10, 40, 85, 80)
    scribus.setText(project['description'], descriptionFrame)
    scribus.setStyle('description', descriptionFrame)

    # shrink the title and text size if it does not fit in the frame
    while scribus.textOverflows(titleFrame) != 0 :
        fontSize = scribus.getFontSize(titleFrame)
        scribus.setFontSize(fontSize - 1, titleFrame)

    while scribus.textOverflows(descriptionFrame) != 0 :
        fontSize = scribus.getFontSize(descriptionFrame)
        scribus.setFontSize(fontSize - 1, descriptionFrame)
