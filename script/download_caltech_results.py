import re
import urllib

page = urllib.urlopen("http://www.vision.caltech.edu/Image_Datasets/CaltechPedestrians/datasets/INRIA/res/")
content = page.read()
links = re.findall(r"<a href=\".*.zip\">", content)
for link in links:
    filename = link.split("\"")[1]
    url = "http://www.vision.caltech.edu/Image_Datasets/CaltechPedestrians/datasets/INRIA/res/" + filename
    page = urllib.urlopen(url)
    content = page.read()
    f = open("/home/vlad/tools/code3.2.1/data-INRIA/res/" + filename, 'w')
    f.write(content)
    f.close()
